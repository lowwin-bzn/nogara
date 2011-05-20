//////////////////////////////////////////////
//! @file  nogara/model/shape/cylinder.hpp
//! @brief 筒状のモデルを生成する
//! このファイルはインクルードしないでください
//////////////////////////////////////////////

namespace cylinder_maker{
    enum{
        num_vertices = 20,
        num_vertices_half = num_vertices / 2,
        num_vertices_mul2 = num_vertices * 2,
    };

    inline void make_indices_at_first(std::vector<uint16_t> &indices){
        indices.push_back(0);
        indices.push_back(num_vertices - 1);
        indices.push_back(1);

        indices.push_back(num_vertices);
        indices.push_back(num_vertices + 1);
        indices.push_back(num_vertices_mul2 - 1);

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(num_vertices);
        indices.push_back(num_vertices + 1);
        indices.push_back(num_vertices);
        indices.push_back(1);

        indices.push_back(0);
        indices.push_back(num_vertices);
        indices.push_back(num_vertices_mul2 - 1);
        indices.push_back(num_vertices - 1);
        indices.push_back(0);
        indices.push_back(num_vertices_mul2 - 1);
    }
 
    inline void make_indices_at_end(std::vector<uint16_t> &indices){
        enum{opposite = num_vertices_half + num_vertices};
        indices.push_back(num_vertices_half);
        indices.push_back(num_vertices_half - 1);
        indices.push_back(num_vertices_half + 1);
                
        indices.push_back(opposite);
        indices.push_back(opposite + 1);
        indices.push_back(opposite - 1);

        indices.push_back(num_vertices_half);
        indices.push_back(opposite);
        indices.push_back(num_vertices_half - 1);
        indices.push_back(opposite - 1);
        indices.push_back(num_vertices_half - 1);
        indices.push_back(opposite);
        
        indices.push_back(num_vertices_half);
        indices.push_back(num_vertices_half + 1);
        indices.push_back(opposite);
        indices.push_back(opposite + 1);
        indices.push_back(opposite);
        indices.push_back(num_vertices_half + 1);
    }

    inline void make_indices_else(std::vector<uint16_t> &indices, int i){
        indices.push_back(i);
        indices.push_back(num_vertices - i);
        indices.push_back(i + 1);
        indices.push_back(num_vertices - i - 1);
        indices.push_back(i + 1);
        indices.push_back(num_vertices - i);

        indices.push_back(num_vertices + i);
        indices.push_back(num_vertices + i + 1);
        indices.push_back(num_vertices_mul2 - i);
        indices.push_back(num_vertices_mul2 - i - 1);
        indices.push_back(num_vertices_mul2 - i);
        indices.push_back(num_vertices + i + 1);

        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(num_vertices + i);
        indices.push_back(num_vertices + i + 1);
        indices.push_back(num_vertices + i);
        indices.push_back(i + 1);

        indices.push_back(num_vertices - i);
        indices.push_back(num_vertices_mul2 - i);
        indices.push_back(num_vertices - i - 1);
        indices.push_back(num_vertices_mul2 - i - 1);
        indices.push_back(num_vertices - i - 1);
        indices.push_back(num_vertices_mul2 - i);
    }

    inline void make_indices(std::vector<uint16_t> &indices){
        for(int i = 0; i < num_vertices_half; ++i){
            if(i == 0){
                make_indices_at_first(indices);
            }else if(i == num_vertices_half - 1){
                make_indices_at_end(indices);
            }else{
                make_indices_else(indices, i);
            }
        }
    }

    inline nogara::model::shared_ptr make(float radius, float height){
        typedef nogara::expression::vector3<float> vector3;
        vector3 vertices[num_vertices_mul2];
        float const height_half = height * 0.5f;
        float const theta = nogara::to_radian(360.0f / num_vertices);
        for(int i = 0; i < num_vertices; ++i){
            float const cosine = std::cos(theta * i) * radius;
            float const sine   = std::sin(theta * i) * radius;
            vertices[i] = vector3(cosine, height_half, sine);
            vertices[i + num_vertices] = vector3(cosine, -height_half, sine);
        }

        std::vector<uint16_t> indices;
        indices.reserve((12 + (num_vertices - 2) * 8) * 3);
        make_indices(indices);

        typedef nogara::vertex1<nogara::vertices::normal_type> Vertex;
        std::vector<Vertex> vb;{
            std::vector<vector3> normals = nogara::make_normals(vertices, indices);
            
            for(std::size_t i = 0; i < normals.size(); ++i){
                vb.push_back(Vertex(vertices[i], normals[i]));
            }
        }

        return nogara::make_model(nogara::make_mesh(nogara::make_mesh_buffer(vb, indices)));
    }
}

