/**
 ** \file object/libobject.hh
 ** \brief Declare functions and variables exported by object module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>
#include <misc/map.hh>
#include <misc/symbol.hh>

namespace object
{

  /*-------.
  | Bind.  |
  `-------*/

  misc::error bind(ast::Ast& tree);
} // namespace object
