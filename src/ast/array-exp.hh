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
    /// Construct a ArrayExp node.
    ArrayExp(const Location& location, Exp* exp ,NameTy* type);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    /// Destroy a ArrayExp node.
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
    /// Return the expression.
    const Exp& exp_get() const;
    /// Return the expression.
    Exp& exp_get();
    /// Return field.
    const FieldInit& field_get() const;
    /// Return field.
    FieldInit& field_get()
    /** \} */

    protected:
    /// The expression.
    Exp* exp_;
    /// The type.
    NameTy* type_;
  };

} // namespace ast

#include <ast/array-exp.hxx>

