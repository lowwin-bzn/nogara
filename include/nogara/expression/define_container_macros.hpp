#ifndef DOXYGEN_SHOULD_SKIP_THIS 
#if defined(NG_CPP0X)

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X(N) \
    MAKE_CONSTRUCTOR_EXTENDS_CPP0X##N

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X1                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)){}                                           \
    template<class U0>                                                  \
    explicit expression_container(U0&& __0):                            \
        _0(std::forward<U0>(__0)){}                                     \
    

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X2                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)){}                      \
    template<class U1, class U2>                                        \
    expression_container(U1&& __0, U2&& __1):                           \
        _0(std::forward<U1>(__0)), _1(std::forward<U2>(__1)){}

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X3                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)){}                                           \
    template<class U0, class U1, class U2>                              \
    expression_container(U0&& __0, U1&& __1, U2&& __2):                 \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)){}                                     \
    
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X4                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)){}                      \
    template<class U0, class U1, class U2, class U3>                    \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3):       \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)){}          \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X5                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)){}                                           \
    template<class U0, class U1, class U2, class U3,                    \
             class U4>                                                  \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4):                                     \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)){}                                     \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X6                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)){}                      \
    template<class U0, class U1, class U2, class U3,                    \
             class U4, class U5>                                        \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4, U5&& __5):                           \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)), _5(std::forward<U5>(__5)){}          \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X7                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)){}                                           \
    template<class U0, class U1, class U2, class U3,                    \
             class U4, class U5, class U6>                              \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4, U5&& __5, U6&& __6):                 \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)), _5(std::forward<U5>(__5)),           \
        _6(std::forward<U6>(__6)){}                                     \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X8                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)){}                      \
    template<class U0, class U1, class U2, class U3,                    \
             class U4, class U5, class U6, class U7>                    \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4, U5&& __5, U6&& __6, U6&& __7):       \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)), _5(std::forward<U5>(__5)),           \
        _6(std::forward<U6>(__6)), _7(std::forward<U7>(__7)){}          \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X9                                 \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)){}                                           \
    template<class U0, class U1, class U2, class U3,                    \
             class U4, class U5, class U6, class U7,                    \
             class U8>                                                  \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4, U5&& __5, U6&& __6, U6&& __7,        \
                         U8&& __8):                                     \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)), _5(std::forward<U5>(__5)),           \
        _6(std::forward<U6>(__6)), _7(std::forward<U7>(__7)),           \
        _8(std::forward<U8>(__8)){}                                     \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X10                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)){}                      \
    template<class U0, class U1, class  U2, class U3,                   \
             class U4, class U5, class  U6, class U7,                   \
             class U8, class U9>                                        \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4, U5&& __5, U6&& __6, U6&& __7,        \
                         U8&& __8, U9&& __9):                           \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)), _5(std::forward<U5>(__5)),           \
        _6(std::forward<U6>(__6)), _7(std::forward<U7>(__7)),           \
        _8(std::forward<U8>(__8)), _9(std::forward<U9>(__9)){}          \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X11                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)),                       \
        _10(std::move(c._10)){}                                         \
    template<class U0, class U1, class  U2, class U3,                   \
             class U4, class U5, class  U6, class U7,                   \
             class U8, class U9, class U10>                             \
    expression_container(U0&& __0, U1&& __1, U2&& __2, U3&& __3,        \
                         U4&& __4, U5&& __5, U6&& __6, U6&& __7,        \
                         U8&& __8, U9&& __9, U10&& __10):               \
        _0(std::forward<U0>(__0)), _1(std::forward<U1>(__1)),           \
        _2(std::forward<U2>(__2)), _3(std::forward<U3>(__3)),           \
        _4(std::forward<U4>(__4)), _5(std::forward<U5>(__5)),           \
        _6(std::forward<U6>(__6)), _7(std::forward<U7>(__7)),           \
        _8(std::forward<U8>(__8)), _9(std::forward<U9>(__9)),           \
        _10(std::forward<U10>(__10)){}                                  \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X12                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)),                       \
        _10(std::move(c._10)), _11(std::move(c._9)){}                   \
    template<class U0, class U1, class  U2, class  U3,                  \
             class U4, class U5, class  U6, class  U7,                  \
             class U8, class U9, class U10, class U11>                  \
    expression_container(U0&& __0, U1&& __1, U2&&  __2,  U3&&  __3,     \
                         U4&& __4, U5&& __5, U6&&  __6,  U7&&  __7,     \
                         U8&& __8, U9&& __9, U10&& __10, U11&& __11):   \
        _0(std::forward<U0>(__0)),    _1(std::forward<U1>(__1)),        \
        _2(std::forward<U2>(__2)),    _3(std::forward<U3>(__3)),        \
        _4(std::forward<U4>(__4)),    _5(std::forward<U5>(__5)),        \
        _6(std::forward<U6>(__6)),    _7(std::forward<U7>(__7)),        \
        _8(std::forward<U8>(__8)),    _9(std::forward<U9>(__9)),        \
        _10(std::forward<U10>(__10)), _11(std::forward<U11>(__11)){}    \
    
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X13                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)),                       \
        _10(std::move(c._10)), _11(std::move(c._11)),                   \
        _12(std::move(c._12)){}                                         \
    template<class U0,  class U1,  class  U2, class  U3,                \
             class U4,  class U5,  class  U6, class  U7,                \
             class U8,  class U9,  class U10, class U11,                \
             class U12>                                                 \
    expression_container(U0&&  __0,  U1&&  __1,  U2&&  __2,  U3&&  __3, \
                         U4&&  __4,  U5&&  __5,  U6&&  __6,  U7&&  __7, \
                         U8&&  __8,  U9&&  __9,  U10&& __10, U11&& __11, \
                         U12&& __12):                                   \
        _0(std::forward<U0>(__0)),    _1(std::forward<U1>(__1)),        \
        _2(std::forward<U2>(__2)),    _3(std::forward<U3>(__3)),        \
        _4(std::forward<U4>(__4)),    _5(std::forward<U5>(__5)),        \
        _6(std::forward<U6>(__6)),    _7(std::forward<U7>(__7)),        \
        _8(std::forward<U8>(__8)),    _9(std::forward<U9>(__9)),        \
        _10(std::forward<U10>(__10)), _11(std::forward<U11>(__11)),     \
        _12(std::forward<U12>(__12)){}                                  \


#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X14                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)),                       \
        _10(std::move(c._10)), _11(std::move(c._11)),                   \
        _12(std::move(c._12)), _13(std::move(c._13)){}                  \
    template<class U0,  class U1,  class  U2, class  U3,                \
             class U4,  class U5,  class  U6, class  U7,                \
             class U8,  class U9,  class U10, class U11,                \
             class U12, class U13>                                      \
    expression_container(U0&&  __0,  U1&&  __1,  U2&&  __2,  U3&&  __3, \
                         U4&&  __4,  U5&&  __5,  U6&&  __6,  U7&&  __7, \
                         U8&&  __8,  U9&&  __9,  U10&& __10, U11&& __11, \
                         U12&& __12, U13&& __13):                       \
        _0(std::forward<U0>(__0)),    _1(std::forward<U1>(__1)),        \
        _2(std::forward<U2>(__2)),    _3(std::forward<U3>(__3)),        \
        _4(std::forward<U4>(__4)),    _5(std::forward<U5>(__5)),        \
        _6(std::forward<U6>(__6)),    _7(std::forward<U7>(__7)),        \
        _8(std::forward<U8>(__8)),    _9(std::forward<U9>(__9)),        \
        _10(std::forward<U10>(__10)), _11(std::forward<U11>(__11)),     \
        _12(std::forward<U12>(__12)), _13(std::forward<U13>(__13)){}    \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X15                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)),                       \
        _10(std::move(c._10)), _11(std::move(c._11)),                   \
        _12(std::move(c._12)), _13(std::move(c._13)),                   \
        _14(std::move(c._14)){}                                         \
    template<class U0,  class U1,  class  U2, class  U3,                \
             class U4,  class U5,  class  U6, class  U7,                \
             class U8,  class U9,  class U10, class U11,                \
             class U12, class U13, class U14>                           \
    expression_container(U0&&  __0,  U1&&  __1,  U2&&  __2,  U3&&  __3, \
                         U4&&  __4,  U5&&  __5,  U6&&  __6,  U7&&  __7, \
                         U8&&  __8,  U9&&  __9,  U10&& __10, U11&& __11, \
                         U12&& __12, U13&& __13, U14&& __14):           \
        _0(std::forward<U0>(__0)),    _1(std::forward<U1>(__1)),        \
        _2(std::forward<U2>(__2)),    _3(std::forward<U3>(__3)),        \
        _4(std::forward<U4>(__4)),    _5(std::forward<U5>(__5)),        \
        _6(std::forward<U6>(__6)),    _7(std::forward<U7>(__7)),        \
        _8(std::forward<U8>(__8)),    _9(std::forward<U9>(__9)),        \
        _10(std::forward<U10>(__10)), _11(std::forward<U11>(__11)),     \
        _12(std::forward<U12>(__12)), _13(std::forward<U13>(__13)),     \
        _14(std::forward<U14>(__14)){}                                  \

#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X16                                \
    expression_container(expression_container&& c):                     \
        _0(std::move(c._0)), _1(std::move(c._1)),                       \
        _2(std::move(c._2)), _3(std::move(c._3)),                       \
        _4(std::move(c._4)), _5(std::move(c._5)),                       \
        _6(std::move(c._6)), _7(std::move(c._7)),                       \
        _8(std::move(c._8)), _9(std::move(c._9)),                       \
        _10(std::move(c._10)), _11(std::move(c._11)),                   \
        _12(std::move(c._12)), _13(std::move(c._13)),                   \
        _14(std::move(c._14)), _15(std::move(c._15)){}                  \
    template<class U0,  class U1,  class  U2, class  U3,                \
             class U4,  class U5,  class  U6, class  U7,                \
             class U8,  class U9,  class U10, class U11,                \
             class U12, class U13, class U14, class U15>                \
    expression_container(U0&&  __0,  U1&&  __1,  U2&&  __2,  U3&&  __3, \
                         U4&&  __4,  U5&&  __5,  U6&&  __6,  U7&&  __7, \
                         U8&&  __8,  U9&&  __9,  U10&& __10, U11&& __11, \
                         U12&& __12, U13&& __13, U14&& __14, U15&& __15): \
        _0(std::forward<U0>(__0)),    _1(std::forward<U1>(__1)),        \
        _2(std::forward<U2>(__2)),    _3(std::forward<U3>(__3)),        \
        _4(std::forward<U4>(__4)),    _5(std::forward<U5>(__5)),        \
        _6(std::forward<U6>(__6)),    _7(std::forward<U7>(__7)),        \
        _8(std::forward<U8>(__8)),    _9(std::forward<U9>(__9)),        \
        _10(std::forward<U10>(__10)), _11(std::forward<U11>(__11)),     \
        _12(std::forward<U12>(__12)), _13(std::forward<U13>(__13)),     \
        _14(std::forward<U14>(__14)), _15(std::forward<U15>(__15)){}    \


#else
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X(N)
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X1
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X2
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X3
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X4
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X5
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X6
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X7
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X8
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X9
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X10
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X11
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X12
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X13
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X14
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X15
#define MAKE_CONSTRUCTOR_EXTENDS_CPP0X16
#endif


#define MAKE_CONSTRUCTOR(N)           \
    expression_container(){}          \
    MAKE_CONSTRUCTOR##N               \
    MAKE_CONSTRUCTOR_EXTENDS_CPP0X(N) \


#define MAKE_CONSTRUCTOR1                                               \
    explicit  expression_container(T const& __0):                      \
        _0(__0){}                                                       \
    expression_container(expression_container const& c):                \
        _0(c._0){}

#define MAKE_CONSTRUCTOR2                                               \
    expression_container(T const& __0, T const& __1):                 \
        _0(__0), _1(__1){}                                              \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1){}

#define MAKE_CONSTRUCTOR3                                               \
    expression_container(T const& __0, T const& __1, T const& __2):  \
        _0(__0), _1(__1), _2(__2){}                                     \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2){}

#define MAKE_CONSTRUCTOR4                                               \
    expression_container(T const& __0, T const& __1, T const& __2, T const& __3): \
        _0(__0), _1(__1), _2(__2), _3(__3){}                            \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2), _3(c._3){}

#define MAKE_CONSTRUCTOR5                                               \
    expression_container(T const& __0, T const& __1, T const& __2, T const& __3, \
                         T const& __4):                                \
        _0(__0), _1(__1), _2(__2), _3(__3), _4(__4){}                   \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2), _3(c._3), _4(c._4){}

#define MAKE_CONSTRUCTOR6                                               \
    expression_container(T const& __0, T const& __1, T const& __2, T const& __3, \
                         T const& __4, T const& __5):                 \
        _0(__0), _1(__1), _2(__2), _3(__3), _4(__4), _5(__5){}          \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2), _3(c._3), _4(c._4), _5(c._5){}

#define MAKE_CONSTRUCTOR7                                               \
    expression_container(T const& __0, T const& __1, T const& __2, T const& __3, \
                         T const& __4, T const& __5, T const& __6):  \
        _0(__0), _1(__1), _2(__2), _3(__3),                             \
        _4(__4), _5(__5), _6(__6){}                                     \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2), _3(c._3),                         \
        _4(c._4), _5(c._5), _6(c._6){}

#define MAKE_CONSTRUCTOR8                                               \
    expression_container(T const& __0, T const& __1, T const& __2, T const& __3, \
                         T const& __4, T const& __5, T const& __6, T const& __7): \
        _0(__0), _1(__1), _2(__2), _3(__3),                             \
        _4(__4), _5(__5), _6(__6), _7(__7){}                            \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2), _3(c._3),                         \
        _4(c._4), _5(c._5), _6(c._6), _7(c._7){}

#define MAKE_CONSTRUCTOR9                                               \
    expression_container(T const& __0, T const& __1, T const& __2, T const& __3, \
                         T const& __4, T const& __5, T const& __6, T const& __7, \
                         T const& __8):                                \
        _0(__0), _1(__1), _2(__2), _3(__3),                             \
        _4(__4), _5(__5), _6(__6), _7(__7),                             \
        _8(__8){}                                                       \
    expression_container(expression_container const& c):                \
        _0(c._0), _1(c._1), _2(c._2), _3(c._3),                         \
        _4(c._4), _5(c._5), _6(c._6), _7(c._7),                         \
        _8(c._8){}


#define MAKE_CONSTRUCTOR10                                              \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9):                \
        _0(__0),   _1(__1), _2(__2), _3(__3),                           \
        _4(__4),   _5(__5), _6(__6), _7(__7),                           \
        _8(__8),   _9(__9){}                                            \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1), _2(c._2), _3(c._3),                       \
        _4(c._4),   _5(c._5), _6(c._6), _7(c._7),                       \
        _8(c._8),   _9(c._9){}


#define MAKE_CONSTRUCTOR11                                               \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9,  T const& __10): \
        _0(__0),   _1(__1),   _2(__2),   _3(__3),                       \
        _4(__4),   _5(__5),   _6(__6),   _7(__7),                       \
        _8(__8),   _9(__9),   _10(__10){}                               \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1),  _2(c._2),   _3(c._3),                    \
        _4(c._4),   _5(c._5),  _6(c._6),   _7(c._7),                    \
        _8(c._8),   _9(c._9),  _10(c._10){}

#define MAKE_CONSTRUCTOR12                                               \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9,  T const& __10, T const& __11): \
        _0(__0),   _1(__1),   _2(__2),   _3(__3),                       \
        _4(__4),   _5(__5),   _6(__6),   _7(__7),                       \
        _8(__8),   _9(__9),   _10(__10), _11(__11){}                    \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1),  _2(c._2),   _3(c._3),                    \
        _4(c._4),   _5(c._5),  _6(c._6),   _7(c._7),                    \
        _8(c._8),   _9(c._9),  _10(c._10), _11(c._11){}

#define MAKE_CONSTRUCTOR13                                               \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9,  T const& __10, T const& __11, \
                         T const& __12):                               \
        _0(__0),   _1(__1),   _2(__2),   _3(__3),                       \
        _4(__4),   _5(__5),   _6(__6),   _7(__7),                       \
        _8(__8),   _9(__9),   _10(__10), _11(__11),                     \
        _12(__12){}                                                     \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1),  _2(c._2),   _3(c._3),                    \
        _4(c._4),   _5(c._5),  _6(c._6),   _7(c._7),                    \
        _8(c._8),   _9(c._9),  _10(c._10), _11(c._11),                  \
        _12(c._12){}


#define MAKE_CONSTRUCTOR14                                               \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9,  T const& __10, T const& __11, \
                         T const& __12, T const& __13):               \
        _0(__0),   _1(__1),   _2(__2),   _3(__3),                       \
        _4(__4),   _5(__5),   _6(__6),   _7(__7),                       \
        _8(__8),   _9(__9),   _10(__10), _11(__11),                     \
        _12(__12), _13(__13){}                                          \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1),  _2(c._2),   _3(c._3),                    \
        _4(c._4),   _5(c._5),  _6(c._6),   _7(c._7),                    \
        _8(c._8),   _9(c._9),  _10(c._10), _11(c._11),                  \
        _12(c._12), _13(c._13){}


#define MAKE_CONSTRUCTOR15                                              \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9,  T const& __10, T const& __11, \
                         T const& __12, T const& __13, T const& __14): \
        _0(__0),   _1(__1),   _2(__2),   _3(__3),                       \
        _4(__4),   _5(__5),   _6(__6),   _7(__7),                       \
        _8(__8),   _9(__9),   _10(__10), _11(__11),                     \
        _12(__12), _13(__13), _14(__14){}                               \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1),  _2(c._2),   _3(c._3),                    \
        _4(c._4),   _5(c._5),  _6(c._6),   _7(c._7),                    \
        _8(c._8),   _9(c._9),  _10(c._10), _11(c._11),                  \
        _12(c._12), _13(c._13), _14(c._14){}

#define MAKE_CONSTRUCTOR16                                               \
    expression_container(T const& __0,  T const& __1,  T const& __2,  T const& __3, \
                         T const& __4,  T const& __5,  T const& __6,  T const& __7, \
                         T const& __8,  T const& __9,  T const& __10, T const& __11, \
                         T const& __12, T const& __13, T const& __14, T const& __15): \
        _0(__0),   _1(__1),   _2(__2),   _3(__3),                       \
        _4(__4),   _5(__5),   _6(__6),   _7(__7),                       \
        _8(__8),   _9(__9),   _10(__10), _11(__11),                     \
        _12(__12), _13(__13), _14(__14), _15(__15){}                    \
    expression_container(expression_container const& c):                \
        _0(c._0),   _1(c._1),  _2(c._2),   _3(c._3),                    \
        _4(c._4),   _5(c._5),  _6(c._6),   _7(c._7),                    \
        _8(c._8),   _9(c._9),  _10(c._10), _11(c._11),                  \
        _12(c._12), _13(c._13), _14(c._14), _15(c._15){}


#define ASSIGN_IMPL1 _0 = c._0
#define ASSIGN_IMPL2 _0 = c._0; _1 = c._1
#define ASSIGN_IMPL3      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2

#define ASSIGN_IMPL4      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3

#define ASSIGN_IMPL5      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3; \
    _4 = c._4

#define ASSIGN_IMPL6      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3; \
    _4 = c._4; _5 = c._5

#define ASSIGN_IMPL7      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3; \
    _4 = c._4; _5 = c._5; \
    _6 = c._6

#define ASSIGN_IMPL8      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3; \
    _4 = c._4; _5 = c._5; \
    _6 = c._6; _7 = c._7

#define ASSIGN_IMPL9      \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3; \
    _4 = c._4; _5 = c._5; \
    _6 = c._6; _7 = c._7; \
    _8 = c._8

#define ASSIGN_IMPL10     \
    _0 = c._0; _1 = c._1; \
    _2 = c._2; _3 = c._3; \
    _4 = c._4; _5 = c._5; \
    _6 = c._6; _7 = c._7; \
    _8 = c._8; _9 = c._9

#define ASSIGN_IMPL11      \
    _0  = c._0; _1 = c._1; \
    _2  = c._2; _3 = c._3; \
    _4  = c._4; _5 = c._5; \
    _6  = c._6; _7 = c._7; \
    _8  = c._8; _9 = c._9; \
    _10 = c._10

#define ASSIGN_IMPL12        \
    _0  = c._0;   _1 = c._1; \
    _2  = c._2;   _3 = c._3; \
    _4  = c._4;   _5 = c._5; \
    _6  = c._6;   _7 = c._7; \
    _8  = c._8;   _9 = c._9; \
    _10 = c._10; _11 = c._11

#define ASSIGN_IMPL13         \
    _0  = c._0;   _1 = c._1;  \
    _2  = c._2;   _3 = c._3;  \
    _4  = c._4;   _5 = c._5;  \
    _6  = c._6;   _7 = c._7;  \
    _8  = c._8;   _9 = c._9;  \
    _10 = c._10; _11 = c._11; \
    _12 = c._12

#define ASSIGN_IMPL14         \
    _0  = c._0;   _1 = c._1;  \
    _2  = c._2;   _3 = c._3;  \
    _4  = c._4;   _5 = c._5;  \
    _6  = c._6;   _7 = c._7;  \
    _8  = c._8;   _9 = c._9;  \
    _10 = c._10; _11 = c._11; \
    _12 = c._12; _13 = c._13

#define ASSIGN_IMPL15         \
    _0  = c._0;   _1 = c._1;  \
    _2  = c._2;   _3 = c._3;  \
    _4  = c._4;   _5 = c._5;  \
    _6  = c._6;   _7 = c._7;  \
    _8  = c._8;   _9 = c._9;  \
    _10 = c._10; _11 = c._11; \
    _12 = c._12; _13 = c._13; \
    _14 = c._14

#define ASSIGN_IMPL16         \
    _0  = c._0;   _1 = c._1;  \
    _2  = c._2;   _3 = c._3;  \
    _4  = c._4;   _5 = c._5;  \
    _6  = c._6;   _7 = c._7;  \
    _8  = c._8;   _9 = c._9;  \
    _10 = c._10; _11 = c._11; \
    _12 = c._12; _13 = c._13; \
    _14 = c._14; _15 = c._15


#if defined(NG_CPP0X)
#define MAKE_ASSIGN(N)                                              \
    expression_container& operator=(expression_container c){        \
        swap(c);                                                    \
        return *this;                                               \
    }                                                               \
    template<class U>                                               \
    expression_container& operator=(expression_container<U, N> c){  \
        swap(c);                                                    \
        return *this;                                               \
    }
#else
#define MAKE_ASSIGN(N)                                              \
    expression_container& operator=(expression_container const& c){ \
        if(&c != this){                                             \
            ASSIGN_IMPL##N;                                         \
        }                                                           \
        return *this;                                               \
    }                                                               \
    template<class U>                                               \
    expression_container& operator=(expression_container<U, N> const& c){ \
        ASSIGN_IMPL##N;                                                 \
        return *this;                                               \
    }                                                               \

#endif

#endif
