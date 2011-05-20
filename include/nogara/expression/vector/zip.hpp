#ifndef NOGARA_EXPRESSION_VECTOR_ZIP_HPP
#define NOGARA_EXPRESSION_VECTOR_ZIP_HPP

/*
struct row_accessor{
    template<class V1, class V2> struct behind{
        typedef typename boost::mpl::if_<
        boost::mpl::less<get_dimension<V1>, get_dimension<V2> >,
        get_dimension<V1>, get_dimension<V2> >::type vector_size;

        struct size{
            typedef vector_size Row;
            typedef 2           Column;
        };
    };
};

template<class V1, class V2, class accessor>
class vector_zipped_matrix : 
    public matrix_expression<vector_zipped_matrix<V1, V2, accessor> >
{
    typedef accessor::behind<V1, V2> access;

public:
    typedef typename deduct2<V1, V2>::value_type value_type;
    typedef value_type                           reference;
    typedef value_type                           const_reference;
    typedef typename access::size::Row           Row;
    typedef typename access::size::Column        Column;

    value_type operator()(std::size_t x, std::size_t y) const {
    return 
    }

private:
    V1 const& v1; V2 const& v2;
};


zip_to_matrix()
*/

#endif
