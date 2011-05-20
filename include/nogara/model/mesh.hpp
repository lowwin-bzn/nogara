#ifndef NOGARA_MESH_H
#define NOGARA_MESH_H

/////////////////////////////////
//! @file  nogara/model/mesh.hpp
//! @brief メッシュデータ
/////////////////////////////////

#include <vector>
#include <nogara/model/material.hpp>
#include <nogara/model/buffer.hpp>

__NOGARA_BEGIN

class mesh{
public:
    //! @brief メッシュデータのポインタ型
    typedef smart_ptr::shared_ptr<mesh> shared_ptr;
    //! @brief ポインタ型のエイリアス
    typedef shared_ptr                  mesh_ptr;

    //! @brief コンストラクタ
    mesh(mesh_buffer const &buf):buffer(buf){}

    //! @brief メッシュデータの描画
    void draw(uint_t mode) const {
        nogara::mesh_buffer_drawer(buffer, mode);
    }

private:
    mesh_buffer     buffer;
};

//! @brief メッシュデータの生成
template<class VertexElement, typename IntType>
inline mesh::shared_ptr make_mesh(VertexElement const *vb, std::size_t ver_size,
                                  IntType const *ib, std::size_t ind_size)
{
    return mesh::shared_ptr(new mesh(make_mesh_buffer(vb, ver_size, ib, ind_size)));
}

//! @brief メッシュデータの生成
template<class VertexElement, typename IntType>
inline mesh::shared_ptr make_mesh(std::vector<VertexElement> const &vb, std::vector<IntType> const &ib){
    return mesh::shared_ptr(new mesh(make_mesh_buffer(vb, ib)));
}

//! @brief メッシュデータの生成
template<class VertexElement, typename IntType, std::size_t SIZE>
inline mesh::shared_ptr make_mesh(std::vector<VertexElement> const &vb, IntType const (&ib)[SIZE]){
    return mesh::shared_ptr(new mesh(make_mesh_buffer(vb, ib)));
}

//! @brief メッシュデータの生成
template<class VertexElement, std::size_t SIZE, typename IntType>
inline mesh::shared_ptr make_mesh(VertexElement const (&vb)[SIZE], std::vector<IntType> const &ib){
    return mesh::shared_ptr(new mesh(make_mesh_buffer(vb, ib)));
}

//! @brief メッシュデータの生成
template<class VertexElement, std::size_t VERTEX_SIZE, typename IntType, std::size_t INDEX_SIZE>
inline mesh::shared_ptr make_mesh(VertexElement const (&vb)[VERTEX_SIZE], IntType const (&ib)[INDEX_SIZE]){
    return mesh::shared_ptr(new mesh(make_mesh_buffer(vb, ib)));
}

//! @brief メッシュデータの生成
inline mesh::shared_ptr make_mesh(mesh_buffer const& buf){
    return mesh::shared_ptr(new mesh(buf));
}

__NOGARA_END

#endif
