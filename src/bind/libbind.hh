/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */
#pragma once

#include <iosfwd>

#include <misc/xalloc.hh>

#include <ast/fwd.hh>

#include <misc/error.hh>

#include <bind/binder.hh>

/// Binding management.
namespace bind
{
  misc::error bind(ast::Ast& tree);
} // namespace bind
