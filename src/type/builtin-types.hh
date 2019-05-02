/**
 ** \file type/builtin-types.hh
 ** \brief The classes Void, Int, String.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  class Int : public Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct a Int type. */
    Int();
    /** \} */

    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the user defined type's structure.
    const int type_get() const;

    /// Set the defined type's structure.
    void type_set(const int type);
    /// Set the defined type's structure.
    void type_set(const int type) const;
    /** \} */

    bool compatible_with(const Type& other) const override;

  private:
    /// The Type pointed to.
    const int* type_;
  }

  class String : public Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct a Int type. */
    String();
    /** \} */

    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the user defined type's structure.
    const std::string type_get() const;

    /// Set the defined type's structure.
    void type_set(const std::string type);
    /// Set the defined type's structure.
    void type_set(const std::string type) const;
    /** \} */

    bool compatible_with(const Type& other) const override;

  private:
    /// The Type pointed to.
    const std::string* type_;
  }

  class Void : public Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct a Int type. */
    Void();
    /** \} */

    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */
  }
} // namespace type
