/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{

  LetExp::LetExp(const Location& location, DecsList* decs, Exp* exp)
    : Exp(location)
    , decs_(decs)
    , exp_(exp)
  {}

  LetExp::~LetExp()
  {
    delete decs_;
    delete exp_;
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

