/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/call-exp.hh>

namespace ast
{
    CallExp::CallExp(const Location& location, Exp* body, FunctionDec* dec, const misc::symbol& name);
    : Exp(location)
    , body_(body)
    , dec_(dec)
    , name_(name)
    {}

    CallExp::~CallExp()
    {
        delete body_;
        delete dec_;
    }

    void
    CallExp::accept(ConstVisitor& v) const
    {
        v(*this);
    }

    void
    CallExp::accept(Visitor& v)
    {
        v(*this)
    }
  // FIXME: Some code was deleted here.

} // namespace ast

