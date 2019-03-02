/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */
#pragma once


#include <ast/fwd.hh>

#include <misc/error.hh>

/// Binding management.
namespace bind
{
  misc::error bind(ast::Ast& tree);
} // namespace bind
