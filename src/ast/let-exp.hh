/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/decs-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{

  /// LetExp.
  class LetExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a LetExp node.
    LetExp(const Location& location, DecsList* decs, exps_type* exps);
    LetExp(const Location& location, DecsList* decs, Exp* exp);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;
    /// Destroy a LetExp node.
    virtual ~LetExp();
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
    /// Return declarations of the let.
    const DecsList& decs_get() const;
    /// Return declarations of the let.
    DecsList& decs_get();
    /// Return expression in the let.
    const exps_type& exps_get() const;
    /// Return expression in the let.
    exps_type& exps_get();
    /** \} */

  protected:
    /// Declarations of the let.
    DecsList* decs_;
    /// Expressions executed in the let.
    exps_type* exps_;
  };

} // namespace ast

#include <ast/let-exp.hxx>

