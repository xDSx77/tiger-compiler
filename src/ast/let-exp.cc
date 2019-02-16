/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{

  LetExp::LetExp(const Location& location, DecsList* decs, exps_type exps)
    : Exp(location)
    , decs_(decs)
    , exps_(exps)
  {}

  LetExp::~LetExp()
  {
    delete decs_;
    for (unsigned i = 0; i < exps_.size(); i++)
      delete exps_[i];
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

