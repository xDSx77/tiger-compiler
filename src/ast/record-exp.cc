/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-exp.hh>

namespace ast
{

  RecordExp::RecordExp(const Location& location, NameTy* type,
                      fieldinits_type fieldinits)
    : Exp(location)
    , type_(type)
    , fieldinits_(fieldinits)
  {}

  RecordExp::~RecordExp()
  {
    delete type_;
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

