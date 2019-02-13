/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/visitor.hh>
#include <ast/if-exp.hh>

namespace ast
{

  IfExp::IfExp(const Location& location, Exp* if)
    : Exp(location)
    , if_(if)
  {}


  void
  IfExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  IfExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

