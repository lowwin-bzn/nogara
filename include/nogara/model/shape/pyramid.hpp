//////////////////////////////////////////////
//! @file  nogara/model/shape/pyramid.hpp
//! @brief ピラミッド型のモデルを生成する
//! このファイルはインクルードしないでください
//////////////////////////////////////////////

namespace pyramid_maker{
    inline nogara::model::shared_ptr make(float radius, float height, int num_base_vertices){
        typedef nogara::expression::vector3<float> vector3;
        std::vector<vector3> vertices;
        vertices.reserve(num_base_vertices + 1);
        //float const height_half = height * 0.5f;
        float const theta = nogara::to_radian(360.0f / num_base_vertices);
        for(int i = 0; i < num_base_vertices; ++i){
            float const cosine = std::cos(theta * i) * radius;
            float const sine = std::sin(theta * i) * radius;
            vertices.push_back(vector3(cosine, 0, sine));
        }
        vertices.push_back(vector3(0, height, 0));
        
        std::vector<uint16_t> indices;
        indices.reserve(num_base_vertices * 2 - 1);

        for(int i = 1; i < num_base_vertices - 1; ++i){
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i);
        }
        
        for(int i = 0; i < num_base_vertices; ++i){
            indices.push_back(i);
            indices.push_back(num_base_vertices);
            if(i == 0){
                indices.push_back(num_base_vertices - 1);
            }else{
                indices.push_back(i - 1);
            }
        }

        typedef nogara::vertex1<nogara::vertices::normal_type> Vertex;
        std::vector<Vertex> vb;{
            std::vector<vector3> const normals = nogara::make_normals(vertices, indices);
            for(std::size_t i = 0; i < normals.size(); ++i){
                vb.push_back(Vertex(vertices[i], normals[i]));
            }
        }

        return nogara::make_model(nogara::make_mesh(nogara::make_mesh_buffer(vb, indices)));
    }
}
