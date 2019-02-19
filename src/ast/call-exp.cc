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
                    exps_type* exps)
    : Exp(location)
    , name_(name)
    , exps_(exps)
    {}

    CallExp::~CallExp()
    {
      if (exps_)
      {
        ast::exps_type& cp = *exps_;
        for (unsigned i = 0; i < cp.size(); i++)
          delete cp[i];
      }
      delete exps_;
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

