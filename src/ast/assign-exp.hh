/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{

  /// AssignExp.
  class AssignExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a AssignExp node.
    AssignExp(const Location& location, Exp* exp, Var* var);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;
    /// Destroy a SubscriptVar node.
    virtual ~AssignExp();
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
    /// Return the offset expression.
    const Exp& exp_get() const;
    /// Return the offset expression.
    Exp& exp_get();
    /// Return the mother variable.
    const Var& var_get() const;
    /// Return the mother variable.
    Var& var_get();
    /** \} */

  protected:
    /// The offset expression.
    Exp* exp_;
    /// The mother variable.
    Var* var_;
  };

} // namespace ast

#include <ast/assign-exp.hxx>

