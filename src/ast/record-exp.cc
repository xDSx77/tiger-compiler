/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-exp.hh>

namespace ast
{

  RecordExp::RecordExp(const Location& location, Ty::NameTy* type,
                      FieldInit* field)
    : Exp(location)
    , type_(type)
    , field_(field)
  {}

  RecordExp::~RecordExp()
  {
    delete type_;
    delete field_;
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

