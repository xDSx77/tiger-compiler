/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/visitor.hh>
#include <ast/type-constructor.hh>

namespace ast
{

  TypeConstructor::TypeConstructor()
  {}

  TypeConstructor::~TypeConstructor()
  {
    //delete created_type_;
  }

} // namespace ast

