#ifndef PAUSE_INTERPOLATE_HPP
#define PAUSE_INTERPOLATE_HPP

///////////////////////////////////////////////////
//! @file  nogara/interpolate/pause_interpolate.hpp
//! @brief ニ行列間の姿勢補間を行うクラス
///////////////////////////////////////////////////

#include <nogara/vector.hpp>
#include <nogara/matrix.hpp>

__NOGARA_BEGIN

template<class T>
class pause_interpolate{
    typedef typename deduct1<T>::real_type real_t;
public:
    //! @brief 行列は3x3以上の行列を要求する
    template<class E1, class E2>
    pause_interpolate(expression::matrix_expression<E1> const& e1,
                      expression::matrix_expression<E2> const& e2,
                      typename boost::enable_if<
                      boost::mpl::and_<
                      expression::matrix_over_size_c<E1, 3, 3>,
                      expression::matrix_over_size_c<E2, 3, 3> >
                      >::type* = 0):
        from_y(normalize(swizzle<swizzle_xyz>(expression::expr_column_vector<E1, 1>(e1)))),
        from_z(normalize(swizzle<swizzle_xyz>(expression::expr_column_vector<E1, 2>(e1)))),
        to_y(normalize(swizzle<swizzle_xyz>(expression::expr_column_vector<E2, 1>(e2)))),
        to_z(normalize(swizzle<swizzle_xyz>(expression::expr_column_vector<E2, 2>(e2)))){}

    matrix33<T> operator()(real_t t) const {
		vector3f const ty = slerp(from_y, to_y, t);
        vector3f const tz = slerp(from_z, to_z, t);
        vector3f const tx = cross(ty, tz);
        vector3f const iy = normalize(cross(tz, tx));
        vector3f const ix = normalize(tx);
        vector3f const iz = normalize(tz);
        return matrix33<T>(ix(0), iy(0), iz(0),
                           ix(1), iy(1), iz(1),
                           ix(2), iy(2), iz(2));
    }
private:
    //! @brief 始点のY軸姿勢
    vector3<T> const from_y;
    //! @brief 始点のZ軸姿勢
    vector3<T> const from_z;
    //! @brief 終点のY軸姿勢
    vector3<T> const to_y;
    //! @brief 終点のZ軸姿勢
    vector3<T> const to_z;
};

__NOGARA_END

#endif
