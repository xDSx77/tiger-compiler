/**
 ** \file object/libobject.cc
 ** \brief Define exported object functions.
 */


#include <object/libobject.hh>
#include <object/binder.hh>

namespace object
{

  /*-------.
  | Bind.  |
  `-------*/

  misc::error
  bind(ast::Ast& tree)
  {
    Binder bin;
    bin(tree);
    return bin.error_get();
  }
} // namespace object
