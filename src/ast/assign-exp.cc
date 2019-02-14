/**
 ** \file ast/assign-exp.cc
 ** \brief Implementation of ast::AssignExp.
 */

#include <ast/visitor.hh>
#include <ast/assign-exp.hh>

namespace ast
{
  AssignExp::AssignExp(const Location& location, Exp* exp,
                             Var* var)
    : Exp(location)
    , exp_(exp)
    , var_(var)
  {}

  AssignExp::~AssignExp()
  {
    delete exp_;
    delete var_;
  }

  void
  AssignExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  AssignExp::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace ast

