//////////////////////////////////////////////
//! @file  nogara/model/shape/corn.hpp
//! @brief コーン型のモデルを生成する
//! このファイルはインクルードしないでください
//////////////////////////////////////////////

namespace corn_maker{
    enum{
        num_vertices = 20,
        num_vertices_half = num_vertices / 2,
    };

    inline void indices_part_of_circle(std::vector<uint16_t> &indices){
        for(int i = 0; i < num_vertices_half; ++i){
            if(i == 0){
                indices.push_back(0);
                indices.push_back(num_vertices - 1);
                indices.push_back(1);
            }else if(i == num_vertices_half - 1){
                indices.push_back(num_vertices_half);
                indices.push_back(num_vertices_half - 1);
                indices.push_back(num_vertices_half + 1);
            }else{
                indices.push_back(i);
                indices.push_back(num_vertices - i);
                indices.push_back(i + 1);
                indices.push_back(num_vertices - i - 1);
                indices.push_back(i + 1);
                indices.push_back(num_vertices - i);
            }
        }
    }

    inline void indices_part_of_side(std::vector<uint16_t> &indices){
        for(int i = 0; i < num_vertices; ++i){
            indices.push_back(i);
            indices.push_back(num_vertices);
            if(i == 0){
                indices.push_back(num_vertices - 1);
            }else{
                indices.push_back(i - 1);
            }
        }
    }

    inline void make_indices(std::vector<uint16_t> &indices){
        indices_part_of_circle(indices);
        indices_part_of_side(indices);
    }

    inline nogara::model::shared_ptr make(float radius, float height){
        typedef nogara::vector3<float> vector3;
        std::vector<vector3> vertices;
        vertices.reserve(num_vertices + 1);
        float const height_half = height * 0.5f;
        float const theta = to_radian(360.0f / num_vertices);
        for(int i = 0; i < num_vertices; ++i){
            float const cosine = std::cos(theta * i) * radius;
            float const sine   = std::sin(theta * i) * radius;
            vertices.push_back(vector3(cosine, -height_half, sine));
        }
        vertices.push_back(vector3(0, height_half, 0));

        std::vector<uint16_t> indices;
        indices.reserve((2 + (num_vertices - 2) * 2 + num_vertices) * 3);
        make_indices(indices);

        typedef nogara::vertex1<nogara::vertices::normal_type> Vertex;
        std::vector<Vertex> vb;{
            std::vector<vector3> normals = nogara::make_normals(vertices, indices);

            for(std::size_t i = 0; i < normals.size(); ++i){
                vb.push_back(Vertex(vertices[i], normals[i]));
            }
        }

        return nogara::make_model(nogara::make_mesh(vb, indices));
    }
}
