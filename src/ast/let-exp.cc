/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{

  LetExp::LetExp(const Location& location, DecsList* decs, Exp* body)
    : Exp(location)
    , decs_(decs)
    , body_(body)
  {}

  LetExp::~LetExp()
  {
    delete decs_;
    delete body_;
  }

  void
  LetExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  LetExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

