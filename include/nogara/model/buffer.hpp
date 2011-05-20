#ifndef NOGARA_MESH_BUFFER_HPP
#define NOGARA_MESH_BUFFER_HPP

//////////////////////////////////
//! @file  nogara/model/buffer.hpp
//! @brief VBO, IBOをを扱う
//////////////////////////////////

#include <vector>
#include <nogara/model/vertex.hpp>
#include <nogara/gl_graphics.hpp>
#include <nogara/smart_ptr.hpp>
#include <nogara/typedef.hpp>
#include <nogara/array.hpp>

__NOGARA_BEGIN

////////////////////////////////
//! @brief VBOを扱うためのクラス
////////////////////////////////
class vertex_buffer{
    //! @brief 頂点型のType Erasureを行う機構
    class place_holder{
    public:
        place_holder(uint_t i):id_(i){}
        virtual ~place_holder(){
            glDeleteBuffers(1, &id_);
        }
        void draw() const {draw_impl();}
        int  id()   const {return id_;}
    private:
        virtual void draw_impl() const = 0;
        uint_t id_;
    };

    template<class vertex>
    struct vertex_info_holder : public place_holder{
        vertex_info_holder(int id):place_holder(id){}
        virtual void draw_impl() const {
            int const pos_next    = set_position_info(0);
            int const normal_next = set_normal_info(pos_next);
            int const color_next  = set_color_info(normal_next);
                                    set_uv_info(color_next);
        }

        int set_position_info(int pos) const {
            return vertices::get_position_type<vertex>::type::apply(pos, vertex::size());
        }
        int set_normal_info(int pos) const {
            return vertices::get_normal_type<vertex>::type::apply(pos, vertex::size());
        }
        int set_color_info(int pos) const {
            return vertices::get_color_type<vertex>::type::apply(pos, vertex::size());
        }
        int set_uv_info(int pos) const {
            return vertices::get_uv_type<vertex>::type::apply(pos, vertex::size());
        }
    };

    typedef smart_ptr::shared_ptr<place_holder> vertex_ptr;

public:
    //! @brief コンストラクタ
    template<class vertex>
    vertex_buffer(int id, vertex const& /*info*/):vertex_info(new vertex_info_holder<vertex>(id)){}
    //! @brief コピーコンストラクタ
    vertex_buffer(vertex_buffer const& vb):vertex_info(vb.vertex_info){}
    //! @brief 代入
    vertex_buffer& operator =(vertex_buffer const& vb){
        vertex_info = vb.vertex_info;
        return *this;
    }
    //! @brief 頂点情報を転送する
    void draw() const{
        glBindBuffer(GL_ARRAY_BUFFER, id());
        vertex_info->draw();
    }

    //! @brief VBOのID
    int id() const {return vertex_info->id();}
private:
    vertex_ptr vertex_info;
};

//! @brief VBOを生成する
template<class vertex_element>
vertex_buffer make_vertex_buffer(vertex_element const* vb,
                                 std::size_t size,
                                 GLenum draw_type = GL_STATIC_DRAW)
{
    uint_t id = 0;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size * vertex_element::size(), vb, draw_type);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertex_buffer(id, *vb);
}

//! @brief VBOを生成する
template<class Element>
vertex_buffer make_vertex_buffer(std::vector<Element> const& v, GLenum draw_type = GL_STATIC_DRAW){
    return make_vertex_buffer(&v[0], v.size(), draw_type);
}

//! @brief VBOを生成する
template<class Element, std::size_t SIZE>
vertex_buffer make_vertex_buffer(Element const (&a)[SIZE], GLenum draw_type = GL_STATIC_DRAW){
    return make_vertex_buffer(&a[0], SIZE, draw_type);
}

///////////////////////////////////////////
//! @brief 頂点配列インデックスを扱うクラス
///////////////////////////////////////////
class index_buffer{
    struct index_info{
        index_info(int i, uint16_t s, uint16_t t):id(i), size(s), type(t){}
        ~index_info(){glDeleteBuffers(1, &id);}
        uint_t id;
        uint16_t size, type;
    };

    typedef smart_ptr::shared_ptr<index_info> info_pointer;
public:
    //! @brief コンストラクタ
    index_buffer(uint_t id, uint16_t size, uint16_t type):info(new index_info(id, size, type)){}
    //! @brief コピーコンストラクタ
    index_buffer(index_buffer const &rhs):info(rhs.info){}
    //! @brief 代入
    index_buffer &operator =(index_buffer const &rhs){
        if(&rhs != this){
            info = rhs.info;
        }
        return *this;        
    }

    //! @brief IBOのID
    uint_t   id()   const {return info->id;}
    //! @brief インデックスの個数
    uint16_t size() const {return info->size;}
    //! @brief インデックスに使用している整数型のOpenGL型
    uint16_t type() const {return info->type;}

    void draw(GLenum mode) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id());
        glDrawElements(mode, size(), type(), 0);
    }

private:
    info_pointer info;
};


//! @brief IBOを生成する
template<typename T>
typename boost::enable_if<boost::is_integral<T>, index_buffer>::type
make_index_buffer(T const* ib, std::size_t size, GLenum draw_type = GL_STATIC_DRAW){
    uint_t id = 0;
    uint16_t const index_size = size * sizeof(T);
    glGenBuffers(1, &id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, ib, draw_type);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return index_buffer(id, index_size, type_to_gl_type<T>::value);
}

//! @brief IBOを生成する
template<class T>
index_buffer make_index_buffer(std::vector<T> const& ib, GLenum draw_type = GL_STATIC_DRAW){
    return make_index_buffer(&ib[0], ib.size(), draw_type);
}

//! @brief IBOを生成する
template<class T>
index_buffer make_index_buffer(T const& ib, GLenum draw_type = GL_STATIC_DRAW){
    return make_index_buffer(&ib[0], ib.size(), draw_type);
}

//! @brief IBOを生成する
template<class T, std::size_t SIZE>
index_buffer make_index_buffer(T const (&ib)[SIZE], GLenum draw_type = GL_STATIC_DRAW){
    return make_index_buffer(&ib[0], SIZE, draw_type);
}

//! @brief VBO、IBOを関連付け、管理する
class mesh_buffer{
public:
    //! @brief コンストラクタ
    mesh_buffer(vertex_buffer const &v, index_buffer const &i):vb(v), ib(i){}
    //! @brief コピーコンストラクタ
    mesh_buffer(mesh_buffer const &rhs):vb(rhs.vb), ib(rhs.ib){}
    //! @brief 代入
    mesh_buffer& operator =(mesh_buffer const &rhs){
        if(&rhs != this){
            vb = rhs.vb;
            ib = rhs.ib;
        }
        return *this;
    }

    //! VBO
    vertex_buffer const& get_vertex_buffer() const {return vb;}
    //! IBO
    index_buffer  const& get_index_buffer() const {return ib;}

    //! 頂点情報を転送し、描画する
    void draw(GLenum mode) const {
        vb.draw();
        ib.draw(mode);
    }

private:
    vertex_buffer vb;
    index_buffer  ib;
};

//! @brief バッファの生成
template<class T, class U>
inline mesh_buffer make_mesh_buffer(T const& vb, U const& ib,
                                    GLenum vb_draw = GL_STATIC_DRAW,
                                    GLenum ib_draw = GL_STATIC_DRAW)
{
    return mesh_buffer(make_vertex_buffer(vb, vb_draw), make_index_buffer(ib, ib_draw));
}

//! @brief バッファの描画をスコープ内で自動で行うための構造体
struct mesh_buffer_drawer{
    mesh_buffer_drawer(mesh_buffer const& buffer, GLenum mode){
        buffer.draw(mode);
    }

    ~mesh_buffer_drawer(){
        glDisable(GL_COLOR_MATERIAL);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};


__NOGARA_END

#endif
