#ifndef NOGARA_BEZIER_HPP
#define NOGARA_BEZIER_HPP

/////////////////////////////////////////
//! @file  nogara/interpolate/bezier.hpp
//! @brief ベジエ曲線を計算するライブラリ
/////////////////////////////////////////

#include <iterator>
#include <vector>
#include <nogara/expression/vector/traits.hpp>
#include <nogara/expression/vector/operator.hpp>
#include <nogara/expression/scalar/function.hpp>

__NOGARA_BEGIN

namespace invisible{
    template<class Container>
    inline std::size_t container_size(Container const& c){return c.size();}

    template<class T, std::size_t SIZE>
    inline std::size_t container_size(T const (&)[SIZE]){return SIZE;}

    template<class T>
    inline typename boost::enable_if<expression::is_vector<T>, T>::type
    zero_value(){return T::zero;}

    template<class T>
    inline typename boost::enable_if<boost::is_arithmetic<T>, T>::type
    zero_value(){return T();}
    
    template<class Result, class Container, typename T>
    Result random_access_bezier(Container const& container, T t){
        Result result = zero_value<Result>();
        int const size = container_size(container);
        for(int i = 0; i < size; ++i){
            T v = T(1);
            int a = size - 1; int b = i; int c = a - b;
            while(true){
                if(a > 1){ v *= a; --a;}else{ break;}
                if(b > 1){ v /= b; --b;}
                if(c > 1){ v /= c; --c;}
            }

            v *= std::pow(t, i) * std::pow(1 - t, (size - 1) - i);
            result += v * container[i];
        }
        return result;
    }

    template<class Iterator, typename T>
    typename std::iterator_traits<Iterator>::value_type
    iterator_bezier(Iterator it, Iterator end, T value){
        typedef typename std::iterator_traits<Iterator>::value_type Result;

        T const t = (value > 1) ? T(1) : (value < 0) ? T(0) : value;
        std::size_t const length = std::distance(it, end);

        if(length == 0){
            return (*it);
        }else if(length == 1){
            Iterator next = it; ++next;
            return nogara::lerp(*it, *next, t);
        }

        std::vector<Result> container; container.reserve(length);
        for(Iterator next = it; it != end; ++it){
            container.push_back(nogara::lerp(*it, *(++next), t));
        }

        return random_access_bezier<Result>(container, t);
    }

    template<class Container, class category, typename T>
    inline typename Container::value_type
    bezier_impl(Container const& container, T t, category){
        return iterator_bezier(container.begin(), container.end(), t);
    }

    template<class Container, typename T>
    inline typename Container::value_type
    bezier_impl(Container const& container, T t, std::random_access_iterator_tag){
        return random_access_bezier<typename Container::value_type>(container, t);
    }
}

template<class Iterator, typename T>
inline typename std::iterator_traits<Iterator>::value_type
bezier_point(Iterator begin, Iterator end, T t){
    return invisible::iterator_bezier(begin, end, t);
}

template<class Container, typename T>
inline typename std::iterator_traits<typename Container::iterator>::value_type
bezier_point(Container const& container, T t){
    typedef typename Container::iterator iterator;
    typedef std::iterator_traits<iterator> iterator_traits;
    typedef typename iterator_traits::iterator_category category;
    return invisible::bezier_impl(container, t, category());
}

template<class Result, std::size_t SIZE, typename T>
Result bezier_point(Result const (&container)[SIZE], T t){
    return invisible::random_access_bezier<Result, Result const[SIZE]>(container, t);
}

__NOGARA_END

#endif
