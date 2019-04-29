/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{

  /// Escapable.
  class Escapable
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Escapable node.
    Escapable();
    Escapable(const Escapable&) = delete;
    Escapable& operator=(const Escapable&) = delete;
    /// Destroy a Escapable node.
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return escaped status of the defined entity.
    const bool& escape_get() const;
    /// Set escaped status of the defined entity.
    void escape_set(const bool& escaped);
    /** \} */

  protected:
    /// Escaped status of the defined entity.
    bool escaped_;
  };

} // namespace ast

#include <ast/escapable.hxx>

