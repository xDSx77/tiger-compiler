/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{

  /// RecordExp.
  class RecordExp : public Exp
  {

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a RecordExp node.
    RecordExp(const Location& location, NameTy* type, fieldinits_type& fieldinits);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;
    /// Destroy a RecordExp node.
    virtual ~RecordExp();
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
    /// Return the type of the record.
    const NameTy& type_get() const;
    /// Return the type of the record.
    NameTy& type_get();
    /// Return the inits field of the record.
    const fieldinits_type& fieldinits_get() const;
    /// Return the inits field of the record.
    fieldinits_type& fieldinits_get();
    /** \} */

  protected:
    /// The Type of the record.
    NameTy* type_;
    /// The inits field of the record.
    fieldinits_type fieldinits_;
  };

} // namespace ast

#include <ast/record-exp.hxx>

