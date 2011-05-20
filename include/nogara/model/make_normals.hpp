#ifndef NOGARA_MAKE_NORMALS_HPP
#define NOGARA_MAKE_NORMALS_HPP

/////////////////////////////////////////
//! @file  nogara/model/make_normals.hpp
//! @brief 法線ベクトル生成関数群
/////////////////////////////////////////

#include <nogara/vector.hpp>

__NOGARA_BEGIN

struct normalize_wrapper{
    template<class T> vector3<T> operator()(vector3<T> const& v){return expression::normalize(v);}
};

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class T, class U>
inline typename boost::enable_if<boost::is_integral<U>, std::vector<expression::vector3<T> > >::type
make_normals(expression::vector3<T> const* positions, std::size_t pos_size, U* indices, std::size_t index_size){
    using expression::vector3;
    std::vector<vector3<T> > normals(pos_size, vector3<T>::zero);
    for(std::size_t i = 0; i < index_size; i += 3){
        U const i0 = indices[i], i1 = indices[i + 1], i2 = indices[i + 2];
        vector3<T> const c = expression::cross(positions[i1] - positions[i0], positions[i2] - positions[i0]);
        vector3<T> const n = expression::normalize(c);
        normals[i0] += n; normals[i1] += n; normals[i2] += n;
    }

    std::transform(normals.begin(), normals.end(), normals.begin(), normalize_wrapper());
    return normals;
}

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class PosContainer, class IdxContainer>
inline std::vector<expression::vector3<typename PosContainer::value_type::value_type> >
make_normals(PosContainer const& positions, IdxContainer const& indices){
    assert(indices.size() % 3 == 0);
    return make_normals(&positions[0], positions.size(), &indices[0], indices.size());
}

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class T, std::size_t PosSize, class IdxContainer>
inline std::vector<expression::vector3<T> >
make_normals(expression::vector3<T> const (&positions)[PosSize],
             IdxContainer const& indices)
{
    assert(indices.size() % 3 == 0);
    return make_normals(&positions[0], PosSize, &indices[0], indices.size());
}

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class PosContainer, class U, std::size_t IndexSize>
inline typename boost::enable_if<
    boost::mpl::equal_to<boost::mpl::size_t<IndexSize % 3>, boost::mpl::size_t<0> >,
    std::vector<vector3<typename PosContainer::value_type::value_type> > >::type
make_normals(PosContainer const &positions, U const (&indices)[IndexSize]){
    return make_normals(&positions[0], positions.size(), &indices[0], IndexSize);
}

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class T, class U, std::size_t PosSize, std::size_t IndexSize>
inline typename boost::enable_if<
    boost::mpl::equal_to<boost::mpl::size_t<IndexSize % 3>, boost::mpl::size_t<0> >,
    std::vector<vector3<T> > >::type
make_normals(expression::vector3<T> const (&positions)[PosSize],
             U const (&indices)[IndexSize])
{
    return make_normals(positions, PosSize, indices, IndexSize);
}

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class PosContainer, class U, std::size_t IndexSize>
inline typename boost::enable_if<
    boost::mpl::equal_to<boost::mpl::size_t<IndexSize % 3>, boost::mpl::size_t<0> >,
    std::vector<vector3<typename PosContainer::value_type::value_type> > >::type
make_normals(PosContainer const &positions,
             nogara::array<U, IndexSize> const &indices){
    return make_normals(&positions[0], positions.size(), &indices[0], IndexSize);
}

//! @brief 頂点位置、頂点インデックスから法線を生成する
template<class T, class U, std::size_t PosSize, std::size_t IndexSize>
inline typename boost::enable_if<
    boost::mpl::equal_to<boost::mpl::size_t<IndexSize % 3>, boost::mpl::size_t<0> >,
    std::vector<expression::vector3<T> > >::type
make_normals(expression::vector3<T> const (&positions)[PosSize],
             nogara::array<U, IndexSize> const &indices)
{
    return make_normals(positions, PosSize, indices, IndexSize);
}

__NOGARA_END

#endif
