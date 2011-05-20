#ifndef NOGARA_MATRIX_ITERATOR_HPP
#define NOGARA_MATRIX_ITERATOR_HPP

///////////////////////////////////////////////
//! @file nogara/expression/matrix/iterator.hpp
//! @brief 行列の行イテレータ、列イテレータ
///////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/traits.hpp>

__NOGARA_EXPRESSION_BEGIN


namespace matrix_iterators{

template<class T>
class row_iterator;

///////////////////////
//! @brief 行イテレータ
///////////////////////
template<class T>
class const_row_iterator{
    typedef const_row_iterator<T> self_type;
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename T::value_type          value_type;
    typedef int                             difference_type;
    typedef value_type const*               pointer;
    typedef value_type const*               const_pointer;
    typedef value_type const&               reference;
    typedef value_type const&               const_reference;

private:
    const_row_iterator(T const* v, difference_type base, difference_type p):
        value(v), base_pos(base), pos((value != NULL) ? p : 0){}

public:
    const_row_iterator():value(NULL), base_pos(0), pos(0){}
    const_row_iterator(T const& v, difference_type base):value(&v), base_pos(base), pos(0){}
    const_row_iterator(T const& v, difference_type base, difference_type p):
        value(&v), base_pos(base), pos(p){}
    const_row_iterator(self_type const& it):value(it.value), base_pos(it.base_pos), pos(it.pos){}
    const_row_iterator(row_iterator<T> const& it):
        value(it.value), base_pos(it.base_pos), pos(it.pos){}

    reference operator *(){
        return (*value)()(pos, base_pos);
    }
    const_reference operator *() const {
        return (*value)()(pos, base_pos);
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
        base_pos = rhs.base_pos;
        pos = rhs.pos;
        return *this;
    }

    self_type& operator ++(){
        ++pos;
        return *this;
    }

    self_type operator ++(int){
        self_type result(self_type);
        ++(*this);
        return result;
    }

    self_type& operator--(){
        --pos;
        return *this;
    }

    self_type operator --(int){
        self_type result(self_type);
        --(*this);
        return result;
    }

    self_type operator +(difference_type n) const {
        return self_type(value, base_pos, pos + n);
    }

    self_type& operator +=(difference_type n){
        if(value != NULL){pos += n;}
        return *this;
    }

    self_type operator -(difference_type n) const {
        return self_type(value, base_pos, pos - n);
    }

    self_type& operator -=(difference_type n){
        if(value != NULL){pos -= n;}
        return *this;
    }
    
    bool operator ==(self_type const& rhs) const {
        return value == rhs.value && base_pos == rhs.base_pos && pos == rhs.pos;
    }

    bool operator <(self_type const& rhs) const {
        return value == rhs.value && base_pos < rhs.base_pos && pos < rhs.pos;
    }

    bool operator !=(self_type const& rhs) const {
        return !(*this == rhs);
    }

    bool operator <=(self_type const& rhs) const {
        return (*this < rhs) || (*this == rhs);
    }

    bool operator >=(self_type const& rhs) const {
        return !(*this < rhs);
    }

    bool operator >(self_type const& rhs) const {
        return !(*this <= rhs);
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
    T const*        value;
    difference_type base_pos;
    difference_type pos;
};

template<class T>
///////////////////////
//! @brief 行イテレータ
///////////////////////
class row_iterator{
    friend class const_row_iterator<T>;
    typedef row_iterator<T> self_type;
    typedef boost::is_const<T> constantible;
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename T::value_type          value_type;
    typedef int                             difference_type;
    typedef value_type*                     pointer;
    typedef value_type const*               const_pointer;
    typedef value_type&                     reference;
    typedef value_type const&               const_reference;

private:
    row_iterator(T* v, difference_type base, difference_type p):
        value(v), base_pos(base), pos((value != NULL) ? p : 0){}

public:
    row_iterator():value(NULL), base_pos(0), pos(0){}
    row_iterator(T& v, difference_type base):value(&v), base_pos(base), pos(0){}
    row_iterator(T& v, difference_type base, difference_type p):value(&v), base_pos(base), pos(p){}
    row_iterator(self_type const& it):value(it.value), base_pos(it.base_pos), pos(it.pos){}

    reference operator *(){
        return (*value)()(pos, base_pos);
    }
    const_reference operator *() const {
        return (*value)()(pos, base_pos);
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
        base_pos = rhs.base_pos;
        pos = rhs.pos;
        return *this;
    }

    self_type& operator ++(){
        ++pos;
        return *this;
    }

    self_type operator ++(int){
        self_type result(self_type);
        ++(*this);
        return result;
    }

    self_type& operator--(){
        --pos;
        return *this;
    }

    self_type operator --(int){
        self_type result(self_type);
        --(*this);
        return result;
    }

    self_type operator +(difference_type n) const {
        return self_type(value, base_pos, pos + n);
    }

    self_type& operator +=(difference_type n){
        if(value != NULL){pos += n;}
        return *this;
    }

    self_type operator -(difference_type n) const {
        return self_type(value, base_pos, pos - n);
    }

    self_type& operator -=(difference_type n){
        if(value != NULL){pos -= n;}
        return *this;
    }
    
    bool operator ==(self_type const& rhs) const {
        return value == rhs.value && base_pos == rhs.base_pos && pos == rhs.pos;
    }

    bool operator <(self_type const& rhs) const {
        return value == rhs.value && base_pos < rhs.base_pos && pos < rhs.pos;
    }

    bool operator !=(self_type const& rhs) const {
        return !(*this == rhs);
    }

    bool operator <=(self_type const& rhs) const {
        return (*this < rhs) || (*this == rhs);
    }

    bool operator >=(self_type const& rhs) const {
        return !(*this < rhs);
    }

    bool operator >(self_type const& rhs) const {
        return !(*this <= rhs);
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
    difference_type base_pos;
    difference_type pos;
};


template<class T>
class column_iterator;

///////////////////////
//! @brief 行イテレータ
///////////////////////
template<class T>
class const_column_iterator{
    typedef const_column_iterator<T> self_type;
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename T::value_type          value_type;
    typedef int                             difference_type;
    typedef value_type const*               pointer;
    typedef value_type const*               const_pointer;
    typedef value_type const&               reference;
    typedef value_type const&               const_reference;

private:
    const_column_iterator(T const* v, difference_type base, difference_type p):
        value(v), base_pos(base), pos((value != NULL) ? p : 0){}

public:
    const_column_iterator():value(NULL), base_pos(0), pos(0){}
    const_column_iterator(T const& v, difference_type base):
        value(&v), base_pos(base), pos(0){}
    const_column_iterator(T const& v, difference_type base, difference_type p):
        value(&v), base_pos(base), pos(p){}
    const_column_iterator(self_type const& it):
        value(it.value), base_pos(it.base_pos), pos(it.pos){}
    const_column_iterator(column_iterator<T> const& it):
        value(it.value), base_pos(it.base_pos), pos(it.pos){}

    reference operator *(){
        return (*value)()(base_pos, pos);
    }
    const_reference operator *() const {
        return (*value)()(base_pos, pos);
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
        base_pos = rhs.base_pos;
        pos = rhs.pos;
        return *this;
    }

    self_type& operator ++(){
        ++pos;
        return *this;
    }

    self_type operator ++(int){
        self_type result(self_type);
        ++(*this);
        return result;
    }

    self_type& operator--(){
        --pos;
        return *this;
    }

    self_type operator --(int){
        self_type result(self_type);
        --(*this);
        return result;
    }

    self_type operator +(difference_type n) const {
        return self_type(value, base_pos, pos + n);
    }

    self_type& operator +=(difference_type n){
        if(value != NULL){pos += n;}
        return *this;
    }

    self_type operator -(difference_type n) const {
        return self_type(value, base_pos, pos - n);
    }

    self_type& operator -=(difference_type n){
        if(value != NULL){pos -= n;}
        return *this;
    }
    
    bool operator ==(self_type const& rhs) const {
        return value == rhs.value && base_pos == rhs.base_pos && pos == rhs.pos;
    }

    bool operator <(self_type const& rhs) const {
        return value == rhs.value && base_pos < rhs.base_pos && pos < rhs.pos;
    }

    bool operator !=(self_type const& rhs) const {
        return !(*this == rhs);
    }

    bool operator <=(self_type const& rhs) const {
        return (*this < rhs) || (*this == rhs);
    }

    bool operator >=(self_type const& rhs) const {
        return !(*this < rhs);
    }

    bool operator >(self_type const& rhs) const {
        return !(*this <= rhs);
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
    T const*        value;
    difference_type base_pos;
    difference_type pos;
};

///////////////////////
//! @brief 行イテレータ
///////////////////////
template<class T>
class column_iterator{
    friend class const_column_iterator<T>;
    typedef column_iterator<T> self_type;
    typedef boost::is_const<T> constantible;
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename T::value_type          value_type;
    typedef int                             difference_type;
    typedef value_type*                     pointer;
    typedef value_type const*               const_pointer;
    typedef value_type&                     reference;
    typedef value_type const&               const_reference;

private:
    column_iterator(T* v, difference_type base, difference_type p):
        value(v), base_pos(base), pos((value != NULL) ? p : 0){}

public:
    column_iterator():value(NULL), base_pos(0), pos(0){}
    column_iterator(T& v, difference_type base):value(&v), base_pos(base), pos(0){}
    column_iterator(T& v, difference_type base, difference_type p):value(&v), base_pos(base), pos(p){}
    column_iterator(self_type const& it):value(it.value), base_pos(it.base_pos), pos(it.pos){}

    reference operator *(){
        return (*value)()(base_pos, pos);
    }
    const_reference operator *() const {
        return (*value)()(base_pos, pos);
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
        base_pos = rhs.base_pos;
        pos = rhs.pos;
        return *this;
    }

    self_type& operator ++(){
        ++pos;
        return *this;
    }

    self_type operator ++(int){
        self_type result(self_type);
        ++(*this);
        return result;
    }

    self_type& operator--(){
        --pos;
        return *this;
    }

    self_type operator --(int){
        self_type result(self_type);
        --(*this);
        return result;
    }

    self_type operator +(difference_type n) const {
        return self_type(value, base_pos, pos + n);
    }

    self_type& operator +=(difference_type n){
        if(value != NULL){pos += n;}
        return *this;
    }

    self_type operator -(difference_type n) const {
        return self_type(value, base_pos, pos - n);
    }

    self_type& operator -=(difference_type n){
        if(value != NULL){pos -= n;}
        return *this;
    }
    
    bool operator ==(self_type const& rhs) const {
        return value == rhs.value && base_pos == rhs.base_pos && pos == rhs.pos;
    }

    bool operator <(self_type const& rhs) const {
        return value == rhs.value && base_pos < rhs.base_pos && pos < rhs.pos;
    }

    bool operator !=(self_type const& rhs) const {
        return !(*this == rhs);
    }

    bool operator <=(self_type const& rhs) const {
        return (*this < rhs) || (*this == rhs);
    }

    bool operator >=(self_type const& rhs) const {
        return !(*this < rhs);
    }

    bool operator >(self_type const& rhs) const {
        return !(*this <= rhs);
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
    difference_type base_pos;
    difference_type pos;
};

}

__NOGARA_EXPRESSION_END

#endif
