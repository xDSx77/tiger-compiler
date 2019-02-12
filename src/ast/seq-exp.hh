/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// SeqExp.
  class SeqExp : public Exp
  {

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a SeqExp node.
    SeqExp(const Location& location, Exp* exp);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;
    /// Destroy a SeqExp node.
    virtual ~SeqExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** Name Accessors.
     ** \{ */
    /// Return exp.
    const Exp& exp_get() const;
    /// Return exp.
    Exp& exp_get();
    /** \} */

  protected:
    /// Exp.
    Exp* exp_;
  };

} // namespace ast

#include <ast/seq-exp.hxx>

