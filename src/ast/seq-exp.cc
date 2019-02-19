/**
 ** \file ast/seq-exp.cc
 ** \brief Implementation of ast::SeqExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/seq-exp.hh>

namespace ast
{

  SeqExp::SeqExp(const Location& location, exps_type* exps)
    : Exp(location)
    , exps_(exps)
  {}

  SeqExp::~SeqExp()
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
  SeqExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  SeqExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

