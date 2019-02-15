/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{

  /// ArrayExp.
  class ArrayExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an ArrayExp node.
    ArrayExp(const Location& location, NameTy* type, Exp* size, Exp* value);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    /// Destroy an ArrayExp node.
    virtual ~ArrayExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return the type.
    const NameTy& type_get() const;
    /// Return the type.
    NameTy& type_get();
    /// Return the size of the array.
    const Exp& size_get() const;
    /// Return the size of the array.
    Exp& size_get();
    /// Return the value of the array.
    const Exp& value_get() const;
    /// Return the value of the array.
    Exp& value_get();
    /** \} */

  protected:
    /// The type of the array.
    NameTy* type_;
    /// The size of the array.
    Exp* size_;
    /// The value of the array.
    Exp* value_;
  };

} // namespace ast

#include <ast/array-exp.hxx>

