/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
    inline const Exp&
    IfExp::test_get() const
    {
        return *test_;
    }
    inline Exp&
    IfExp::test_get()
    {
        return *test_;
    }
    inline const Exp&
    IfExp::body_get() const
    {
        return *body_;
    }
    inline Exp&
    IfExp::body_get()
    {
        return *body_;
    }
    inline const Exp*
    IfExp::body_2_get() const
    {
        return body_2_;
    }
    inline Exp*
    IfExp::body_2_get()
    {
        return body_2_;
    }

} // namespace ast

