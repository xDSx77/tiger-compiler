* README

Tiger Abstract Syntax Tree nodes with their principal members.
Incomplete classes are tagged with a `*'.

/Ast/               (Location location)
  /Dec/             (symbol name)
    FunctionDec     (VarDecs formals, NameTy result, Exp body)
      MethodDec     ()
    TypeDec         (Ty ty)
    VarDec          (NameTy type_name, Exp init)

  /Exp/             ()
    /Var/           ()
      CastVar       (Var var, Ty ty)
*     FieldVar      (Var var, symbol name)
      SimpleVar     (symbol name)
      SubscriptVar  (Var var, Exp index)

*   ArrayExp        (Exp exp, NameTy type)
*   AssignExp       (Exp exp, Var var)
*   BreakExp        (Exp exp)
*   CallExp         (Exp body, FunctionDec dec, symbol name)
*     MethodCallExp (Var var, MethodDec method)
    CastExp         (Exp exp, Ty ty)
    ForExp          (VarDec vardec, Exp hi, Exp body)
*   IfExp           (Exp test, Exp body, Exp body_2)
    IntExp          (int value)
*   LetExp          (DecsList decs, Exp body)
    NilExp          ()
*   ObjectExp       (Exp exp, NameTy type)
    OpExp           (Exp left, Oper oper, Exp right)
*   RecordExp       (NameTy type, FieldInit field)
*   SeqExp          (Exp exp)
*   StringExp       (string s)
    WhileExp        (Exp test, Exp body)

  /Ty/              ()
    ArrayTy         (NameTy base_type)
    ClassTy         (NameTy super, DecsList decs)
    NameTy          (symbol name)
*   RecordTy        (Field field, Ty ty)

  DecsList          (decs_type decs)

  Field             (symbol name, NameTy type_name)

  FieldInit         (symbol name, Exp init)


