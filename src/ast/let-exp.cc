/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{

  LetExp::LetExp(const Location& location, DecsList* decs, exps_type* exps)
    : Exp(location)
    , decs_(decs)
    , exps_(exps)
  {}

  LetExp::LetExp(const Location& location, DecsList* decs, Exp* exp)
    : Exp(location)
    , decs_(decs)
  {
    exps_->push_back(exp);
  }

  LetExp::~LetExp()
  {
    delete decs_;
    ast::exps_type& cp = *exps_;
    for (unsigned i = 0; i < cp.size(); i++)
      delete cp[i];
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

