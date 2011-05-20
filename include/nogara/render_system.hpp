#ifndef NOGARA_RENDER_SYSTEM_HPP
#define NOGARA_RENDER_SYSTEM_HPP

////////////////////////////////////////
//! @file  nogara/render_system.hpp
//! @brief OpenGLへの処理を受け持つクラス
/////////////////////////////////////////

#include <nogara/camera.hpp>
#include <boost/optional.hpp>
#include <nogara/color/color.hpp>
#include <nogara/gl_graphics.hpp>

__NOGARA_BEGIN

class render_system{
    typedef boost::optional<nogara::matrixf> optional_m;
public:
    render_system():
        projection_(nogara::matrixf::identity),
        inv_projection_(nogara::matrixf::identity),
        modelview_(nogara::matrixf::identity),
        update_projection(true)
    {}

    void clear_color(float r, float g, float b, float a = 1.0f){
        back_color_.set_color(r, g, b, a);
        glClearColor(r, g, b, a);
    }

    void clear_color(nogara::rgba::color<float> const& color){
        clear_color(color.rgba(0), color.rgba(1), color.rgba(2), color.rgba(3));
    }
    nogara::rgba::color<float> const& back_color() const {return back_color_;}

    void use_shader(uint_t id){glUseProgram(id);}
    void unuse_shader(){glUseProgram(0);}

    template<std::size_t N>
    void enable_opengl_state(){glEnable(N);}
    void enable_opengl_state(int N){glEnable(N);}

    template<std::size_t N>
    void disable_opengl_state(){glDisable(N);}
    void disable_opengl_state(int N){glDisable(N);}

    template<std::size_t N>
    typename boost::enable_if<
    boost::mpl::less<boost::mpl::size_t<N>, light_enums::max_lights> >::type
    use_light_num(){enable_opengl_state<light_enums::get_light<N>::value>();}

    template<std::size_t N>
    typename boost::enable_if<
    boost::mpl::less<boost::mpl::size_t<N>, light_enums::max_lights> >::type
    unuse_light_num(){disable_opengl_state<light_enums::get_light<N>::value>();}

    //! @brief 指定した番号のライトにライト情報を書き込む関数
    template<std::size_t N>
    void set_light(nogara::light const& light){
        std::size_t const light_num = light_enums::get_light<N>::value;
        glLightfv(light_num, light_enums::position::value,              light.position_with_type().begin());
        glLightfv(light_num, light_enums::spot_direction::value,        light.direction().begin());

        glLightfv(light_num, material_enums::diffuse::value,            light.diffuse().to_pointer());
        glLightfv(light_num, material_enums::ambient::value,            light.ambient().to_pointer());
        glLightfv(light_num, material_enums::specular::value,           light.specular().to_pointer());

        glLightf(light_num,  light_enums::spot_exponent::value,         light.exponent());
        glLightf(light_num,  light_enums::spot_cutoff::value,           light.cutoff());
        glLightf(light_num,  light_enums::constant_attenuation::value,  light.constant_attenuation());
        glLightf(light_num,  light_enums::linear_attenuation::value,    light.linear_attenuation());
        glLightf(light_num,  light_enums::quadratic_attenuation::value, light.quadratic_attenuation());
    }

    //! @brief 現在のマテリアルを変更する関数
    void set_material(nogara::material<float> const& material){
        glMaterialfv(GL_FRONT_AND_BACK, material_enums::diffuse::value,   material.diffuse.to_pointer());
        glMaterialfv(GL_FRONT_AND_BACK, material_enums::ambient::value,   material.ambient.to_pointer());
        glMaterialfv(GL_FRONT_AND_BACK, material_enums::specular::value,  material.specular.to_pointer());
        glMaterialfv(GL_FRONT_AND_BACK, material_enums::emission::value,  material.emissive.to_pointer());
        glMaterialf(GL_FRONT_AND_BACK,  material_enums::shininess::value, material.shininess);
    }

    void perspective(float fovy, float width, float height, float near, float far){
        perspective(fovy, height / width, near, far);
    }

    void perspective(float fovy, float aspect, float near, float far){
        projection_ = nogara::perspective_matrix(fovy, aspect, near, far);
        inv_projection_ = nogara::inverse_perspective_matrix(fovy, aspect, near, far);
        update_projection = false;
    }

    void perspective(nogara::matrixf const& m){
        projection_ = m;
        inv_projection_ = nogara::inverse(m);
        update_projection = false;
    }

    void frustum(float left, float right, float top, float bottom, float near, float far){
        projection_ = nogara::frustum_matrix(left, right, top, bottom, near, far);
        inv_projection_ = nogara::inverse_frustum_matrix(left, right, top, bottom, near, far);
        update_projection = false;
    }

    void ortho(float left, float right, float top, float bottom, float near, float far){
        projection_ = nogara::ortho_matrix(left, right, top, bottom, near, far);
        inv_projection_ = nogara::inverse_ortho_matrix(left, right, top, bottom, near, far);
        update_projection = false;
    }

    void look_at(nogara::vector3f const& look,
                 nogara::vector3f const& at,
                 nogara::vector3f const& up = nogara::vector3f::unit_y)
    {
        look_at(nogara::look_at(look, at, up));
    }

    void look_at(nogara::camera_eye const& camera){
        look_at(camera.get_matrix());
    }

    void look_at(nogara::matrixf const& m){
        modelview_ = m;
        inv_modelview_.reset();
    }

    nogara::matrixf const& projection_matrix() const {return projection_;}
    nogara::matrixf const& inverse_projection_matrix() const {return inv_projection_;}
    nogara::matrixf const& modelview_matrix() const {return modelview_;}
    nogara::matrixf const& inverse_modelview() const {
        if(!inv_modelview_){
            inv_modelview_ = nogara::inverse(modelview_);
        }
        return *inv_modelview_;
    }

    nogara::matrixf projection_modelview_matrix() const {
        projection_to_gl();
        return modelview_matrix();
    }

    nogara::matrixf inverse_projection_modelview_matrix() const {
        return inv_projection_ * (*inv_modelview_);
    }

    //! @brief オブジェクトの2D描画(主に画像描画に使用)
    template<class T>
    void draw2D(T const& obj){
        glMatrixMode(GL_PROJECTION);{
            nogara::auto_push_pop_matrix pp;
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);{
                nogara::auto_push_pop_matrix pp;
                glLoadIdentity();
                obj.draw(nogara::matrixf::identity);
                glMatrixMode(GL_PROJECTION);
            }
            glMatrixMode(GL_MODELVIEW);
        }
    }

    void projection_to_gl() const {
        if(!update_projection){
            glMatrixMode(GL_PROJECTION);
            nogara::set_world_matrix(projection_);
            glMatrixMode(GL_MODELVIEW);
            update_projection = true;
        }
    }

private:
    nogara::rgba::color<float> back_color_;

    nogara::matrixf projection_;
    nogara::matrixf inv_projection_;
    nogara::matrixf modelview_;
    mutable optional_m inv_modelview_;
    mutable bool update_projection;
};

__NOGARA_END

#endif
