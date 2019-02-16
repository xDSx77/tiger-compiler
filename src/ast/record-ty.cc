/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-ty.hh>

namespace ast
{

  RecordTy::RecordTy(const Location& location, fields_type fields)
    : Ty(location)
    , fields_(fields)
  {}

  RecordTy::~RecordTy()
  {
    for (unsigned i = 0; i < fields_.size(); i++)
      delete fields_[i];
  }

  void
  RecordTy::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  RecordTy::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace ast

