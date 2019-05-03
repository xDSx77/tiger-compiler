/**
 ** \file type/builtin-types.hh
 ** \brief The classes Void, Int, String.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  /// Singleton design pattern.
  template <class C> class Singleton : public Type
  {
  public:
    /// Get a unique instance of the Singleton.
    static Singleton* getInstance()
    {
      static Singleton* instance = new Singleton();
      return instance;
    }

  protected:
    /// Delete copy operators.
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
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

    /** \name Ctor & dtor.
     ** \{ */
  private:
    /// Construct an Int.
    Int() = default;
    /// Destroys an Int.
    ~Int() = default;
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

    /** \name Ctor & dtor.
     ** \{ */
  private:
    /// Construct a String.
    String() = default;
    /// Destroys a String.
    ~String() = default;
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

    /** \name Ctor & dtor.
     ** \{ */
  private:
    /// Construct Void type.
    Void() = default;
    /// Destroys Void type.
    ~Void() = default;
  };

} // namespace type
