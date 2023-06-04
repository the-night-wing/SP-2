/* p2c -- Pascal to C converter.
   Copyright (C) 2015  abhijit13@gmail.com Abhijit A.M..

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


%{
#include <stdio.h>
#include <string.h>
#include "data_struct.h"
#include "y.tab.h"
#include "prototype.h"

int line_no = 1;
%}

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]
NQUOTE [^']

%%

{A}{N}{D}   { MakeRetRec(AND);return(AND);}
{A}{R}{R}{A}{Y}   {MakeRetRec(ARRAY);return(ARRAY);}
{C}{A}{S}{E}   {MakeRetRec(CASE);return(CASE);}
{C}{O}{N}{S}{T}  {MakeRetRec(CONST); return(CONST);}
{D}{I}{V}   {MakeRetRec(DIV);return(DIV);}
{D}{O}    {MakeRetRec(DO);return(DO);}
{D}{O}{W}{N}{T}{O}  {MakeRetRec(DOWNTO);return(DOWNTO);}
{E}{L}{S}{E}  {MakeRetRec(ELSE); return(ELSE);}
{E}{N}{D}   {MakeRetRec(END);return(END);}
{E}{X}{T}{E}{R}{N} |
{E}{X}{T}{E}{R}{N}{A}{L} {MakeRetRec(EXTERNAL);return(EXTERNAL);}
{F}{O}{R}  {MakeRetRec(FOR); return(FOR);}
{F}{O}{R}{W}{A}{R}{D}  {MakeRetRec(FORWARD);return(FORWARD);}
{F}{U}{N}{C}{T}{I}{O}{N} {MakeRetRec(FUNCTION);return(FUNCTION);}
{G}{O}{T}{O}   {MakeRetRec(GOTO);return(GOTO);}
{I}{F}    {MakeRetRec(IF);return(IF);}
{I}{N}    {MakeRetRec(IN);return(IN);}
{L}{A}{B}{E}{L}   {MakeRetRec(LABEL);return LABEL;}
{M}{O}{D}  {MakeRetRec(MOD); return(MOD);}
{N}{I}{L}  {MakeRetRec(NIL); return(NIL);}
{N}{O}{T}   	{ 
		yytext[0]='!';	yytext[1]='\0'; 
		MakeRetRec(NOT);
		return(NOT);
		}
{O}{F}    {MakeRetRec(OF);return(OF);}
{O}{R}    { MakeRetRec(OR);return(OR);}
{O}{T}{H}{E}{R}{W}{I}{S}{E} {MakeRetRec(OTHERWISE);return(OTHERWISE);}
{P}{A}{C}{K}{E}{D}  {MakeRetRec(PACKED);return(PACKED);}
{B}{E}{G}{I}{N}   { MakeRetRec(_BEGIN);return(_BEGIN);}
{F}{I}{L}{E}   {MakeRetRec(_FILE);return(_FILE);}
{P}{R}{O}{C}{E}{D}{U}{R}{E} {MakeRetRec(PROCEDURE);return(PROCEDURE);}
{P}{R}{O}{G}{R}{A}{M} {MakeRetRec(PROGRAM); return(PROGRAM);}
{R}{E}{C}{O}{R}{D}  {MakeRetRec(RECORD);return(RECORD);}
{R}{E}{P}{E}{A}{T}  {MakeRetRec(REPEAT);return(REPEAT);}
{S}{E}{T}  {MakeRetRec(SET); return(SET);}
{T}{H}{E}{N}   {MakeRetRec(THEN);return(THEN);}
{T}{O}   { MakeRetRec(TO); return(TO);}
{T}{Y}{P}{E}   {MakeRetRec(TYPE);return(TYPE);}
{U}{N}{T}{I}{L}  {MakeRetRec(UNTIL); return(UNTIL);}
{V}{A}{R}  {MakeRetRec(VAR); return(VAR);}
{W}{H}{I}{L}{E}   {MakeRetRec(WHILE);return(WHILE);}
{W}{I}{T}{H}   {MakeRetRec(WITH);return(WITH);}
/*{N}{E}{W}	{MakeRetRec(NEW);return(NEW);}*/
/*{D}{E}{L}{E}{T}{E}	{MakeRetRec(DELETE);return (DELETE);}*/
		}
{F}{A}{L}{S}{E}		{MakeRetRec(FALSE);return FALSE;}
{T}{R}{U}{E}		{MakeRetRec(TRUE);return TRUE;}
[a-zA-Z_]([a-zA-Z0-9_])*  { 
		MakeRetRec(IDENTIFIER);
		return(IDENTIFIER);
		}

":="    	{
		MakeRetRec(ASSIGNMENT);
		return(ASSIGNMENT);
		}
'({NQUOTE}|'')*'  {  // because in C character string is in " "
		yytext[strlen(yytext)-1]='"';
		yytext[0]='"';
		MakeRetRec(CHARACTER_STRING);
		return(CHARACTER_STRING);
		}
":"   		{
		MakeRetRec(COLON);
		return(COLON);
		}

","    		{
		MakeRetRec(COMMA);
		return(COMMA);
		}
[0-9]+   	{
		MakeRetRec(DIGSEQ);
		return(DIGSEQ);
		}
"."   		{ 
		MakeRetRec(DOT);
		return(DOT);
		}
".."   		{
		MakeRetRec(DOTDOT);
		return(DOTDOT);
		}
"="		{
		MakeRetRec(EQUAL);
		return(EQUAL);
		}
">="   		{
		MakeRetRec(GE);
		return(GE);
		}
">"   		{
		MakeRetRec(GT);
		return(GT);
		}
"["  		{
		MakeRetRec(LBRAC);
		return(LBRAC);
		}
"<="		{
		MakeRetRec(LE);
		return(LE);
		}
"(" 		{
		MakeRetRec(LPAREN);
		return(LPAREN);
		}
"<" 		{
		MakeRetRec(LT);
		return(LT);
		}

"-"		{
		MakeRetRec(MINUS);
		return(MINUS);
		}

"<>"		{ 
		MakeRetRec(NOTEQUAL);
		return(NOTEQUAL);
		}
"+" 		{
		MakeRetRec(PLUS);
		return(PLUS);
		}
"]" 		{
		MakeRetRec(RBRAC);
		return(RBRAC);
		}
[0-9]+"."[0-9]+  {
		MakeRetRec(REALNUMBER);
		return(REALNUMBER);
		}
")"		{
		MakeRetRec(RPAREN);
		return(RPAREN);
		}
";"		{
		MakeRetRec(SEMICOLON);
		return(SEMICOLON);
		}
"/"		{   
		MakeRetRec(SLASH);
		return(SLASH);
		}

"*" 		{
		MakeRetRec(STAR);
		return(STAR);
		}
"**" 		{
		MakeRetRec(STARSTAR);
		return(STARSTAR);
		}
"->"   |
"^"    		{
		MakeRetRec(UPARROW);
		return(UPARROW);
		}
"(*"   |
"{"    { register int c;
     while ((c = input()))
     {
      if (c == '}')
       break;
      else if (c == '*')
      {
       if ((c = input()) == ')')
        break;
       else
        unput (c);
      }
      else if (c == '\n')
       line_no++;
      else if (c == 0)
       commenterror();
     }
    }

[ \t\f]    ;

\n    line_no++;

.    { fprintf (stderr,  "'%c' (0%o): illegal charcter at line %d\n",
     yytext[0], yytext[0], line_no);
    }

%%
int commenterror()
{
 fprintf (stderr, "unexpected EOF inside comment at line %d\n",  line_no);
 exit (1);
}

int yywrap ()
{
 return (1);
}
int MakeRetRec(int ret_val)
{
	yylval.stackptr=(YaccRetptr)malloc(sizeof(YaccRettype));
        yylval.stackptr->lexeme=malloc(strlen(yytext)+1);
        strcpy(yylval.stackptr->lexeme,yytext);
	yylval.stackptr->type=ret_val;
}
