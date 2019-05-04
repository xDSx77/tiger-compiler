/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-exp.hh>

namespace ast
{

  RecordExp::RecordExp(const Location& location, NameTy* name_ty,
                      fieldinits_type& fieldinits)
    : Exp(location)
    , name_ty_(name_ty)
    , fieldinits_(fieldinits)
  {}

  RecordExp::~RecordExp()
  {
    delete name_ty_;
    for (unsigned i = 0; i < fieldinits_.size(); i++)
      delete fieldinits_[i];
  }

  void
  RecordExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  RecordExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

