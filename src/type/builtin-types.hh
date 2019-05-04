/**
 ** \file type/builtin-types.hh
 ** \brief The classes Void, Int, String.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  class Int;
  class String;
  class Void;

  /// Singleton design pattern.
  template <class C> class Singleton : public Type
  {
  friend class Int;
  friend class String;
  friend class Void;
  public:
    /// Delete copy operators.
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    /// Get a unique instance of the Singleton.
    static C& instance()
    {
      static C instance;
      return instance;
    }

  protected:
    Singleton() = default;
  };

  /// Int builtin type.
  class Int : public Singleton<Int>
  {
  public:
    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

  };

  /// String builtin type.
  class String : public Singleton<String>
  {
  public:
    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

  };

  /// Void builtin type.
  class Void : public Singleton<Void>
  {
  public:
    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

  };

} // namespace type
