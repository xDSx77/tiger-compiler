/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/visitor.hh>
#include <ast/if-exp.hh>

namespace ast
{

  IfExp::IfExp(const Location& location, Exp* test, Exp* body, Exp body_2)
    : Exp(location)
    , test_(test)
    , body_(body)
    , body_2_(body_2)
  {}

  IfExp::~IfExp()
  {
    delete test_;
    delete body_;
    delete body_2_;
  }

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

