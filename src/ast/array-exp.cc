/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/visitor.hh>
#include <ast/array-exp.hh>

namespace ast
{

  ArrayExp::ArrayExp(const Location& location, NameTy* name_ty, Exp* size, Exp* value)
    : Exp(location)
    , name_ty_(name_ty)
    , size_(size)
    , value_(value)
  {}

  ArrayExp::~ArrayExp()
  {
    delete name_ty_;
    delete size_;
    delete value_;
  }

  void
  ArrayExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  ArrayExp::accept(Visitor& v)
  {
    v(*this);
  }


} // namespace ast

