/**
 ** \file astclone/cloner.cc
 ** \brief Implementation of astclone::Cloner.
 */

#include <ast/all.hh>
#include <astclone/cloner.hh>
#include <misc/symbol.hh>

namespace astclone
{

  using namespace ast;

  Cloner::Cloner()
    : result_(nullptr)
  {}

  Ast*
  Cloner::result_get()
  {
    return result_;
  }

  void
  Cloner::operator()(const ast::ArrayExp& e)
  {
    const Location& location = e.location_get();
    NameTy* name_ty = recurse(e.name_ty_get());
    Exp* size = recurse(e.size_get());
    Exp* value = recurse(e.value_get());
    result_ = new ArrayExp(location, name_ty, size, value);
  }

  void
  Cloner::operator()(const ast::ArrayTy& e)
  {
    const Location& location = e.location_get();
    NameTy* base_type = recurse(e.base_type_get());
    result_ = new ArrayTy(location, base_type);
  }

  void
  Cloner::operator()(const ast::AssignExp& e)
  {
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    Exp* exp = recurse(e.exp_get());
    result_ = new AssignExp(location, var, exp);
  }

  void
  Cloner::operator()(const ast::BreakExp& e)
  {
    const Location& location = e.location_get();
    result_ = new BreakExp(location);
  }

  void
  Cloner::operator()(const ast::CallExp& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    exps_type* exps = recurse_collection(e.exps_get());
    result_ = new CallExp(location, name, exps);

  }

  void
  Cloner::operator()(const ast::CastExp& e)
  {
    const Location& location = e.location_get();
    Exp* exp = recurse(e.exp_get());
    Ty* ty = recurse(e.ty_get());
    result_ = new CastExp(location, exp, ty);
  }

  void
  Cloner::operator()(const ast::CastVar& e)
  {
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    Ty* ty = recurse(e.ty_get());
    result_ = new CastVar(location, var, ty);
  }

  void
  Cloner::operator()(const ast::ClassTy& e)
  {
    const Location& location = e.location_get();
    NameTy* super = recurse(e.super_get());
    DecsList* decs = recurse(e.decs_get());
    result_ = new ClassTy(location, super, decs);
  }

  void
  Cloner::operator()(const ast::DecsList& e)
  {
    const Location& location = e.location_get();
    DecsList::decs_type decs = *recurse_collection(e.decs_get());
    result_ = new DecsList(location, decs);
  }

  void
  Cloner::operator()(const ast::Field& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    NameTy* type_name = recurse(e.type_name_get());
    result_ = new Field(location, name, type_name);
  }

  void
  Cloner::operator()(const ast::FieldInit& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    Exp* init = recurse(e.init_get());
    result_ = new FieldInit(location, name, init);
  }

  void
  Cloner::operator()(const ast::FieldVar& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    Var* var = recurse(e.var_get());
    result_ = new FieldVar(location, name, var);
  }

  void
  Cloner::operator()(const ast::ForExp& e)
  {
    const Location& location = e.location_get();
    VarDec* vardec = recurse(e.vardec_get());
    Exp* hi = recurse(e.hi_get());
    Exp* body = recurse(e.body_get());
    result_ = new ForExp(location, vardec, hi, body);
  }

  void
  Cloner::operator()(const ast::FunctionDec& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    VarDecs* formals = recurse(e.formals_get());
    NameTy* result = recurse(e.result_get());
    Exp* body = recurse(e.body_get());
    auto fundec = new FunctionDec(location, name, formals, result, body);
    result_ = fundec;
  }

  void
  Cloner::operator()(const ast::IfExp& e)
  {
    const Location& location = e.location_get();
    Exp* test = recurse(e.test_get());
    Exp* body = recurse(e.body_get());
    Exp* body_2 = recurse(e.body_2_get());
    result_ = new IfExp(location, test, body, body_2);
  }

  void
  Cloner::operator()(const ast::IntExp& e)
  {
    const Location& location = e.location_get();
    int value = e.value_get();
    result_ = new IntExp(location, value);
  }

  void
  Cloner::operator()(const ast::LetExp& e)
  {
    const Location& location = e.location_get();
    DecsList* decs = recurse(e.decs_get());
    Exp* exp = recurse(e.exp_get());
    result_ = new LetExp(location, decs, exp);
  }

  void
  Cloner::operator()(const ast::MethodCallExp& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    exps_type* exps = recurse_collection(e.exps_get());
    Var* var = recurse(e.var_get());
    result_ = new MethodCallExp(location, name, exps, var);
  }

  void
  Cloner::operator()(const ast::MethodDec& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    VarDecs* formals = recurse(e.formals_get());
    NameTy* result = recurse(e.result_get());
    Exp* body = recurse(e.body_get());
    result_ = new MethodDec(location, name, formals, result, body);
  }

  void
  Cloner::operator()(const ast::NameTy& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    result_ = new NameTy(location, name);
  }

  void
  Cloner::operator()(const ast::NilExp& e)
  {
    const Location& location = e.location_get();
    result_ = new NilExp(location);
  }

  void
  Cloner::operator()(const ast::ObjectExp& e)
  {
    const Location& location = e.location_get();
    NameTy* type = recurse(e.type_get());
    result_ = new ObjectExp(location, type);
  }

  void
  Cloner::operator()(const ast::OpExp& e)
  {
    const Location& location = e.location_get();
    Exp* left = recurse(e.left_get());
    OpExp::Oper oper = e.oper_get();
    Exp* right = recurse(e.right_get());
    result_ = new OpExp(location, left, oper, right);
  }

  void
  Cloner::operator()(const ast::RecordExp& e)
  {
    const Location& location = e.location_get();
    NameTy* name_ty = recurse(e.name_ty_get());
    fieldinits_type fieldinits = e.fieldinits_get();
    result_ = new RecordExp(location, name_ty, fieldinits);
  }

  void
  Cloner::operator()(const ast::RecordTy& e)
  {
    const Location& location = e.location_get();
    fields_type fields = e.fields_get();
    result_ = new RecordTy(location, fields);
  }

  void
  Cloner::operator()(const ast::SeqExp& e)
  {
    const Location& location = e.location_get();
    exps_type* exps = recurse_collection(e.exps_get());
    result_ = new SeqExp(location, exps);
  }

  void
  Cloner::operator()(const ast::SimpleVar& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    result_ = new SimpleVar(location, name);
  }

  void
  Cloner::operator()(const ast::StringExp& e)
  {
    const Location& location = e.location_get();
    std::string s = e.value_get();
    result_ = new StringExp(location, s);
  }

  void
  Cloner::operator()(const ast::SubscriptVar& e)
  {
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    Exp* index = recurse(e.index_get());
    result_ = new SubscriptVar(location, var, index);
  }

  void
  Cloner::operator()(const ast::TypeDec& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    Ty* ty = recurse(e.ty_get());
    result_ = new TypeDec(location, name, ty);
  }

  void
  Cloner::operator()(const ast::VarDec& e)
  {
    const Location& location = e.location_get();
    const misc::symbol& name = e.name_get();
    NameTy* type_name = recurse(e.type_name_get());
    Exp* init = recurse(e.init_get());
    result_ = new VarDec(location, name, type_name, init);
  }

  void
  Cloner::operator()(const ast::WhileExp& e)
  {
    const Location& location = e.location_get();
    Exp* test = recurse(e.test_get());
    Exp* body = recurse(e.body_get());
    result_ = new WhileExp(location, test, body);
  }


  void
  Cloner::operator()(const ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDecs>(e);
  }

  void
  Cloner::operator()(const ast::MethodDecs& e)
  {
    decs_visit<ast::MethodDecs>(e);
  }

  void
  Cloner::operator()(const ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDecs>(e);
  }

  void
  Cloner::operator()(const ast::VarDecs& e)
  {
    decs_visit<ast::VarDecs>(e);
  }

} // namespace astclone
