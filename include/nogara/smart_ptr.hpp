#ifndef NOGARA_SMART_PTR_HPP
#define NOGARA_SMART_PTR_HPP

///////////////////////////////////////////////////////
//! @file  nogara/smart_ptr.hpp
//! @brief smart_ptrを使うためのラッパー
//!        c++0x対応のコンパイラならc++0xのsmart_ptrを、
//!        そうでなければboostのsmart_ptrを使用する
///////////////////////////////////////////////////////
#include <nogara/nogara_define.hpp>

#if defined(NG_CPP0X)
#include <memory>
#else
#include <boost/smart_ptr.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp> 
#include <boost/checked_delete.hpp>
#include <boost/make_shared.hpp>
#endif

__NOGARA_BEGIN

namespace smart_ptr{
#if defined(NG_CPP0X)
    using std::shared_ptr;
    using std::weak_ptr;
    using std::unique_ptr;
    template<class T>
    struct default_unique_ptr{
        typedef unique_ptr<T> type;
    };
    using std::make_shared;
    using std::allocate_shared;
#else
    using boost::shared_ptr;
    using boost::weak_ptr;
    using boost::interprocess::unique_ptr;
    template<class T>
    struct default_unique_ptr{
        typedef unique_ptr<T, boost::checked_deleter<T> > type;
    };

    using boost::make_shared;
    using boost::allocate_shared;
#endif
}

__NOGARA_END

#endif
