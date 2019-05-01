/**
 ** \file ast/typable.hh
 ** \brief Declaration of ast::Typable.
 */

#pragma once

#include <type/fwd.hh>
#include <ast/fwd.hh>

namespace ast
{


  /** \class ast::Typable
   ** \brief Hold a type information.
   **
   ** A Typable node holds a type information (type::Type) about
   ** this node.  This can be:
   ** \li the type of the node itself, if it is a Exp or a Ty, or
   ** \li the type of of the declared object, in case of a Dec.
   */

  class Typable
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Typable node.
    Typable();
    Typable(const Typable&) = delete;
    Typable& operator=(const Typable&) = delete;
    /// Destroy a Typable node.
    virtual ~Typable() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return a pointer to the type of the node.
    const type::Type* type_get() const;
    /// Set the type of the node.
    void type_set(const type::Type* type);
    /** \} */

  protected:
    /// Pointer to the type of the node.
    const type::Type* type_;
  };

} // namespace ast

#include <ast/typable.hxx>

