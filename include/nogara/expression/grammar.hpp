#ifndef NOGARA_EXPRESSION_GRAMMAR_HPP
#define NOGARA_EXPRESSION_GRAMMAR_HPP

namespace grammar{
    namespace invisible{
        template<class E>
        class has_grammar_tag : sfinae_check{
            template<class T> static yes_type has_tag(typename T::grammar_category*);
            template<class> static no_type has_tag(...);
        public:
            static bool const value = (sizeof(yes_type) == sizeof(has_tag<E>(0)));
        };
        
        template<class E, bool has_grammar>
        struct get_grammar_tag_impl{
            typedef typename E::grammar_category type;
        };

        template<class E>
        struct get_grammar_tag_impl<E, false>{
            typedef grammar::no_grammar_tag type;
        };
    }
    template<class E>
    struct get_grammar_tag{
        typedef typename invisible::get_grammar_tag_impl<
            E, invisible::has_grammar_tag<E>::value>::type type;
    };

    template<class E>
    struct is_expression : boost::is_convertible<typename get_grammar_tag<E>::type, grammar::expression_tag>{};
    template<class E>
    struct is_terminal : boost::is_same<typename get_grammar_tag<E>::type, grammar::terminal_tag>{};
    template<class E>
    struct is_calcuator : boost::is_same<typename get_grammar_tag<E>::type, grammar::calculator_tag>{};

    template<class E>
    struct is_mutable : boost::mpl::not_<grammar::is_calcuator<E> >{};
}


#endif
