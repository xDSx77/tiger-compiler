/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/call-exp.hh>

namespace ast
{
    CallExp::CallExp(const Location& location, const misc::symbol& name,
                    exps_type exps)
    : Exp(location)
    , name_(name)
    , exps_(exps)
    {}

    CallExp::~CallExp()
    {
        for (unsigned i = 0; i < exps_.size(); i++)
          delete exps_[i];
    }

    void
    CallExp::accept(ConstVisitor& v) const
    {
        v(*this);
    }

    void
    CallExp::accept(Visitor& v)
    {
        v(*this);
    }

} // namespace ast

