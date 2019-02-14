/**
 ** \file ast/method-call-exp.hh
 ** \brief Declaration of ast::MethodCallExp.
 */

#pragma once

#include <ast/call-exp.hh>
#include <ast/method-dec.hh>
#include <ast/var.hh>

namespace ast
{

  /** \class ast::MethodCallExp
   ** \brief Method call.
   **
   ** A method call is \em not a function call in the strict sense
   ** of object-oriented programming.  Inheritance is used as a
   ** factoring tool here.
   */

  /// MethodCallExp.
  class MethodCallExp : public CallExp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a MethodCallExp node.
    MethodCallExp(const Location& location, Var* var, MethodDec* method);
    MethodCallExp(const MethodCallExp&) = delete;
    MethodCallExp& operator=(const MethodCallExp&) = delete;
    /// Destroy a MethodCallExp node.
    virtual ~MethodCallExp();
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
    /// Return variable.
    const Var& var_get() const;
    /// Return variable.
    Var& var_get();
    /// Return method declaration.
    const MethodDec& method_get() const;
    /// Return method declaration.
    MethodDec& method_get();
    /** \} */

  protected:
    /// Variable.
    Var* var_;
    /// Method Declaration.
    MethodDec* method_;

  };

} // namespace ast

#include <ast/method-call-exp.hxx>

