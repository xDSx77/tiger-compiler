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
    RecordExp(const Location& location, NameTy* type, FieldInit* field);
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
    /// Return type.
    const NameTy& type_get() const;
    /// Return type.
    NameTy& type_get();
    /// Return field.
    const FieldInit& field_get() const;
    /// Return field.
    FieldInit& field_get();
    /** \} */

  protected:
    /// Type.
    NameTy* type_;
    /// Field.
    FieldInit* field_;
  };

} // namespace ast

#include <ast/record-exp.hxx>

