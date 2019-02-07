%option debug nounput noyywrap

%{
#include <iostream>
#include <fstream>
#define TOKEN(Type)
  yy::parser::make_

%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
STRING      "\""[a-zA-Z0-9]*"\""

%%
<<EOF>> yyterminate();
"if"        return TOKEN(IF);
"\n"        return TOKEN(NEWLINE);
"nil"       return TOKEN(NIL);
"then"      return TOKEN(THEN);
"else"      return TOKEN(ELSE);
"while"     return TOKEN(WHILE);
"do"        return TOKEN(DO);
"for"       return TOKEN(FOR);
"to"        return TOKEN(TO);
"break"     return TOKEN(BREAK);
"let"       return TOKEN(LET);
"in"        return TOKEN(IN);
"end"       return TOKEN(END);
"assign"    return TOKEN(ASSIGN);
"type"      return TOKEN(TYPE);
"class"     return TOKEN(CLASS);
"extends"   return TOKEN(EXTENDS);
"function"  return TOKEN(FUNCTION);
"import"    return TOKEN(IMPORT);
"primitive" return TOKEN(PRIMITIVE);
"var"       return TOKEN(VAR);
"method"    return TOKEN(METHOD);
"array"     return TOKEN(ARRAY);
"."         return TOKEN(DOT);
","         return TOKEN(COMMA);
":"         return TOKEN(COLON);
";"         return TOKEN(SEMICOLON);
"*"         return TOKEN(MUL);
"/"         return TOKEN(DIV);
"+"         return TOKEN(PLUS);
"-"         return TOKEN(MINUS);
"("         return TOKEN(LPAR);
")"         return TOKEN(RPAR);
"["         return TOKEN(LBRACK);
"]"         return TOKEN(RBRACK);
"{"         return TOKEN(LBRACE);
"}"         return TOKEN(RBRACE);
">="        return TOKEN(SUP_EQ);
"<="        return TOKEN(INF_EQ);
"="         return TOKEN(EQUAL);
"<>"        return TOKEN(DIF);
"<"         return TOKEN(INF);
">"         return TOKEN(SUP);
"&"         return TOKEN(AND);
"|"         return TOKEN(OR);

{LETTER}    return TOKEN(LETTER);
{DIGIT}     return TOKEN(DIGIT);
{STRING}    return TOKEN(DIGIT);

%%
