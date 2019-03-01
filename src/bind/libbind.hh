/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */
#pragma once

#include <iosfwd>

#include <misc/xalloc.hh>

#include <ast/fwd.hh>

/// Ast management.
namespace bind
{

  extern const misc::xalloc<bool> bind;
  extern const misc::xalloc<bool> bindings_display;

  /// Output \a a on \a ostr.
  std::ostream& operator<<(std::ostream& ostr, const ast::Dec& e);


} // namespace ast
