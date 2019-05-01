/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <type/fwd.hh>
#include <ast/fwd.hh>

namespace ast
{


  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */

  class TypeConstructor
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a TypeConstructor node.
    TypeConstructor();
    TypeConstructor(const TypeConstructor&) = delete;
    TypeConstructor& operator=(const TypeConstructor&) = delete;
    /// Destroy a TypeConstructor node.
    ~TypeConstructor();
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
    /// Return a pointer to the newly created type of the node.
    const type::Type* created_type_get() const;
    /// Set the created type of the node.
    void create_type_set(const type::Type* type);
    /** \} */

  protected:
    /// Pointer to the created type of the node.
    const type::Type* created_type_;
  };

} // namespace ast

#include <ast/type-constructor.hxx>

