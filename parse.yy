%language "C++"
%require "3.0"
%define api.value.type variant
/*%define api.token.prefix {TOK_}*/
%define api.token.constructor
%define locations
%define filename_type {const std::string}
%expect 0
%defines
%right ELSE THEN
%left OR
%left AND
%left SUP_EQ INF_EQ EQUAL SUP INF DIF
%left PLUS MINUS
%left MUL DIV
%left LPAR RPAR

%token
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
                LETTER      "LETTER"
                DIGIT       "DIGIT"
                STRING      "STRING"
                UNDER_S     "_"
%start program

%%

program :
    exp
    { $$ = $1 }
  | decs
    { $$ = $1 }

sev_choices :
    LETTER
    { $$ = $LETTER }
  | DIGIT
    { $$ = $DIGIT }
  | UNDER_S
    { $$ = $1 }
  | LETTER sev_choices
    { $$ = $LETTER $2}
  | DIGIT sev_choices
    { $$ = $DIGIT $2}
  | UNDER_S sev_choices
    { $$ = $UNDER_S $2}

id :
    LETTER
    { $$ = $LETTER }
  | LETTER sev_choices
    { $$ = $LETTER $2}

id_exp:
    id EQUAL exp
    { $$ = $1 $EQUAL $3 }
  | id EQUAL exp COMMA id_exp
    { $$ = $1 $EQUAL $3 $COMMA $5 }

digits:

  | DIGIT digits
    { $$ = $DIGIT $2 }

integer :
    DIGIT digits
    { $$ = $DIGIT $2 }


exp2:
    exp
    { $$ = $1 }
  | exp COMMA exp2
    { $$ = $1 $COMMA $3 }

exp :
    NIL
    { $$ = $NIL }
  | integer
    { $$ = $1 }
  | STRING
    { $$ = $1 }

/* Array and record creations. */
  | type-id LBRACK exp RBRACK OF exp
    { $$ = $1 $LBRACK $3 $RBRACK $OF $6 }
  | type-id LBRACE RBRACE
    { $$ = $1 $LBRACE $RBRACE }
  | type-id LBRACE id_exp RBRACE
    { $$ = $1 $LBRACE $3 $RBRACE }

/* Object creation. */
  | NEW type-id
  { $$ = $NEW $2 }

/* Variables, field, elements of an array. */
  | lvalue
    { $$ = $1 }

/* Function call. */
  | id LPAR RPAR
    { $$ = $1 $LPAR $RPAR }
  | id LPAR exp2 RPAR
    { $$ = $1 $LPAR $3 $RPAR }

/* Method call. */
  | lvalue DOT id LPAR RPAR
    { $$ = $1 $DOT $3 $LPAR $RPAR }
  | lvalue DOT id LPAR exp2 RPAR
    { $$ = $1 $DOT $3 $LPAR $5 $RPAR }

/* Operations. */
  | MINUS exp
    { $$ = - $2 }
  | exp op exp
    { $$ = $1 $2 $3 }
  | LPAR exps RPAR
    { $$ = $LPAR $2 $RPAR }

/* Assignment. */
  | lvalue ASSIGN exp
    { $$ = $1 $ASSIGN $3 }

/* Control structures. */
  | IF exp THEN exp
    { $$ = $IF $2 $THEN $4 }
  | IF exp THEN exp ELSE exp
    { $$ = $IF $2 $THEN $4 $ELSE $6 }
  | WHILE exp DO exp
    { $$ = $WHILE $2 $DO $4 }
  | FOR id ASSIGN exp TO exp DO exp
    { $$ = $FOR $2 $ASSIGN $4 $TO $6 $DO $8 }
  | BREAK
    { $$ = $BREAK }
  | LET decs IN exps END
    { $$ = $LET $2 $IN $4 $END }

lvalue :
    id
    { $$ = s1 }
  | lvalue DOT id
    { $$ = $1 $DOT $3 }
  | lvalue LBRACK exp RBRACK
    { $$ = $1 $LBRACK $3 $RBRACK}

exp3:
    exp
    { $$ = s1 }
  | exp SEMICOLON exp3
    { $$ = s1 $SEMICOLON $3 }

exps :

  | exp3
    { $$ = s1 }

decs :

  | dec decs
    { $$ = s1 $2 }

dec :
/* Type declaration. */
    TYPE id EQUAL ty
    { $$ = $TYPE $2 $EQUAL $4 }
/* Class definition (alternative form). */
  | CLASS id LBRACE classfields RBRACE
    { $$ = $CLASS $2 $LBRACE $4 $RBRACE }
  | CLASS id EXTENDS type-id LBRACE classfields RBRACE
    { $$ = $CLASS $2 $EXTENDS $4 $LBRACE $6 $RBRACE }
/* Variable declaration. */
  | vardec
    { $$ = $1; }
/* Function declaration. */
  | FUNCTION id LPAR tyfields RPAR EQUAL exp
    { $$ = sFUNCTION $2 $LPAR $4 $RPAR $EQUAL $7 }
  | FUNCTION id LPAR tyfields RPAR COLON type-id EQUAL exp
    { $$ = sFUNCTION $2 $LPAR $4 $RPAR $COLON $7 $EQUAL $9 }
/* Primitive declaration. */
  | PRIMITIVE id LPAR tyfields RPAR
    { $$ = sPRIMITIVE $2 $LPAR $4 $RPAR }
  | PRIMITIVE id LPAR tyfields RPAR COLON type-id
    { $$ = sPRIMITIVE $2 $LPAR $4 $RPAR $COLON $7 }
/* Importing a set of declarations. */
  | IMPORT STRING
    { $$ = $IMPORT $STRING}

vardec :
    VAR id ASSIGN exp
    {$$ = $VAR $2 $ASSIGN $4}
  | VAR id COLON type-id ASSIGN exp
    {$$ = $VAR $2 $COLON $4 $ASSIGN $6 }

classfields :

  | classfield classfields
    {$$ = $1 $2}

/* Class fields. */
classfield :
/* Attribute declaration. */
    vardec
    { $$ = $1}
/* Method declaration. */
  | METHOD id LPAR tyfields RPAR EQUAL exp
    { $$ = $METHOD $2 $LPAR $4 $RPAR $EQUAL $7}
  | METHOD id LPAR tyfields RPAR COLON type-id EQUAL exp
    { $$ = $METHOD $2 $LPAR $4 $RPAR $COLON $7 $EQUAL $9}

/* Types. */
ty :
/* Type alias. */
    type-id
    { $$ = $1}
/*  Record type definition. */
  | LBRACE tyfields RBRACE
    { $$ = $LBRACE $2 $RBRACE}
/* Array type definition. */
  | ARRAY OF type-id
    { $$ = $ARRAY $OF $3}
/* Class definition (canonical form). */
  | CLASS LBRACE classfields RBRACE
    { $$ = $CLASS $LBRACE $3 $RBRACE}
  | CLASS EXTENDS type-id LBRACE classfields RBRACE
    { $$ = $CLASS $EXTENDS $3 $LBRACE $5 $RBRACE}

id_comma:

  | COMMA id COLON type-id id_comma
    { $$ = $COMMA $2 $COLON $4 $5}

tyfields :

  | id COLON type-id id_comma
    { $$ = $1 $COLON $3 $4}

type-id :
    id
    { $$ = $1}

op:
    MUL
    { $$ = *}
  | DIV
    { $$ = /}
  | PLUS
    { $$ = +}
  | MINUS
    { $$ = -}
  | INF_EQ
    { $$ = <=}
  | SUP_EQ
    { $$ = >=}
  | EQUAL
    { $$ = =}
  | DIF
    { $$ = <>}
  | INF
    { $$ = <}
  | SUP
    { $$ = >}
  | AND
    { $$ = &}
  | OR
    { $$ = |}

%%
/* Part 3 */

int main()
{
    yylex();
    return 0;
}
