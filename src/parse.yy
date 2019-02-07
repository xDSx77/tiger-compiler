/* Part 1 */

%language "C++"
%define api.value.type variant
//%define api.token.prefix {TOK_}
%define api.token.constructor
%define locations
%define filename_type {const std::string}

%expect 0
%defines
%param {bistro::parser::ParseDriver& p}

%token          EXPR        "exp"
                NEWLINE     "\n"
                DECS        "decs"
                ID          "id"
                NIL         "nil"
                LVALUE      "lvalue"
                EXPRS       "exps"
                TYPE-ID     "type-id"
                TY          "ty"
                CLASSDIELD  "classfield"
                VARDEC      "vardec"
                TYFIELDS    "tyfields"
                STRING      "string"
                OP          "op"
                MUL         "*"
                DIV         "/"
                PLUS        "+"
                MINUS       "-"
                SUP_EQ      ">="
                INF_EQ      "<="
                EQUAL       "="
                DIF         "<>"
                INF         "<"
                SUP         ">"
                AND         "&"
                PIPE        "|"

%%
/* Part 2 */

program :
    exp
    {$$ = $exp}
  | decs
    {$$ = $decs}

exp :
    nil
    {$$ = $nil}
  | integer
    {$$ = $integer}
  | string
    {$$ = $string}

/* Array and record creations. */
    type-id [ exp ] of exp
    {$$ = $1 [ $2 ] $3}
    type-id {[ id = exp { , id = exp } ] }
    {$$ = $1 {[ $2 = $3 { , $2 = $3} ] } }

/* Object creation. */
  | new type-id
  {$$ = $type-id}

/* Variables, field, elements of an array. */
  | lvalue
  {$$ = $lvalue}

/* Function call. */
  | id ( [ exp { , exp }] )
  {$$ = $1 ( [ $2 { , $2 } ] ) }

/* Method call. */
  | lvalue . id ( [ exp { , exp }] )
  {$$ = $1 . $2 ( [ $3 { , $3 } ] ) }

/* Operations. */
  | - exp
  {$$ = - $exp}
  | exp op exp
  {$$ = $exp op $exp}
  | ( exps )
  {$$ = ($exps) }

/* Assignment. */
  | lvalue := exp
  {$$ = $exp}

/* Control structures. */
  | if exp then exp [else exp]
  {$$ = if $exp then $exp [else $exp] }
  | while exp do exp
  {$$ = while $1 do $2 }
  | for id := exp to exp do exp
  {$$ = for $1 = $2 to $3 do $4}
  | break
  {$$ = $break}
  | let decs in exps end
  {$$ = let $1 in $2 end}

lvalue ::= id
  | lvalue . id
  {$$ = $lavlue . $id}
  | lvalue [ exp ]
  {$$ = $exp}
exps ::= [ exp { ; exp } ]
{$$ = $exp {; $exp} }

decs ::= { dec }
     {$$ = $dec}
dec ::=
/* Type declaration. */
    type id = ty
    {$$ = $ty}
/* Class definition (alternative form). */
  | class id [ extends type-id ] { classfields }
  {$$ = $type-id {$classfields}}
/* Variable declaration. */
  | vardec
  {$$ = $vardec}
/* Function declaration. */
  | function id ( tyfields ) [ : type-id ] = exp
  {$$ = }
/* Primitive declaration. */
  | primitive id ( tyfields ) [ : type-id ]
/* Importing a set of declarations. */
  | import string

vardec ::= var id [ : type-id ] := exp

classfields ::= { classfield }
/* Class fields. */
classfield ::=
/* Attribute declaration. */
    vardec
/* Method declaration. */
  | method id ( tyfields ) [ : type-id ] = exp

/* Types. */
ty ::=
/* Type alias. */
     type-id
/*  Record type definition. */
   | { tyfields  }
/* Array type definition. */
   | array of type-id
/* Class definition (canonical form). */
   | class [ extends type-id ] { classfields }
tyfields ::= [ id : type-id { , id : type-id } ]
type-id ::= id


%%
/* Part 3 */

