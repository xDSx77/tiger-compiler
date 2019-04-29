/**
 ** \file ast/escapable.cc
 ** \brief Implementation of ast::Escapable.
 */

#include <ast/visitor.hh>
#include <ast/escapable.hh>

namespace ast
{

  Escapable::Escapable()
    : escaped_(true)
  {}

} // namespace ast

