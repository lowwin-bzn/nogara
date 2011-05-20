#ifndef NOGARA_SHADER_CONTAINER_HPP
#define NOGARA_SHADER_CONTAINER_HPP

//////////////////////////////////////
//! @file  nogara/shader_container.hpp
//! @brief シェーダの管理機構
//////////////////////////////////////

#include <string>
#include <set>
#include <functional>
#include <nogara/gl_traits.hpp>
#include <nogara/file_cover.hpp>
#include <boost/unordered_map.hpp>

__NOGARA_BEGIN

//! @brief シェーダの管理機構
class shader_container{
    typedef boost::unordered_map<uint_t, uint_t> map_type;

    //! @brief シェーダ削除用関数オブジェクト
    struct shader_deleter{
        void operator()(map_type::value_type const& pair){
            glDeleteShader(pair.second);
        }
    };
    //! @brief プログラム削除用関数オブジェクト
    struct program_deleter{
        void operator()(map_type::value_type const& pair){
            glDeleteShader(pair.second);
        }
    };
public:
    //! @brief シェーダを解放する
    ~shader_container(){
        std::for_each(vertices.begin(),  vertices.end(),  shader_deleter());
        std::for_each(fragments.begin(), fragments.end(), shader_deleter());
        std::for_each(programs.begin(),  programs.end(),  program_deleter());
    }

    //! @brief シェーダファイル読み込み
    bool file_loader(uint_t id, char const* filename){
        nogara::file_data data(filename);
        if(!data){
            return false;
        }
        int size = data.size();
        char const* ptr = data.pointer();
        glShaderSource(id, 1, &ptr, &size);
        glCompileShader(id);
        int compiled;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
        if(compiled == GL_FALSE){
            return false;
        }
        
        return true;
    }

    //! @brief バーテックスシェーダファイルの読み込み
    bool load_vertex(uint_t id, char const* filename){
        uint_t shader = glCreateShader(GL_VERTEX_SHADER);
        if(!file_loader(shader, filename)){
            return false;
        }
        vertices[id] = shader;
        return true;
    }
    //! @brief バーテックスシェーダファイルの読み込み
    bool load_vertex(uint_t id, std::string const& filename){
        return load_vertex(id, filename.c_str());
    }

    //! @brief フラグメントシェーダファイルの読み込み
    bool load_fragment(uint_t id, char const* filename){
        uint_t shader = glCreateShader(GL_FRAGMENT_SHADER);
        if(!file_loader(shader, filename)){
            return false;
        }
        fragments[id] = shader;
        return true;
    }
    //! @brief フラグメントシェーダファイルの読み込み
    bool load_fragment(uint_t id, std::string const& filename){
        return load_fragment(id, filename.c_str());
    }

    //! @brief バーテックスシェーダとフラグメントシェーダをリンクする
    bool link_program(uint_t id, uint_t vertex_id, uint_t fragment_id){
        uint_t program = glCreateProgram();
        glAttachShader(program, vertex_id);
        glAttachShader(program, fragment_id);
        glLinkProgram(program);
        int linked;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if(linked == GL_FALSE){
            return false;
        }

        programs[id] = program;
        return true;
    }

    uint_t vertex_shader(uint_t id) const{
        return vertices.find(id)->second;
    }
    uint_t fragment_shader(uint_t id) const {
        return fragments.find(id)->second;
    }
    uint_t program(uint_t id) const {
        return programs.find(id)->second;
    }

    //! @brief バーテックスシェーダの解放
    void delete_vertex(uint_t id){
        glDeleteShader(vertices[id]);
        vertices.erase(id);
    }
    //! @brief フラグメントシェーダの解放
    void delete_fragment(uint_t id){
        glDeleteShader(fragments[id]);
        fragments.erase(id);
    }
    //! @brief プログラムの解放
    void delete_program(uint_t id){
        glDeleteProgram(programs[id]);
        programs.erase(id);
    }

private:
    map_type vertices;
    map_type fragments;
    map_type programs;
};

__NOGARA_END

#endif
