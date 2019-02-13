/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{

  /// ObjectExp.
  class ObjectExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an ObjectExp node.
    ObjectExp(const Location& location, Exp* exp, NameTy* type);
    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    /// Destroy an ObjectExp node.
    virtual ~ObjectExp();
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
    /// Return the type.
    const NameTy& type_get() const;
    /// Return the type.
    NameTy& type_get();
    /** \} */

  protected:
    /// The expression.
    Exp* exp_;
    /// The type.
    NameTy* type_;
  };

} // namespace ast

#include <ast/object-exp.hxx>

