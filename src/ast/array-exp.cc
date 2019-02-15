/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/visitor.hh>
#include <ast/array-exp.hh>

namespace ast
{

  ArrayExp::ArrayExp(const Location& location, NameTy* type, Exp* size, Exp* value)
    : Exp(location)
    , type_(type)
    , size_(size)
    , value_(value)
  {}

  ArrayExp::~ArrayExp()
  {
    delete type_;
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

