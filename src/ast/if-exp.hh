/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
    /// IfExp.
    class IfExp : public Exp
    {
    public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a IfExp node.
      IfExp(const Location& location, Exp* test, Exp* body, Exp* body_2);
      IfExp(const IfExp&) = delete;
      IfExp& operator=(const IfExp&) = delete;
      /// Destroy a IfExp node.
      virtual ~IfExp();
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
      /// Return condition of the if.
      const Exp& test_get() const;
      /// Return condition of the if.
      Exp& test_get();
      /// Return instructions executed in the then.
      const Exp& body_get() const;
      /// Return instructions executed in the then.
      Exp& body_get();
      /// Return instructions executed in the else.
      const Exp* body_2_get() const;
      /// Return instructions executed in the else.
      Exp* body_2_get();

      /** \} */

  protected:
    /// Condition of the if.
    Exp* test_;
    /// Instructions executed in the then.
    Exp* body_;
    /// Instructions executed in the else.
    Exp* body_2_;
  };
} // namespace ast

#include <ast/if-exp.hxx>

