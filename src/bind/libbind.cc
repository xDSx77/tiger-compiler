/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */
#include <fstream>

#include <bind/libbind.hh>

namespace bind
{
    misc::error
    bind(ast::Ast& tree)
    {
        Binder bin;
        bin(tree);
        return bin.error_get();
    }
} // namespace bind
