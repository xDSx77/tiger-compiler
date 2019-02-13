/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-ty.hh>

namespace ast
{
    RecordTy::RecordTy(const Location& location, Ty* ty,
                      Field* fld)
    : Exp(location)
    , fld_(fld)
    , ty_(ty)
  {}
  CastExp::~CastExp()
  {
    delete fld_;
    delete ty_;
  }

  void
  CastExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  CastExp::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace ast

