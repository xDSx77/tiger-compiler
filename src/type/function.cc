/**
 ** \file type/function.cc
 ** \brief Implementation for type/function.hh.
 */

#include <ostream>

#include <type/function.hh>
#include <type/visitor.hh>

namespace type
{

  Function::Function(const Record* formals, const Type& result)
    : result_(result)
  {
    precondition(formals);

    formals_ = formals;
  }

  Function::~Function()
  {
    delete formals_;
  }

  void
  Function::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Function::accept(Visitor& v)
  {
    v(*this);
  }

  bool
  Function::compatible_with(const Type& other) const
  {
    if (*this != other)
      return false;
    const Function& f2 = dynamic_cast<const Function&>(other);
    if (formals_ != nullptr && f2.formals_ != nullptr)
    {
      if (formals_->fields_get().size() != f2.formals_get().fields_get().size())
        return false;
      for (long unsigned int i = 0; i < formals_->fields_get().size(); i++)
      {
        if (!(formals_->field_type(formals_->fields_get()[i].name_get())->compatible_with(*f2.formals_get().field_type(f2.formals_get().fields_get()[i].name_get()))))
          return false;
      }
    }
    if (result_ != f2.result_)
      return false;
    return true;
  }

} // namespace type
