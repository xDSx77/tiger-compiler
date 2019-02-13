/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/visitor.hh>
#include <ast/array-exp.hh>

namespace ast
{

    ArrayExp::ArrayExp(const Location& location, Exp* exp
            NameTy* type,)
    : Exp(location)
    , exp_(exp)
    , type_(type)
  {}

  ArrayExp::~ArrayExp()
  {
    delete exp_;
    delete type_;
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

