#ifndef NOGARA_VECTOR_ITERATOR_H
#define NOGARA_VECTOR_ITERATOR_H

//////////////////////////////////////////////
//! @file nogara/expression/vector/iterator.hpp
//! @brief ベクトル式で使用するイテレータ
//////////////////////////////////////////////

#include <iterator>
#include <nogara/expression/define.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////
//! @brief ベクトル式で使用するイテレータ
/////////////////////////////////////////
template<class T>
class vector_iterator{
    typedef vector_iterator<T> self_type;
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename T::value_type          value_type;
    typedef int                             difference_type;
    typedef value_type*                     pointer;
    typedef value_type const*               const_pointer;
    typedef value_type&                     reference;
    typedef value_type const                const_reference;

private:
    vector_iterator(T* v, difference_type p):value(v), pos((value != NULL) ? p : 0){}

public:
    vector_iterator():value(NULL), pos(0){}
    explicit vector_iterator(T& v):value(&v), pos(0){}
    vector_iterator(T& v, difference_type p):value(&v), pos(p){}
    vector_iterator(self_type const& it):value(it.value), pos(it.pos){}

    reference operator *(){
        return (*value)()(pos);
    }
    const_reference operator *() const {
        return (*value)()(pos);
    }

    reference operator [](difference_type n){
        return *(*this + n);
    }
    const_reference operator [](difference_type n) const {
        return *(*this + n);
    }

    self_type const& base() const {
        return *this;
    }

    self_type& operator =(self_type const& rhs){
        value = rhs.value;
        pos = rhs.pos;
        return *this;
    }

    self_type& operator ++(){
        ++pos;
        return *this;
    }

    self_type operator ++(int){
        self_type result(*this);
        ++(*this);
        return result;
    }

    self_type& operator--(){
        --pos;
        return *this;
    }

    self_type operator --(int){
        self_type result(*this);
        --(*this);
        return result;
    }

    self_type operator +(difference_type n) const {
        return self_type(value, pos + n);
    }

    self_type& operator +=(difference_type n){
        if(value != NULL){pos += n;}
        return *this;
    }

    self_type operator -(difference_type n) const {
        return self_type(value, pos - n);
    }

    self_type& operator -=(difference_type n){
        if(value != NULL){pos -= n;}
        return *this;
    }
    
    bool operator ==(self_type const& rhs) const {
        return value == rhs.value && pos == rhs.pos;
    }

    bool operator !=(self_type const& rhs) const {
        return !(*this == rhs);
    }

    bool operator <(self_type const& rhs) const {
        return value == rhs.value && pos < rhs.pos;
    }

    bool operator >(self_type const& rhs) const {
        return value == rhs.value && pos > rhs.pos;
    }

    bool operator <=(self_type const& rhs) const {
        return value == rhs.value && pos <= rhs.pos;
    }

    bool operator >=(self_type const& rhs) const {
        return value == rhs.value && pos >= rhs.pos;
    }

    friend difference_type operator -(difference_type n, self_type const& iter){
        return iter.pos - n;
    }
    
    friend difference_type operator +(difference_type n, self_type const& iter){
        return iter.pos + n;
    }

    difference_type operator -(self_type const& rhs) const {
        return pos - rhs.pos;
    }

    difference_type operator +(self_type const& rhs) const {
        return pos + rhs.pos;
    }

private:
    T*              value;
    difference_type pos;
};

__NOGARA_EXPRESSION_END

#endif
