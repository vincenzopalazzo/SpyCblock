#ifndef DEFINITIONMACRO_H
#define DEFINITIONMACRO_H

#ifndef NDEBUG
#   define M_Assert(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_Assert(Expr, Msg) ;
#endif

#endif // DEFINITIONMACRO_H
