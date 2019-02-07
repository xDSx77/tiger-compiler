%language "C++"
%require "3.0"
%define api.value.type variant
/*%define api.token.prefix {TOK_}*/
%define api.token.constructor
%define locations
%define filename_type {const std::string}
%expect 0
%defines

%token          NEWLINE     "\n"
                NIL         "nil"
                NEW         "new"
                OF          "of"
                IF          "if"
                THEN        "then"
                ELSE        "else"
                WHILE       "while"
                DO          "do"
                FOR         "for"
                TO          "to"
                BREAK       "break"
                LET         "let"
                IN          "in"
                END         "end"
                ASSIGN      ":="
                TYPE        "type"
                CLASS       "class"
                EXTENDS     "extends"
                FUNCTION    "function"
                IMPORT      "import"
                PRIMITIVE   "primitive"
                VAR         "var"
                METHOD      "method"
                ARRAY       "array"
                DOT         "."
                COMMA       ","
                COLON       ":"
                SEMICOLON   ";"
                MUL         "*"
                DIV         "/"
                PLUS        "+"
                MINUS       "-"
                LPAR        "("
                RPAR        ")"
                LBRACK      "["
                RBRACK      "]"
                LBRACE      "{"
                RBRACE      "}"
                SUP_EQ      ">="
                INF_EQ      "<="
                EQUAL       "="
                DIF         "<>"
                INF         "<"
                SUP         ">"
                AND         "&"
                OR          "|"

%start program

%%

program :
    exp
    { $$ = $1; }
  | decs
    { $$ = $1; }

id_exp:
    id EQUAL exp
    
  | id EQUAL exp COMMA id_exp
    

exp2:
    exp
    
  | exp COMMA exp2
    

exp :
    NIL
    { $$ = $1; }
  | integer
    { $$ = $1; }
  | string
    { $$ = $1; }

/* Array and record creations. */
  | type-id LBRACK exp RBRACK of exp
    { $$ = $1; }
  | type-id LBRACE RBRACE
    { $$ = $1; }
  | type-id LBRACE id_exp RBRACE
    

/* Object creation. */
  | NEW type-id
  { $$ = $1; }

/* Variables, field, elements of an array. */
  | lvalue
    { $$ = $1; }

/* Function call. */
  | id LPAR RPAR
    { $$ = $1; }
  | id LPAR exp2 RPAR
    

/* Method call. */
  | lvalue DOT id LPAR RPAR
    { $$ = $1; }
  | lvalue DOT id LPAR exp2 RPAR
    

/* Operations. */
  | MINUS exp
    { $$ = $1; }
  | exp op exp
    { $$ = $1; }
  | LPAR exps RPAR
    { $$ = $1; }

/* Assignment. */
  | lvalue ASSIGN exp
    { $$ = $1; }

/* Control structures. */
  | IF exp THEN exp
    { $$ = $1; }
  | IF exp THEN exp ELSE exp
    
  | WHILE exp DO exp
    { $$ = $1; }
  | FOR id ASSIGN exp TO exp DO exp
    { $$ = $1; }
  | BREAK
    { $$ = $1; }
  | LET decs IN exps END
    { $$ = $1; }

lvalue :
    id
    
  | lvalue DOT id
    { $$ = $1; }
  | lvalue LBRACK exp RBRACK
    { $$ = $1; }

exp3:
    exp
    
  | exp SEMICOLON exp3
    

exps :

  | exp3
    

decs :

  | dec decs
    

dec :
/* Type declaration. */
    TYPE id EQUAL ty
    { $$ = $1; }
/* Class definition (alternative form). */
  | CLASS id LBRACE classfields RBRACE
    { $$ = $1; }
  | CLASS id EXTENDS type-id LBRACE classfields RBRACE
    { $$ = $1; }
/* Variable declaration. */
  | vardec
    { $$ = $1; }
/* Function declaration. */
  | FUNCTION id LPAR tyfields RPAR EQUAL exp
    { $$ = s1; }
  | FUNCTION id LPAR tyfields RPAR COLON type_id EQUAL exp
    
/* Primitive declaration. */
  | PRIMITIVE id LPAR tyfields RPAR
    
  | PRIMITIVE id LPAR tyfields RPAR COLON type-id
    
/* Importing a set of declarations. */
  | IMPORT string
    

vardec :
    VAR id ASSIGN exp
    
  | VAR id COLON type-id ASSIGN exp
    

classfields :

  | classfield classfields
    

/* Class fields. */
classfield :
/* Attribute declaration. */
    vardec
    
/* Method declaration. */
  | METHOD id LPAR tyfields RPAR EQUAL exp
    
  | METHOD id LPAR tyfields RPAR COLON type_id EQUAL exp
    

/* Types. */
ty :
/* Type alias. */
    type-id
    
/*  Record type definition. */
  | LBRACE tyfields RBRACE
    
/* Array type definition. */
  | ARRAY OF type-id
    
/* Class definition (canonical form). */
  | CLASS LBRACE classfields RBRACE
    
  | CLASS EXTENDS type-id LBRACE classfields RBRACE
    

id_comma:

  | COMMA id COLON type-id id_comma
    

tyfields :

  | id COLON type-id id_comma
    

type-id :
    id
    

op:
    MUL
    
  | DIV
    
  | PLUS
    
  | MINUS
    
  | INF_EQ
    
  | SUQ_EQ
    
  | EQUAL
    
  | DIF
    
  | INF
    
  | SUP
    
  | AND
    
  | OR
    

%%
/* Part 3 */

