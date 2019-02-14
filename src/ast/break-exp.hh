/**
 ** \file ast/break-exp.hh
 ** \brief Declaration of ast::BreakExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// BreakExp.
  class BreakExp : public Exp
  {
    BreakExp(const Location& location, Exp* exp);
    BreakExp(const BreakExp&) = delete;
    BreakExp& operator=(const BreakExp&) = delete;
    /// Destroy an ArrayExp node.
    virtual ~BreakExp();
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

    protected:
    /// The expression.
    Exp* exp_;
  };

} // namespace ast

#include <ast/break-exp.hxx>

