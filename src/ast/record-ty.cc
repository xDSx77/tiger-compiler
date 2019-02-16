/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-ty.hh>

namespace ast
{

  RecordTy::RecordTy(const Location& location, Field* fld)
    : Ty(location)
    , fld_(fld)
  {}

  RecordTy::~RecordTy()
  {
    delete fld_;
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

