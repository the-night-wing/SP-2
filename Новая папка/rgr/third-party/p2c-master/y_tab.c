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


#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "pas.y"
#include <stdio.h>
#include <stdarg.h>
#include "prototype.h"
#include "data_struct.h"

int func_level=0;
Funptr tempfun;
Typeptr temptype;
Argptr temparg;
Idptr tempid;
int BLOCK_IS_FUNC_FLAG=0;

extern int line_no;
extern Funptr symtab,currfun;
extern int indent;
extern Type basic_types[4];
#define free(args) ;
/*#undef getchar*/
#line 21 "pas.y"
typedef union {
   YaccRetptr stackptr;
   Typeptr typeptr;	
   Varptr  varptr;
    Idptr idptr;
    Constptr constptr;
   void *voidptr;
   Argptr argptr;
   Typecheckptr chkptr;
} YYSTYPE;
#line 42 "y.tab.c"
#define AND 257
#define ARRAY 258
#define ASSIGNMENT 259
#define CASE 260
#define CHARACTER_STRING 261
#define COLON 262
#define COMMA 263
#define CONST 264
#define DIGSEQ 265
#define DIV 266
#define DO 267
#define DOT 268
#define DOTDOT 269
#define DOWNTO 270
#define ELSE 271
#define END 272
#define EQUAL 273
#define EXTERNAL 274
#define FOR 275
#define FORWARD 276
#define FUNCTION 277
#define GE 278
#define GOTO 279
#define GT 280
#define IDENTIFIER 281
#define IF 282
#define IN 283
#define LABEL 284
#define LBRAC 285
#define LE 286
#define LPAREN 287
#define LT 288
#define MINUS 289
#define MOD 290
#define NIL 291
#define NOT 292
#define NOTEQUAL 293
#define OF 294
#define OR 295
#define OTHERWISE 296
#define PACKED 297
#define _BEGIN 298
#define _FILE 299
#define PLUS 300
#define PROCEDURE 301
#define PROGRAM 302
#define RBRAC 303
#define REALNUMBER 304
#define RECORD 305
#define REPEAT 306
#define RPAREN 307
#define SEMICOLON 308
#define SET 309
#define SLASH 310
#define STAR 311
#define STARSTAR 312
#define THEN 313
#define TO 314
#define TYPE 315
#define UNTIL 316
#define UPARROW 317
#define VAR 318
#define WHILE 319
#define WITH 320
#define NEW 321
#define DELETE 322
#define TRUE 323
#define FALSE 324
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,  125,   12,   12,   13,   13,   86,   86,  126,
  127,  129,  130,  131,   14,   15,   16,   16,   17,   17,
   18,   85,   85,   72,   72,   73,   76,   76,   77,   77,
   78,   78,   79,   79,   80,   80,   81,   81,   81,   81,
   82,   82,   82,    6,    6,    7,    7,    7,  100,  100,
   87,   87,   88,   89,   89,  101,  101,  101,   90,   90,
   91,   92,   93,   93,   94,   94,   94,   94,   95,  111,
  111,  112,   96,   96,   99,   98,   98,   98,  114,  114,
  115,  102,  102,  102,  103,  103,  104,  104,  105,  105,
  105,   75,   75,   74,   74,  106,  107,  108,  109,  110,
   97,   10,  128,  128,  117,  117,  116,   19,   19,   20,
   20,   21,   21,   22,   22,   23,   23,  132,   25,   24,
   24,  118,  119,  119,  120,  120,  120,  120,  121,  122,
  123,  124,   26,   27,   27,   28,  133,   28,  113,   29,
   30,  134,   31,   32,   32,   64,   64,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   65,   65,  135,  136,
   66,  137,   67,  138,   68,   69,   70,  141,  139,  142,
  140,  140,   63,   43,   43,   43,   43,   44,   45,   45,
   46,   47,   71,   71,   62,   59,   59,   40,   40,   40,
   33,   34,  143,  144,  144,  145,  144,   42,   35,   35,
  146,   36,   37,   37,   41,   50,   11,   11,   51,   38,
   38,   48,   49,   49,   52,   52,   53,   53,   54,   54,
   55,   55,   56,   56,   56,   56,   56,   56,   56,   56,
   56,   83,   83,   84,   84,    8,    9,   57,   57,   58,
   58,   60,   60,   61,   61,   39,   39,   39,    1,    1,
    1,    1,    1,    2,    2,    2,    2,    2,    2,    2,
    3,    4,    5,
};
short yylen[] = {                                         2,
    1,    1,    0,    5,    2,    2,    5,    3,    1,    0,
    0,    0,    0,    0,   11,    4,    3,    0,    3,    1,
    1,    2,    0,    2,    1,    4,    1,    3,    1,    3,
    1,    3,    2,    1,    1,    3,    1,    3,    1,    2,
    1,    2,    1,    1,    1,    1,    1,    1,    2,    0,
    2,    1,    4,    1,    1,    1,    1,    1,    1,    1,
    3,    3,    1,    2,    1,    1,    1,    1,    6,    3,
    1,    1,    1,    1,    1,    3,    5,    3,    3,    1,
    3,    5,    4,    0,    3,    1,    3,    1,    5,    7,
    5,    3,    1,    1,    3,    1,    1,    3,    1,    3,
    2,    1,    3,    0,    3,    1,    3,    2,    0,    3,
    1,    1,    1,    3,    3,    1,    2,    0,    3,    1,
    1,    3,    3,    1,    1,    1,    1,    1,    3,    4,
    1,    1,    1,    3,    3,    4,    0,    6,    1,    1,
    1,    0,    4,    3,    1,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    0,    0,    0,
    6,    0,    5,    0,    9,    4,    2,    0,    5,    0,
    3,    0,    3,    1,    1,    1,    2,    4,    3,    1,
    1,    3,    2,    1,    3,    3,    1,    1,    3,    5,
    2,    2,    3,    2,    3,    0,    6,    1,    3,    1,
    0,    4,    1,    2,    1,    1,    1,    1,    1,    3,
    1,    1,    1,    3,    1,    3,    1,    3,    2,    1,
    1,    3,    1,    1,    1,    1,    3,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    3,    3,
    2,    3,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    1,    0,    0,    2,   10,    0,
  261,    0,    0,   25,   21,    0,   20,    0,  262,    3,
    5,    0,    0,    0,    0,   24,  263,   17,    0,    0,
    0,   11,    0,    0,   52,    0,    0,  233,  236,    0,
   45,    0,   44,  237,   37,    0,  234,  235,    0,    0,
    0,   31,   34,    0,   39,  232,   19,    9,    0,    0,
    0,    0,   51,    0,  106,    0,    0,  118,   16,    0,
  111,  112,    0,    0,  113,    0,    0,   40,   33,   26,
  254,  259,  257,  260,  258,  256,  247,  255,  248,  246,
    0,    0,  253,  251,  252,  250,  249,    0,    0,    7,
    0,    4,   12,    0,   43,   46,    0,    0,    0,   48,
    0,    0,    0,    0,    0,   41,    0,    0,   56,   59,
   60,   57,   63,   65,   58,   66,   54,   67,   68,    0,
    0,    0,    0,    0,    0,    0,  117,    0,   38,    0,
    0,   32,   36,    8,    0,    0,    0,   64,    0,    0,
    0,    0,    0,   80,    0,  102,  101,   47,   42,    0,
   53,  107,  105,    0,    0,  119,  110,  121,  120,  133,
  114,  115,    0,  131,  132,    0,    0,  124,  125,  126,
  127,  128,  140,  134,  135,   13,    0,   73,   72,    0,
   71,   61,   75,  100,    0,    0,    0,   86,    0,   78,
   76,    0,   99,   98,   62,  139,  136,    0,    0,    0,
  122,    0,    0,    0,    0,    0,    0,   81,    0,   79,
    0,    0,  129,  123,   14,    0,   70,   93,    0,    0,
    0,   88,   97,   85,   77,  138,  130,    0,   69,    0,
    0,    0,    0,  142,   15,  141,    0,   92,   95,   87,
    0,    0,    0,    0,    0,    0,    0,  159,    0,    0,
    0,    0,  151,    0,  150,  152,    0,  175,  176,  148,
  145,  147,  153,  156,  157,  154,  155,  149,    0,    0,
   91,   89,    0,    0,    0,  231,    0,  229,  230,    0,
    0,    0,    0,  198,    0,    0,  217,  220,    0,  225,
  226,  224,  205,    0,  191,    0,  212,    0,    0,  174,
    0,    0,    0,  183,    0,  143,    0,    0,    0,    0,
  177,  170,  167,    0,  200,    0,  192,    0,  241,  245,
    0,    0,    0,  228,    0,  238,  219,  193,    0,    0,
    0,    0,    0,  168,    0,  162,    0,    0,  187,    0,
    0,  146,  144,  173,  182,    0,  180,  181,    0,  194,
    0,    0,  201,   90,  240,    0,    0,  227,  239,    0,
    0,  218,  222,  206,    0,    0,  160,    0,  166,    0,
    0,  185,    0,  178,    0,  171,  195,    0,  199,  196,
    0,    0,  244,  208,  207,    0,  169,    0,  163,    0,
  186,  179,  204,    0,  202,  209,    0,  161,    0,    0,
  164,  190,  197,    0,  165,
};
short yydgoto[] = {                                       4,
   98,   91,  290,  317,  101,  291,  116,   47,   48,  157,
  396,    5,    6,    7,    8,    9,   16,  262,   69,   70,
   71,   72,   73,  171,   74,  172,   75,   76,  185,  245,
  263,  264,  265,  266,  324,  325,  390,  311,   92,  349,
  304,  292,  293,  268,  356,  357,  269,  306,  307,  375,
  407,  295,  296,  297,  298,  299,  300,  301,  351,  331,
  332,  314,  270,  271,  272,  273,  274,  275,  276,  277,
  278,   13,   14,  228,  229,   49,   50,   51,   52,   53,
   54,  117,  302,   56,   10,  151,   34,   35,  193,  119,
  120,  121,  122,  123,  124,  189,  125,  126,  194,   24,
  127,  152,  196,  231,  232,  197,  198,  128,  204,  129,
  190,  191,  207,  153,  154,   65,   66,  137,  177,  178,
  179,  180,  181,  182,   31,   22,   61,   37,  145,  213,
  238,  133,  165,  251,  308,  398,  378,  414,  279,  323,
  376,  359,  280,  327,  404,  391,
};
short yysindex[] = {                                   -226,
 -238, -200, -238,    0,    0, -156, -191,    0,    0, -145,
    0, -180, -238,    0,    0, -240,    0,  -74,    0,    0,
    0,  -91, -238,  -94,  140,    0,    0,    0, -200, -238,
  -62,    0,  -10, -238,    0, -238, -231,    0,    0,  140,
    0,   52,    0,    0,    0,  140,    0,    0, -156,  712,
 -133,    0,    0,  -69,    0,    0,    0,    0, -219,    2,
 -145,  436,    0,  -63,    0, -156, -238,    0,    0, -156,
    0,    0, -156,  -21,    0, -156,  -19,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  140,  140,    0,    0,    0,    0,    0,  140,   52,    0,
 -238,    0,    0,   12,    0,    0, -238, -171,   36,    0,
 -209,   44, -238,    0,  -26,    0,   93, -156,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  436,
 -238,   49, -238, -231,   67, -115,    0,   67,    0,   -2,
 -133,    0,    0,    0,  -94,  325, -194,    0,  436, -238,
   97,   83,  -46,    0,  325,    0,    0,    0,    0,  427,
    0,    0,    0, -238,  -21,    0,    0,    0,    0,    0,
    0,    0, -238,    0,    0,  104,   42,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -199,
    0,    0,    0,    0,    0,   63,  114,    0,  436,    0,
    0, -209,    0,    0,    0,    0,    0,  146,  107, -238,
    0, -115, -231,  108,  325,  427, -238,    0,  142,    0,
 -238, -238,    0,    0,    0,  436,    0,    0,  118,  148,
 -156,    0,    0,    0,    0,    0,    0,  122,    0,  139,
  427,  427,  427,    0,    0,    0, -209,    0,    0,    0,
  -30,  123,   75,  -96, -238, -200,  -96,    0,  -96, -238,
  152,  179,    0,  -43,    0,    0, -212,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  174,  427,
    0,    0, -209,  193,  -96,    0,   87,    0,    0,  155,
  -96,  154, -206,    0,  712, -133,    0,    0,  138,    0,
    0,    0,    0,  190,    0,  147,    0,  -30,  184,    0,
 -215, -206,  -96,    0,  137,    0,  -30,  -96, -238,  -96,
    0,    0,    0,  -35,    0,  126,    0,  145,    0,    0,
 -196,  195,  162,    0,  214,    0,    0,    0,  -96,  -96,
  -96,   87,  -96,    0, -114,    0,  -30, -238,    0,  197,
 -143,    0,    0,    0,    0, -127,    0,    0,  -30,    0,
  198,  570,    0,    0,    0,  -96,  -96,    0,    0,   -2,
 -133,    0,    0,    0, -131,  -30,    0,  -30,    0, -206,
  -96,    0,  -96,    0,  -96,    0,    0,  209,    0,    0,
  -30,  195,    0,    0,    0,  -96,    0,  -96,    0,  210,
    0,    0,    0,  -30,    0,    0,  206,    0,  -96,  205,
    0,    0,    0,  -30,    0,
};
short yyrindex[] = {                                      4,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,
    0,    0,    8,    0,    0,    0,    0,  175,    0,    0,
    0,  -24,    0,    9,    0,    0,    0,    0,    0,    0,
  -54,    0,    0,    3,    0,    0,  486,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   88,
  666,    0,    0,  572,    0,    0,    0,    0,    0,    0,
   86,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   99,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  215,    0,    0,  -12,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   26,  201,    0,    1,  -54,    0,    0,  -54,    0,  130,
  689,    0,    0,    0,  -29,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  159,    0,    0,    0,
    0,    0,    0,    0, -120,    0,    0,    0,    0,    0,
    0,  215,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  192,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  171,
 -222,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -88,    0,    0,    0,  185,    0,    0,    0,
  -16,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  443,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -141,    0,
    0,    0,  185,    0,    0,    0,    0,    0,    0,  262,
    0,    0,  338,    0,  606,  485,    0,    0,  396,    0,
    0,    0,    0,    0,    0,    0,    0,  -33,    0,    0,
    0,   68,    0,    0, -111,    0, -128,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -122,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -111,    0,    0, -136,
    0,    0,    0,    0,    0,    0,    0,    0, -111,    0,
  637,    0,    0,    0,    0,    0,    0,    0,    0,  622,
  533,    0,    0,    0,    0, -111,    0, -111,    0,   69,
    0,    0,    0,    0,    0,    0,    0,  317,    0,    0,
  -16, -116,    0,    0,    0,    0,    0,    0,    0,  -95,
    0,    0,    0,  222,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -111,    0,
};
short yygindex[] = {                                      0,
 -269,  203,   -1,    5,  -11,   -9,  385,    0,    0,    0,
    0,    0,    0,  -13,    0,    0,    0,   11,  289,    0,
  370,    0, -126,  369,    0,    0,    0, -117,    0,    0,
  270,  202,    0,    0,    0,  149,    0,    0, -267,  129,
    0,    0,   77,    0,    0,  124,    0, -245,   80,    0,
    0,  176,  173, -261,  178,  235,    0,    0,    0,    0,
  157,  236,    0,   -5,  212,    0,    0,    0,    0,    0,
    0,    0,  523,  298, -263,  501,  452,  454,  -14,  445,
  507, -124,   17,    0,  531,   19,    0,  520,  -56, -121,
    0,    0,    0,  450,    0,  404,    0,    0,  334,  500,
    0, -187,    0,    0,  320,    0,  347,    0,    0,    0,
    0,  351,  346,  321, -182,  440,    0,  415,    0,  371,
    0,    0,    0,    0,    0,    0,    0,  439,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 1012
short yytable[] = {                                      12,
  108,   18,   49,   23,   29,  118,   50,   22,  104,  174,
   20,   12,   17,  309,  219,   46,  326,   60,  175,  220,
   28,   33,   27,   45,  188,  103,  341,  340,   58,  337,
   46,   79,   33,  188,   58,  205,   46,    1,   45,   57,
   45,   55,   11,   27,   45,   67,  318,   27,   59,   83,
  150,  347,  115,   80,   64,  319,   55,    2,   55,  252,
  114,  319,   55,   27,   15,  132,   27,   19,   27,   68,
  131,   11,  320,  162,  134,    3,   21,  135,  320,  372,
  138,   46,   46,  142,   83,  174,  104,  100,   46,   45,
   45,  230,   25,  188,  175,  328,   45,   45,  326,  144,
  220,  341,  340,  214,  321,   58,  365,   55,   55,   58,
  321,  156,  192,  158,   55,   55,  230,  249,  230,   27,
  115,  170,  161,   93,  183,  147,  188,  109,  114,   58,
  172,  166,   94,  111,   58,   27,  115,  112,  394,  115,
  243,   96,  218,  158,  187,  115,  242,  114,  195,   64,
  115,   19,  408,  187,  176,  230,   95,  202,  158,  158,
  158,   67,  206,  382,   38,   11,  172,  189,   39,   23,
  188,   58,    1,   97,  172,  384,   96,   97,  215,  158,
  243,  212,  395,   82,   11,   68,  242,  158,  284,  115,
  285,  209,   41,   19,  286,  287,  158,  114,  130,   27,
   58,  377,  173,   43,  158,  115,  115,   44,  223,   18,
   58,  189,   30,  187,  158,  233,  115,  241,   82,  206,
  237,    2,   18,   36,  114,  201,  288,  289,  316,  254,
  176,  115,  115,  115,   15,  243,  360,  230,  106,  158,
  158,  158,   99,   18,  255,   58,   18,  104,  256,  261,
   11,  257,   23,  303,   11,  158,   47,  283,  310,   55,
   18,   19,   62,   18,   19,  136,  305,  244,  104,  102,
  115,  104,  361,   23,  158,  258,   23,  110,  158,   49,
   18,   58,  158,   50,   22,  104,   87,  139,  259,  260,
   23,  158,   89,   23,   55,   55,  146,   90,  108,  348,
   49,   18,  103,   49,   18,   22,  261,   50,   22,  104,
  164,  353,   38,  261,  241,  261,   39,  355,   18,  366,
   49,   18,   22,  103,   50,   22,  103,  267,  362,  149,
  211,  210,   11,  294,  211,  210,  312,  155,   40,  383,
  168,  379,  169,   42,  385,  261,  310,   38,  211,   19,
    2,   39,  115,  386,  200,   44,  216,  261,  199,   27,
  158,  160,   50,  330,  333,  210,   27,   11,  222,   27,
  397,  284,  399,  285,  261,  217,  261,  286,  287,  240,
   27,  282,   19,   50,  267,  405,   50,  363,   27,  261,
   44,  267,  350,  267,   27,   27,  254,  354,  410,  358,
   38,  226,  261,   50,   39,  116,  116,  221,  415,  288,
  289,  255,  261,  235,  350,  256,  242,   11,  257,  244,
   11,   74,  374,  267,  380,  247,   40,   47,   41,  281,
   74,   42,   94,   94,  244,  267,   28,   28,  313,   43,
  315,  335,  258,   44,  322,  330,  393,  338,  343,  342,
  346,  364,  267,   38,  267,  259,  260,   39,  381,  344,
  400,   74,  350,  367,  358,   74,   74,  267,  368,  387,
  403,  409,  411,   11,   38,  406,  413,  284,   39,  285,
  267,   41,    6,  286,  287,  109,   84,  137,  412,  109,
  267,   84,   43,  158,   11,  329,   44,  339,  284,  159,
  285,  225,   41,  167,  286,  287,  184,  246,  402,  345,
  389,  401,  371,   43,  370,  288,  289,   44,  174,  373,
  369,  334,  392,  174,  174,  336,  352,  174,  174,  174,
  174,  174,  174,  174,  174,   26,  288,  289,  248,  174,
   77,  174,  140,  143,  174,  141,  174,  174,   78,  174,
  174,  174,   32,   63,  174,  174,  174,  148,  203,  239,
  103,  174,  250,  234,  174,  227,  236,  253,  174,  174,
  163,  174,  174,  174,  174,  174,  203,  174,  174,  208,
    0,  203,  224,  186,    0,  105,    0,    0,  203,  106,
    0,  203,    0,    0,  223,  203,    0,  203,  203,  223,
  223,    0,    0,  223,  223,   11,  223,  223,  223,  223,
  223,  107,    0,   41,  203,  223,    0,  223,    0,    0,
  223,    0,  203,  223,   43,  223,  223,  223,  110,    0,
  223,  223,  223,    0,    0,  203,  203,  223,    0,    0,
  223,    0,    0,    0,  223,  223,    0,  223,  223,  223,
  223,  223,  221,  223,    0,    0,    0,  221,  221,    0,
    0,  221,  221,    0,  221,  221,  221,  221,  221,    0,
    0,    0,    0,  221,    0,  221,    0,    0,  221,    0,
    0,  221,    0,  221,  221,  221,    0,  105,  221,  221,
  221,  106,    0,  104,    0,  221,  105,    0,  221,    0,
  106,  174,  221,  221,    0,  221,  221,   11,  221,  221,
  174,  221,    0,  184,  184,   41,   11,    0,    0,    0,
    0,    0,  107,    0,   41,    0,   43,  174,    0,    0,
  110,    0,  108,    0,  109,   43,    0,    0,    0,  110,
  111,    0,    0,    0,  112,    0,  215,  215,    0,    0,
  184,  215,  113,  215,  215,  215,  215,  215,  184,  174,
    0,    0,  215,    0,  215,    0,    0,  215,    0,    0,
  215,    0,  215,  215,    0,    0,    0,  215,  215,  215,
    0,    0,    0,    0,  215,    0,    0,  215,    0,    0,
    0,  215,  215,    0,  216,  216,    0,  215,  215,  216,
  215,  216,  216,  216,  216,  216,    0,    0,    0,    0,
  216,    0,  216,    0,    0,  216,    0,    0,  216,    0,
  216,  216,    0,    0,    0,  216,  216,  216,   35,    0,
  105,    0,  216,    0,  106,  216,    0,   35,    0,  216,
  216,    0,    0,    0,   35,  216,  216,    0,  216,   35,
   11,   35,    0,    0,   35,    0,    0,   35,   41,   35,
   35,   35,    0,    0,   35,  388,   35,  213,  213,   43,
    0,   35,  213,  110,  213,  213,  213,  213,   35,   35,
    0,   35,   35,  214,  214,    0,    0,    0,  214,    0,
  214,  214,  214,  214,    0,    0,    0,  262,    0,  213,
    0,  262,    0,    0,    0,    0,    0,    0,  213,    0,
    0,    0,  213,  213,    0,  214,    0,  262,  213,  213,
    0,  213,    0,    0,  214,  262,    0,    0,  214,  214,
    0,    0,  262,    0,  214,  214,  262,  214,   29,    0,
  262,    0,    0,   29,    0,   29,    0,    0,   29,    0,
    0,   29,    0,   29,   29,    0,    0,    0,   29,    0,
   29,   30,    0,    0,    0,   29,   30,    0,   30,    0,
    0,   30,   29,   29,   30,    0,   30,   30,    0,    0,
    0,   30,    0,   30,   81,    0,    0,    0,   30,   82,
    0,   83,    0,    0,   84,   30,   30,   85,    0,   86,
   87,    0,    0,    0,   88,    0,   89,    0,    0,    0,
    0,   90,
};
short yycheck[] = {                                       1,
    0,    3,    0,    0,   16,   62,    0,    0,    0,  136,
    6,   13,    2,  259,  202,   25,  280,   31,  136,  202,
   16,   23,  263,   25,  146,    0,  296,  295,   30,  291,
   40,   46,   34,  155,   36,  160,   46,  264,   40,   29,
   42,   25,  281,  263,   46,  277,  259,  263,   30,  272,
  260,  267,   62,   49,   36,  268,   40,  284,   42,  247,
   62,  268,   46,  263,  265,   67,  263,  308,  263,  301,
   66,  281,  285,  130,   70,  302,  268,   73,  285,  341,
   76,   91,   92,   98,  307,  212,  258,  307,   98,   91,
   92,  216,  273,  215,  212,  283,   98,   99,  362,  101,
  283,  371,  370,  303,  317,  107,  303,   91,   92,  111,
  317,  113,  307,  115,   98,   99,  241,  242,  243,  263,
  130,  135,  118,  257,  138,  107,  263,  299,  130,  131,
  272,  133,  266,  305,  136,  263,  146,  309,  270,  149,
  263,  262,  199,  272,  146,  155,  263,  149,  150,  131,
  160,  308,  398,  155,  136,  280,  290,  153,  160,  271,
  272,  277,  164,  307,  261,  281,  308,  263,  265,  315,
  307,  173,  264,  294,  316,  303,  310,  311,  190,  308,
  303,  177,  314,  272,  281,  301,  303,  316,  285,  199,
  287,  173,  289,  308,  291,  292,  308,  199,  262,  263,
  202,  316,  318,  300,  316,  215,  216,  304,  210,  264,
  212,  307,  287,  215,  216,  217,  226,  229,  307,  221,
  222,  284,  277,  318,  226,  272,  323,  324,  272,  260,
  212,  241,  242,  243,  265,  231,  272,  362,  265,  241,
  242,  243,  312,  298,  275,  247,  301,  277,  279,  251,
  281,  282,  277,  255,  281,  272,  269,  253,  260,  272,
  315,  308,  273,  318,  308,  287,  256,  298,  298,  268,
  280,  301,  308,  298,  308,  306,  301,  304,  280,  277,
  277,  283,  316,  277,  277,  277,  289,  307,  319,  320,
  315,  308,  295,  318,  307,  308,  285,  300,  298,  311,
  298,  298,  277,  301,  301,  298,  308,  301,  301,  301,
  262,  317,  261,  315,  326,  317,  265,  319,  315,  331,
  318,  318,  315,  298,  318,  318,  301,  251,  324,  294,
  263,  263,  281,  254,  267,  267,  260,  294,  287,  351,
  274,  347,  276,  292,  356,  347,  348,  261,  307,  308,
  284,  265,  362,  359,  272,  304,  294,  359,  262,  263,
  362,  269,  277,  284,  285,  262,  263,  281,  262,  263,
  376,  285,  378,  287,  376,  262,  378,  291,  292,  262,
  263,  307,  308,  298,  308,  391,  301,  262,  263,  391,
  304,  315,  313,  317,  307,  308,  260,  318,  404,  320,
  261,  294,  404,  318,  265,  307,  308,  262,  414,  323,
  324,  275,  414,  272,  335,  279,  269,  281,  282,  298,
  281,  263,  343,  347,  348,  287,  287,  269,  289,  307,
  272,  292,  262,  263,  298,  359,  307,  308,  287,  300,
  262,  287,  306,  304,  271,  366,  367,  294,  259,  312,
  267,  307,  376,  261,  378,  319,  320,  265,  262,  313,
  381,  303,  383,  269,  385,  307,  308,  391,  307,  272,
  262,  262,  267,  281,  261,  396,  272,  285,  265,  287,
  404,  289,  308,  291,  292,    0,  272,  287,  409,  298,
  414,  307,  300,  272,  281,  303,  304,  295,  285,  115,
  287,  213,  289,  134,  291,  292,  138,  238,  385,  308,
  362,  383,  340,  300,  339,  323,  324,  304,  257,  342,
  307,  287,  366,  262,  263,  290,  315,  266,  267,  268,
  269,  270,  271,  272,  273,   13,  323,  324,  241,  278,
   40,  280,   91,   99,  283,   92,  285,  286,   42,  288,
  289,  290,   22,   34,  293,  294,  295,  108,  155,  226,
   61,  300,  243,  217,  303,  215,  221,  247,  307,  308,
  131,  310,  311,  312,  313,  314,  260,  316,  317,  165,
   -1,  265,  212,  145,   -1,  261,   -1,   -1,  272,  265,
   -1,  275,   -1,   -1,  257,  279,   -1,  281,  282,  262,
  263,   -1,   -1,  266,  267,  281,  269,  270,  271,  272,
  273,  287,   -1,  289,  298,  278,   -1,  280,   -1,   -1,
  283,   -1,  306,  286,  300,  288,  289,  290,  304,   -1,
  293,  294,  295,   -1,   -1,  319,  320,  300,   -1,   -1,
  303,   -1,   -1,   -1,  307,  308,   -1,  310,  311,  312,
  313,  314,  257,  316,   -1,   -1,   -1,  262,  263,   -1,
   -1,  266,  267,   -1,  269,  270,  271,  272,  273,   -1,
   -1,   -1,   -1,  278,   -1,  280,   -1,   -1,  283,   -1,
   -1,  286,   -1,  288,  289,  290,   -1,  261,  293,  294,
  295,  265,   -1,  258,   -1,  300,  261,   -1,  303,   -1,
  265,  259,  307,  308,   -1,  310,  311,  281,  313,  314,
  268,  316,   -1,  271,  272,  289,  281,   -1,   -1,   -1,
   -1,   -1,  287,   -1,  289,   -1,  300,  285,   -1,   -1,
  304,   -1,  297,   -1,  299,  300,   -1,   -1,   -1,  304,
  305,   -1,   -1,   -1,  309,   -1,  262,  263,   -1,   -1,
  308,  267,  317,  269,  270,  271,  272,  273,  316,  317,
   -1,   -1,  278,   -1,  280,   -1,   -1,  283,   -1,   -1,
  286,   -1,  288,  289,   -1,   -1,   -1,  293,  294,  295,
   -1,   -1,   -1,   -1,  300,   -1,   -1,  303,   -1,   -1,
   -1,  307,  308,   -1,  262,  263,   -1,  313,  314,  267,
  316,  269,  270,  271,  272,  273,   -1,   -1,   -1,   -1,
  278,   -1,  280,   -1,   -1,  283,   -1,   -1,  286,   -1,
  288,  289,   -1,   -1,   -1,  293,  294,  295,  257,   -1,
  261,   -1,  300,   -1,  265,  303,   -1,  266,   -1,  307,
  308,   -1,   -1,   -1,  273,  313,  314,   -1,  316,  278,
  281,  280,   -1,   -1,  283,   -1,   -1,  286,  289,  288,
  289,  290,   -1,   -1,  293,  296,  295,  262,  263,  300,
   -1,  300,  267,  304,  269,  270,  271,  272,  307,  308,
   -1,  310,  311,  262,  263,   -1,   -1,   -1,  267,   -1,
  269,  270,  271,  272,   -1,   -1,   -1,  261,   -1,  294,
   -1,  265,   -1,   -1,   -1,   -1,   -1,   -1,  303,   -1,
   -1,   -1,  307,  308,   -1,  294,   -1,  281,  313,  314,
   -1,  316,   -1,   -1,  303,  289,   -1,   -1,  307,  308,
   -1,   -1,  296,   -1,  313,  314,  300,  316,  273,   -1,
  304,   -1,   -1,  278,   -1,  280,   -1,   -1,  283,   -1,
   -1,  286,   -1,  288,  289,   -1,   -1,   -1,  293,   -1,
  295,  273,   -1,   -1,   -1,  300,  278,   -1,  280,   -1,
   -1,  283,  307,  308,  286,   -1,  288,  289,   -1,   -1,
   -1,  293,   -1,  295,  273,   -1,   -1,   -1,  300,  278,
   -1,  280,   -1,   -1,  283,  307,  308,  286,   -1,  288,
  289,   -1,   -1,   -1,  293,   -1,  295,   -1,   -1,   -1,
   -1,  300,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 324
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"AND","ARRAY","ASSIGNMENT","CASE",
"CHARACTER_STRING","COLON","COMMA","CONST","DIGSEQ","DIV","DO","DOT","DOTDOT",
"DOWNTO","ELSE","END","EQUAL","EXTERNAL","FOR","FORWARD","FUNCTION","GE","GOTO",
"GT","IDENTIFIER","IF","IN","LABEL","LBRAC","LE","LPAREN","LT","MINUS","MOD",
"NIL","NOT","NOTEQUAL","OF","OR","OTHERWISE","PACKED","_BEGIN","_FILE","PLUS",
"PROCEDURE","PROGRAM","RBRAC","REALNUMBER","RECORD","REPEAT","RPAREN",
"SEMICOLON","SET","SLASH","STAR","STARSTAR","THEN","TO","TYPE","UNTIL",
"UPARROW","VAR","WHILE","WITH","NEW","DELETE","TRUE","FALSE",
};
char *yyrule[] = {
"$accept : file",
"file : program",
"file : module",
"$$1 :",
"program : program_heading semicolon $$1 block DOT",
"program : block DOT",
"program_heading : PROGRAM identifier",
"program_heading : PROGRAM identifier LPAREN identifier_list RPAREN",
"identifier_list : identifier_list comma identifier",
"identifier_list : identifier",
"$$2 :",
"$$3 :",
"$$4 :",
"$$5 :",
"$$6 :",
"block : label_declaration_part $$2 constant_definition_part $$3 type_definition_part $$4 variable_declaration_part $$5 procedure_and_function_declaration_part $$6 statement_part",
"module : constant_definition_part type_definition_part variable_declaration_part procedure_and_function_declaration_part",
"label_declaration_part : LABEL label_list semicolon",
"label_declaration_part :",
"label_list : label_list comma label",
"label_list : label",
"label : DIGSEQ",
"constant_definition_part : CONST constant_list",
"constant_definition_part :",
"constant_list : constant_list constant_definition",
"constant_list : constant_definition",
"constant_definition : identifier EQUAL const_expression semicolon",
"const_expression : const_simple_expression",
"const_expression : const_simple_expression relop const_simple_expression",
"const_simple_expression : const_term",
"const_simple_expression : const_simple_expression addop const_term",
"const_term : const_factor",
"const_term : const_term mulop const_factor",
"const_factor : sign const_factor",
"const_factor : const_exponentiation",
"const_exponentiation : const_primary",
"const_exponentiation : const_primary STARSTAR const_exponentiation",
"const_primary : identifier",
"const_primary : LPAREN const_expression RPAREN",
"const_primary : unsigned_constant",
"const_primary : NOT const_primary",
"constant : non_string",
"constant : sign non_string",
"constant : CHARACTER_STRING",
"sign : PLUS",
"sign : MINUS",
"non_string : DIGSEQ",
"non_string : identifier",
"non_string : REALNUMBER",
"type_definition_part : TYPE type_definition_list",
"type_definition_part :",
"type_definition_list : type_definition_list type_definition",
"type_definition_list : type_definition",
"type_definition : identifier EQUAL type_denoter semicolon",
"type_denoter : new_type",
"type_denoter : identifier",
"new_type : new_ordinal_type",
"new_type : new_structured_type",
"new_type : new_pointer_type",
"new_ordinal_type : enumerated_type",
"new_ordinal_type : subrange_type",
"enumerated_type : LPAREN identifier_list RPAREN",
"subrange_type : constant DOTDOT constant",
"new_structured_type : structured_type",
"new_structured_type : PACKED structured_type",
"structured_type : array_type",
"structured_type : record_type",
"structured_type : set_type",
"structured_type : file_type",
"array_type : ARRAY LBRAC index_list RBRAC OF component_type",
"index_list : index_list comma index_type",
"index_list : index_type",
"index_type : ordinal_type",
"ordinal_type : new_ordinal_type",
"ordinal_type : identifier",
"component_type : type_denoter",
"record_type : RECORD record_section_list END",
"record_type : RECORD record_section_list semicolon variant_part END",
"record_type : RECORD variant_part END",
"record_section_list : record_section_list semicolon record_section",
"record_section_list : record_section",
"record_section : identifier_list COLON type_denoter",
"variant_part : CASE variant_selector OF variant_list semicolon",
"variant_part : CASE variant_selector OF variant_list",
"variant_part :",
"variant_selector : tag_field COLON tag_type",
"variant_selector : tag_type",
"variant_list : variant_list semicolon variant",
"variant_list : variant",
"variant : case_constant_list COLON LPAREN record_section_list RPAREN",
"variant : case_constant_list COLON LPAREN record_section_list semicolon variant_part RPAREN",
"variant : case_constant_list COLON LPAREN variant_part RPAREN",
"case_constant_list : case_constant_list comma case_constant",
"case_constant_list : case_constant",
"case_constant : constant",
"case_constant : constant DOTDOT constant",
"tag_field : identifier",
"tag_type : identifier",
"set_type : SET OF base_type",
"base_type : ordinal_type",
"file_type : _FILE OF component_type",
"new_pointer_type : UPARROW domain_type",
"domain_type : identifier",
"variable_declaration_part : VAR variable_declaration_list semicolon",
"variable_declaration_part :",
"variable_declaration_list : variable_declaration_list semicolon variable_declaration",
"variable_declaration_list : variable_declaration",
"variable_declaration : identifier_list COLON type_denoter",
"procedure_and_function_declaration_part : proc_or_func_declaration_list semicolon",
"procedure_and_function_declaration_part :",
"proc_or_func_declaration_list : proc_or_func_declaration_list semicolon proc_or_func_declaration",
"proc_or_func_declaration_list : proc_or_func_declaration",
"proc_or_func_declaration : procedure_declaration",
"proc_or_func_declaration : function_declaration",
"procedure_declaration : procedure_heading semicolon directive",
"procedure_declaration : procedure_heading semicolon procedure_block",
"procedure_heading : procedure_identification",
"procedure_heading : procedure_identification formal_parameter_list",
"$$7 :",
"procedure_identification : PROCEDURE $$7 identifier",
"directive : FORWARD",
"directive : EXTERNAL",
"formal_parameter_list : LPAREN formal_parameter_section_list RPAREN",
"formal_parameter_section_list : formal_parameter_section_list semicolon formal_parameter_section",
"formal_parameter_section_list : formal_parameter_section",
"formal_parameter_section : value_parameter_specification",
"formal_parameter_section : variable_parameter_specification",
"formal_parameter_section : procedural_parameter_specification",
"formal_parameter_section : functional_parameter_specification",
"value_parameter_specification : identifier_list COLON identifier",
"variable_parameter_specification : VAR identifier_list COLON identifier",
"procedural_parameter_specification : procedure_heading",
"functional_parameter_specification : function_heading",
"procedure_block : block",
"function_declaration : function_heading semicolon directive",
"function_declaration : function_heading semicolon function_block",
"function_heading : FUNCTION identifier COLON result_type",
"$$8 :",
"function_heading : FUNCTION identifier $$8 formal_parameter_list COLON result_type",
"result_type : identifier",
"function_block : block",
"statement_part : compound_statement",
"$$9 :",
"compound_statement : _BEGIN $$9 statement_sequence END",
"statement_sequence : statement_sequence semicolon statement",
"statement_sequence : statement",
"statement : label COLON non_labeled_statement",
"statement : non_labeled_statement",
"non_labeled_statement : assignment_statement",
"non_labeled_statement : procedure_statement",
"non_labeled_statement : goto_statement",
"non_labeled_statement : compound_statement",
"non_labeled_statement : case_statement",
"non_labeled_statement : repeat_statement",
"non_labeled_statement : with_statement",
"non_labeled_statement : if_statement",
"non_labeled_statement : while_statement",
"non_labeled_statement : for_statement",
"non_labeled_statement :",
"$$10 :",
"$$11 :",
"repeat_statement : REPEAT $$10 statement_sequence UNTIL $$11 boolean_expression",
"$$12 :",
"while_statement : WHILE boolean_expression DO $$12 statement",
"$$13 :",
"for_statement : FOR control_variable ASSIGNMENT initial_value direction final_value DO $$13 statement",
"with_statement : WITH record_variable_list DO statement",
"if_statement : if_part else_part",
"$$14 :",
"if_part : IF boolean_expression THEN $$14 statement",
"$$15 :",
"else_part : ELSE $$15 statement",
"else_part :",
"assignment_statement : variable_access ASSIGNMENT expression",
"variable_access : identifier",
"variable_access : indexed_variable",
"variable_access : field_designator",
"variable_access : variable_access UPARROW",
"indexed_variable : variable_access LBRAC index_expression_list RBRAC",
"index_expression_list : index_expression_list comma index_expression",
"index_expression_list : index_expression",
"index_expression : expression",
"field_designator : variable_access DOT identifier",
"procedure_statement : identifier params",
"procedure_statement : identifier",
"params : LPAREN actual_parameter_list RPAREN",
"actual_parameter_list : actual_parameter_list comma actual_parameter",
"actual_parameter_list : actual_parameter",
"actual_parameter : expression",
"actual_parameter : expression COLON expression",
"actual_parameter : expression COLON expression COLON expression",
"goto_statement : GOTO label",
"case_statement : header_part case_statement_part",
"header_part : CASE case_index OF",
"case_statement_part : case_list_element_list END",
"case_statement_part : case_list_element_list SEMICOLON END",
"$$16 :",
"case_statement_part : case_list_element_list semicolon otherwisepart $$16 statement END",
"case_index : expression",
"case_list_element_list : case_list_element_list semicolon case_list_element",
"case_list_element_list : case_list_element",
"$$17 :",
"case_list_element : case_constant_list COLON $$17 statement",
"otherwisepart : OTHERWISE",
"otherwisepart : OTHERWISE COLON",
"control_variable : identifier",
"initial_value : expression",
"direction : TO",
"direction : DOWNTO",
"final_value : expression",
"record_variable_list : record_variable_list comma variable_access",
"record_variable_list : variable_access",
"boolean_expression : expression",
"expression : simple_expression",
"expression : simple_expression relop simple_expression",
"simple_expression : term",
"simple_expression : simple_expression addop term",
"term : factor",
"term : term mulop factor",
"factor : sign factor",
"factor : exponentiation",
"exponentiation : primary",
"exponentiation : primary STARSTAR exponentiation",
"primary : variable_access",
"primary : unsigned_constant",
"primary : function_designator",
"primary : set_constructor",
"primary : LPAREN expression RPAREN",
"primary : NOT primary",
"primary : TRUE",
"primary : FALSE",
"primary : NIL",
"unsigned_constant : unsigned_number",
"unsigned_constant : CHARACTER_STRING",
"unsigned_number : unsigned_integer",
"unsigned_number : unsigned_real",
"unsigned_integer : DIGSEQ",
"unsigned_real : REALNUMBER",
"function_designator : identifier params",
"function_designator : identifier LPAREN RPAREN",
"set_constructor : LBRAC member_designator_list RBRAC",
"set_constructor : LBRAC RBRAC",
"member_designator_list : member_designator_list comma member_designator",
"member_designator_list : member_designator",
"member_designator : member_designator DOTDOT expression",
"member_designator : expression",
"addop : PLUS",
"addop : MINUS",
"addop : OR",
"mulop : STAR",
"mulop : SLASH",
"mulop : DIV",
"mulop : MOD",
"mulop : AND",
"relop : EQUAL",
"relop : NOTEQUAL",
"relop : LT",
"relop : GT",
"relop : LE",
"relop : GE",
"relop : IN",
"identifier : IDENTIFIER",
"semicolon : SEMICOLON",
"comma : COMMA",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 2208 "pas.y"

yyerror(char *s)
{ printf("\nline %d:  %s",line_no,s);
  yyerrok;
  return 1;	
}

YaccRetptr StringCat(int args,...)
{	
	va_list argptr;
 	int i,size=1;
	YaccRetptr temp1,temp2;
	if(args<2)
	  { printf("\n args to StringCat should be more than 1 ");
	   return;
	  }	
	va_start(argptr,args);

	temp1=(YaccRetptr)malloc(sizeof(YaccRettype));
	temp1->lexeme=(char *) malloc(sizeof(char));
	for(i=0;i<args;i++)
	{     temp2=va_arg(argptr,YaccRetptr);
	      size=size	+ sizeof(temp2->lexeme)+1;	
	      temp1->lexeme=(char *)realloc(temp1->lexeme,size);
	      strcat(temp1->lexeme,temp2->lexeme);
	}
	va_end(argptr);
	return &(*temp1);
}		
Constptr MakeConstList(Constptr ptr1,Constptr ptr2)
{ Constptr temp; int low,high;
  if(ptr1->const_type==CONST_REAL||ptr2->const_type==CONST_REAL)
 	{printf("\n constant list of real is not possible "); getchar();
	return NULL;	
	}
  if((ptr1->const_type==CONST_CHAR && strlen(ptr1->string)>1)
    ||(ptr2->const_type==CONST_CHAR && strlen(ptr2->string)>1))
   { printf("\n char constant can't  be more than one character in constlist");
	getchar();
	return NULL;
   }
  if(ptr1->const_type==CONST_INT && ptr2->const_type==CONST_INT)
  {  low=(int)ptr1->value; high=(int)ptr2->value;
     temp=ptr1;
     while(low<high-1)
    { temp->nxt=(Constptr)malloc(sizeof(Constant));
	temp->nxt->const_type=CONST_INT;
	temp->nxt->value=low+1; 
	temp=temp->nxt;
	low++;
    }
    temp->nxt=ptr2;
     temp=ptr1;
     while(temp) { printf(" %d",(int)temp->value); temp=temp->nxt;}
    return ptr1;	
  }
  if(ptr1->const_type==CONST_CHAR && ptr2->const_type==CONST_CHAR)
  {  low=(int)ptr1->string[0]; high=(int)ptr2->string[0];
     temp=ptr1;
     while(low<high-1)
    {  char buf[24];temp->nxt=(Constptr)malloc(sizeof(Constant));
	temp->const_type=CONST_CHAR;
	temp->string=(char *)malloc(2);
	sprintf(buf,"%c",low+1);
	strcpy(temp->string,buf);
	low++;
    }
    temp->nxt=ptr2;
    return ptr1;	
  }
  else { printf("\n both constants are not of same type");
	getchar();
	return NULL;
  }	
}
#line 932 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 105 "pas.y"
{ printf("\n ----------------HURRAY------------\n"); 
		  SymtabTraverseFuncTree(symtab);
		  Print("\n");
		  exit(0);	
		}
break;
case 3:
#line 115 "pas.y"
{ printf("\n--------program head-----------"); }
break;
case 4:
#line 117 "pas.y"
{ printf("\n program head block . ");
		}
break;
case 5:
#line 120 "pas.y"
{ printf("\n block  . ");
		}
break;
case 6:
#line 126 "pas.y"
{ 
		}
break;
case 7:
#line 129 "pas.y"
{  free(yyvsp[-4].stackptr); free(yyvsp[-2].stackptr); free(yyvsp[0].stackptr);
		 SymtabPrintIdlist(yyvsp[-1].idptr);
		}
break;
case 8:
#line 136 "pas.y"
{ Idptr temp;
		   printf("\n id_list");
		   temp=SymtabCreateNewId(yyvsp[0].stackptr->lexeme);	
		   yyval.idptr=SymtabAppendToIdlist(yyvsp[-2].idptr,temp);	
		}
break;
case 9:
#line 142 "pas.y"
{ /*printf("\n id");*/
		   yyval.idptr=SymtabCreateNewId(yyvsp[0].stackptr->lexeme);	
		}
break;
case 10:
#line 149 "pas.y"
{ printf("\n----label-decl-----------------");
		}
break;
case 11:
#line 152 "pas.y"
{ printf("\n-------const_def----------"); 
		}
break;
case 12:
#line 155 "pas.y"
{ printf("\n------type-def-------------");
		}
break;
case 13:
#line 158 "pas.y"
{ printf("\n---------var-def-----------");
		 printf("\n ===================definations over ============");
		getchar();
		  PrintAllDeclarations();
		}
break;
case 14:
#line 164 "pas.y"
{ 
		 BLOCK_IS_FUNC_FLAG=1;
		}
break;
case 15:
#line 168 "pas.y"
{ 
		  printf("\n block");
		  printf("\n*************************************************");
		}
break;
case 17:
#line 184 "pas.y"
{ printf("\n label label_list ; ");
		}
break;
case 18:
#line 187 "pas.y"
{ printf("\n empty label decl ");
		}
break;
case 19:
#line 193 "pas.y"
{ printf("\n label_list , label");
		}
break;
case 20:
#line 196 "pas.y"
{ printf("\n label");
		}
break;
case 21:
#line 201 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 22:
#line 206 "pas.y"
{ printf("\n const const_list ");
		 /*PrintConstlist();*/
		}
break;
case 23:
#line 210 "pas.y"
{ printf("\n empty const list");
		/*PrintConstlist();*/
		}
break;
case 24:
#line 217 "pas.y"
{ printf("\n const_list const_def");
		}
break;
case 25:
#line 220 "pas.y"
{ printf("\n const_def");
		}
break;
case 26:
#line 226 "pas.y"
{ printf("\n id = cexpr ;");
		 if(yyvsp[-1].constptr!=NULL)
		  { SymtabInsertConst(yyvsp[-3].stackptr->lexeme,yyvsp[-1].constptr); 
		    free(yyvsp[-2].stackptr); free(yyvsp[-3].stackptr); free(yyvsp[0].stackptr);
		  }
		 else 
		   printf("\n Not inserting constaant def due to $3=NULL");
		}
break;
case 27:
#line 239 "pas.y"
{ printf("\n const_simple_expr");
		 yyval.constptr=yyvsp[0].constptr;	
		}
break;
case 28:
#line 243 "pas.y"
{printf("\nconst_simple_expression relop const_simple_expression");
		yyval.constptr=SymtabCreateNewConst(CONST_INT,"0");
		if(yyvsp[-2].constptr->const_type==CONST_CHAR || yyvsp[0].constptr->const_type==CONST_CHAR)
		  {   
		    error(INVALID_STRING_OPR);
		       free(yyval.constptr); yyval.constptr=NULL;
		    }
		else{
  		  switch(yyvsp[-1].stackptr->type) {
		     case EQUAL: yyval.constptr->value=(yyvsp[-2].constptr->value)==(yyvsp[0].constptr->value); break;
		     case NOTEQUAL: yyval.constptr->value=(yyvsp[-2].constptr->value)!=(yyvsp[0].constptr->value); break;
		     case GT: yyval.constptr->value=(yyvsp[-2].constptr->value)>(yyvsp[0].constptr->value); break;
		     case LT: yyval.constptr->value=(yyvsp[-2].constptr->value)<(yyvsp[0].constptr->value); break;
		     case LE: yyval.constptr->value=(yyvsp[-2].constptr->value)<=(yyvsp[0].constptr->value); break;
		     case GE: yyval.constptr->value=(yyvsp[-2].constptr->value)>=(yyvsp[0].constptr->value); break;
		  /* the IN case is to be handled*/
		   } 
		 }
		free(yyvsp[-2].constptr); free(yyvsp[0].constptr); free(yyvsp[-1].stackptr);
	      }
break;
case 29:
#line 267 "pas.y"
{ printf("\n const_term");
		 yyval.constptr=yyvsp[0].constptr;	
		}
break;
case 30:
#line 271 "pas.y"
{ printf("\n const_simple_expr addop const_term");
		yyval.constptr=(Constptr)malloc(sizeof(Constant));
		if(yyvsp[-2].constptr->const_type==CONST_CHAR || yyvsp[0].constptr->const_type==CONST_CHAR)
		  {  error(INVALID_STRING_OPR);
		    free(yyval.constptr); 
		    yyval.constptr=NULL;
		  } 
		else {
		  if(yyvsp[-2].constptr->const_type==CONST_INT && yyvsp[0].constptr->const_type==CONST_INT)
	 		yyval.constptr->const_type=CONST_INT;
	          else if(yyvsp[-2].constptr->const_type==CONST_REAL ||
			 yyvsp[0].constptr->const_type==CONST_REAL)
				yyval.constptr->const_type=CONST_REAL;
		   yyval.constptr->nxt=NULL;
		  switch(yyvsp[-1].stackptr->type) {
			case PLUS: yyval.constptr->value=yyvsp[-2].constptr->value+yyvsp[0].constptr->value;break;
			case MINUS: yyval.constptr->value=yyvsp[-2].constptr->value-yyvsp[0].constptr->value;break;
			case OR: yyval.constptr->value=(int)yyvsp[-2].constptr->value|(int) yyvsp[0].constptr->value;break;
		   }
		}
	     free(yyvsp[-2].constptr); free(yyvsp[0].constptr);	free(yyvsp[-1].stackptr);
	   }
break;
case 31:
#line 297 "pas.y"
{ printf("\n const_factor");
		 yyval.constptr=yyvsp[0].constptr;	
		}
break;
case 32:
#line 301 "pas.y"
{ printf("\n const_term mulop const_factor");
		yyval.constptr=(Constptr)malloc(sizeof(Constant));
		if(yyvsp[-2].constptr->const_type==CONST_CHAR || yyvsp[0].constptr->const_type==CONST_CHAR)
		  {  error(INVALID_STRING_OPR);
		    free(yyval.constptr); 
		    yyval.constptr=NULL;
		  } 
		else {
		  if(yyvsp[-2].constptr->const_type==CONST_INT && yyvsp[0].constptr->const_type==CONST_INT)
	 		yyval.constptr->const_type=CONST_INT;
	          else if(yyvsp[-2].constptr->const_type==CONST_REAL ||
			 yyvsp[0].constptr->const_type==CONST_REAL)
				yyval.constptr->const_type=CONST_REAL;
		   yyval.constptr->nxt=NULL;
		  switch(yyvsp[-1].stackptr->type) {
			case STAR: yyval.constptr->value=yyvsp[-2].constptr->value*yyvsp[0].constptr->value;break;
			case SLASH: yyval.constptr->value=yyvsp[-2].constptr->value/yyvsp[0].constptr->value;break;
			case DIV: 
			    (int)yyval.constptr->value=yyvsp[-2].constptr->value/ yyvsp[0].constptr->value;break;
			case MOD: 
			    yyval.constptr->value=(int)yyvsp[-2].constptr->value%(int)yyvsp[0].constptr->value;break;
			case AND: 
			    yyval.constptr->value=(int)yyvsp[-2].constptr->value &(int) yyvsp[0].constptr->value;break;
		   }
		}
	     free(yyvsp[-2].constptr); free(yyvsp[0].constptr);	free(yyvsp[-1].stackptr);
	 }
break;
case 33:
#line 332 "pas.y"
{ printf("\n sign const_factor");
		 if(yyvsp[0].constptr->const_type==CONST_CHAR) yyval.constptr=NULL;
		 else {
			yyval.constptr=(Constptr)malloc(sizeof(Constant));
			if(strcmp(yyvsp[-1].stackptr->lexeme,"-")==0) 
				yyval.constptr->value=-yyvsp[0].constptr->value;
			else yyval.constptr->value=yyvsp[0].constptr->value;
			yyval.constptr->nxt=NULL;
		  }
		   free(yyvsp[0].constptr); free(yyvsp[-1].stackptr);
		}
break;
case 34:
#line 344 "pas.y"
{ printf("\n const_exponentiation");
		 yyval.constptr=yyvsp[0].constptr;	
		}
break;
case 35:
#line 351 "pas.y"
{ printf("\n const_primary");
		 yyval.constptr=yyvsp[0].constptr;
		}
break;
case 36:
#line 355 "pas.y"
{ printf("\n const_prim ** const exponentin");
		  if(yyvsp[-2].constptr->const_type=CONST_CHAR || yyvsp[0].constptr->const_type==CONST_CHAR)
		  {  error(INVALID_STRING_OPR);
		     yyval.constptr=NULL;
		    }
		    else{
		      yyval.constptr=(Constptr)malloc(sizeof(Constant));
		      yyval.constptr->value=pwr(yyvsp[-2].constptr->value,yyvsp[0].constptr->value);
		      yyval.constptr->nxt=NULL;
		    }
		 free(yyvsp[-2].constptr); free(yyvsp[-1].stackptr); free(yyvsp[0].constptr);
		}
break;
case 37:
#line 371 "pas.y"
{ /*printf("\n id");*/
		yyval.constptr=SymtabCreateNewConst(CONST_ID,yyvsp[0].stackptr->lexeme);
		}
break;
case 38:
#line 375 "pas.y"
{ 
		 yyval.constptr=yyvsp[-1].constptr;printf("\n (const_expr");
		}
break;
case 39:
#line 379 "pas.y"
{ printf("\n unsinged_const");
		 yyval.constptr=yyvsp[0].constptr;
		}
break;
case 40:
#line 383 "pas.y"
{ yyvsp[0].constptr->value=~(int)yyvsp[0].constptr->value;
                  yyval.constptr=yyvsp[0].constptr;
		  printf("\n ! const_primary");
		}
break;
case 41:
#line 392 "pas.y"
{ printf("\n non_string");
		  if(yyvsp[0].stackptr->type==DIGSEQ) 
			yyval.constptr=SymtabCreateNewConst(CONST_INT,yyvsp[0].stackptr->lexeme);
		  else if(yyvsp[0].stackptr->type==REALNUMBER)
			yyval.constptr=SymtabCreateNewConst(CONST_REAL,yyvsp[0].stackptr->lexeme);
		  else if(yyvsp[0].stackptr->type==IDENTIFIER) 
			yyval.constptr=SymtabCreateNewConst(CONST_ID,yyvsp[0].stackptr->lexeme);
		}
break;
case 42:
#line 401 "pas.y"
{ 
		  if(yyvsp[0].stackptr->type==DIGSEQ) {
			yyval.constptr=SymtabCreateNewConst(CONST_INT,yyvsp[0].stackptr->lexeme);
			if(yyvsp[-1].stackptr->type==MINUS)
				yyval.constptr->value=-yyval.constptr->value;
		  }
		  else if(yyvsp[0].stackptr->type==REALNUMBER){
			yyval.constptr=SymtabCreateNewConst(CONST_REAL,yyvsp[0].stackptr->lexeme);
			if(yyvsp[-1].stackptr->type==MINUS)
				yyval.constptr->value=-yyval.constptr->value;
		  }	
		  else if(yyvsp[0].stackptr->type==IDENTIFIER) 
			{  yyval.constptr=SymtabCreateNewConst(CONST_ID,yyvsp[0].stackptr->lexeme);
			   if(yyvsp[-1].stackptr->type==MINUS)
				if(yyval.constptr) yyval.constptr->value=-yyval.constptr->value;
			}
		   printf("\n sign non_string");
		}
break;
case 43:
#line 420 "pas.y"
{ printf("\n char_string");
		  yyval.constptr=SymtabCreateNewConst(CONST_CHAR,yyvsp[0].stackptr->lexeme);
		}
break;
case 44:
#line 425 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 45:
#line 426 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 46:
#line 430 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 47:
#line 431 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 48:
#line 432 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 49:
#line 437 "pas.y"
{ printf("\n type type_def_list"); 
		    SymtabVerifyFwdRef();
		    SymtabPrintTypeList();
		}
break;
case 50:
#line 442 "pas.y"
{ printf("\n empty type_def_list");
		}
break;
case 51:
#line 448 "pas.y"
{ printf("\n type_def_list type_def"); 
		}
break;
case 52:
#line 451 "pas.y"
{
		 printf("\n type_def");
		}
break;
case 53:
#line 458 "pas.y"
{ printf("\n id %s= type_denoter ;",yyvsp[-3].stackptr->lexeme);
		   if(yyvsp[-1].typeptr!=NULL)
		   { if(SymtabIsNameDefined(yyvsp[-3].stackptr->lexeme))
			error(DUPLICATE_DECLARATION);
		     else{	
		      yyvsp[-1].typeptr->typename=(char*)malloc(strlen(yyvsp[-3].stackptr->lexeme)+1);
		      strcpy(yyvsp[-1].typeptr->typename,yyvsp[-3].stackptr->lexeme);
		      SymtabInsertType(yyvsp[-1].typeptr);
		     }	
		   }
		    else printf("\n Not inserting type due to error in defn");	
		}
break;
case 54:
#line 474 "pas.y"
{ printf("\n new type ");
		  yyval.typeptr = yyvsp[0].typeptr;
		}
break;
case 55:
#line 478 "pas.y"
{ /*printf("\n id");*/
		  Typeptr temp;
		  temp=SymtabIsTypePresent(yyvsp[0].stackptr->lexeme);
		  if(temp!=NULL) 
		  {  yyval.typeptr=(Typeptr)malloc(sizeof(Type));
		      *yyval.typeptr=*temp; 
		     yyval.typeptr->nxt=NULL;
		   }
		   else
		   {  error(INVALID_TYPEDEF); 
			yyval.typeptr=NULL;
		    }
		}
break;
case 56:
#line 495 "pas.y"
{ printf("\n new_ordinal_type");
		  yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 57:
#line 499 "pas.y"
{ printf("\n new_structured_type");
		 yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 58:
#line 503 "pas.y"
{ printf("\n new_pointer_type");
		 yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 59:
#line 510 "pas.y"
{ printf("\n enum_type");
		   yyval.typeptr=yyvsp[0].typeptr;	
		}
break;
case 60:
#line 514 "pas.y"
{ printf("\n subrange_type");
		 yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 61:
#line 521 "pas.y"
{ printf("\n (id_list)");
		  yyval.typeptr=SymtabCreateNewType(ENUM_TYPE,yyvsp[-1].idptr);
		  free(yyvsp[-2].stackptr); free(yyvsp[0].stackptr);
		}
break;
case 62:
#line 529 "pas.y"
{ printf("\n const..const");
		  yyval.typeptr=SymtabCreateNewType(SUBRANGE_TYPE,yyvsp[-2].constptr,yyvsp[0].constptr);
		  free(yyvsp[-1].stackptr);
		}
break;
case 63:
#line 537 "pas.y"
{ printf("\n structured_type");
		 yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 64:
#line 541 "pas.y"
{ printf("\n packed structured_type");
		yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 65:
#line 549 "pas.y"
{ printf("\n array_type");
		  yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 66:
#line 553 "pas.y"
{ printf("\n record_type");
		yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 67:
#line 557 "pas.y"
{ printf("\n set_type");
		yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 68:
#line 561 "pas.y"
{ printf("\n file_type");
		yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 69:
#line 568 "pas.y"
{ printf("\n array[index_list] of compo_type");
		  if(yyvsp[-3].typeptr && yyvsp[0].typeptr ) 
			yyval.typeptr=SymtabCreateNewType(ARRAY_TYPE,yyvsp[-3].typeptr,yyvsp[0].typeptr);
		  else 
			yyval.typeptr=NULL; 
		 free(yyvsp[-5].stackptr); free(yyvsp[-4].stackptr); free(yyvsp[-2].stackptr); free(yyvsp[-1].stackptr);
		}
break;
case 70:
#line 579 "pas.y"
{ printf("\n index_list , index_type");
		temptype=yyvsp[-2].typeptr;
		  if(temptype!=NULL)
		  {
	        	while(temptype->nxt!=NULL) 
				temptype=temptype->nxt;
			temptype->nxt=yyvsp[0].typeptr;
			yyval.typeptr=yyvsp[-2].typeptr;
		  } else 
			yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 71:
#line 591 "pas.y"
{ 
		  printf("\n index_type");
  		   yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 72:
#line 600 "pas.y"
{ printf("\n ordinal_type");
		 yyval.typeptr=yyvsp[0].typeptr;  
		}
break;
case 73:
#line 607 "pas.y"
{ printf("\n new_ordinal_type");
		 yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 74:
#line 611 "pas.y"
{ Typeptr temp;  /* this id should be prev_defined ordinal_type*/
			/*	   printf("\n----id= %s ---",$1->lexeme);*/
			/*	  SymtabPrintTypeList();*/
		  temp=SymtabIsTypePresent(yyvsp[0].stackptr->lexeme);
		  if(temp!=NULL)
		  {    if(SymtabIsOrdinalType(temp->type_type))
			  yyval.typeptr=SymtabCreateNewType(EXISTING,temp);
		        else{
			  error(NON_ORDINAL_TYPE);	
			  yyval.typeptr=NULL;
			}
		   }
                   else {
			error(INVALID_TYPEDEF);
			yyval.typeptr=NULL;
		   }
		 }
break;
case 75:
#line 632 "pas.y"
{ printf("\n type_denoter");
		  yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 76:
#line 639 "pas.y"
{
		  printf("\n record record_section_list end");
		 if(yyvsp[-1].varptr)
		  yyval.typeptr=SymtabCreateNewType(RECORD_TYPE,1,yyvsp[-1].varptr);
		 else 
		   yyval.typeptr=NULL;
		SymtabPrintVarlist(yyvsp[-1].varptr);
 		}
break;
case 77:
#line 648 "pas.y"
{
		  printf("\n record record_section_list;variant_part end");
		if(yyvsp[-3].varptr)
		  yyval.typeptr=SymtabCreateNewType(RECORD_TYPE,2,yyvsp[-3].varptr,yyvsp[-1].typeptr);
		else 
		  yyval.typeptr=NULL;
		SymtabPrintVarlist(yyvsp[-3].varptr);
		}
break;
case 78:
#line 657 "pas.y"
{ 
		  printf("\n record variant_part end");
		 if(yyvsp[-1].typeptr)
		   yyval.typeptr=SymtabCreateNewType(RECORD_TYPE,3,yyvsp[-1].typeptr);
		 else 
		   yyval.typeptr=NULL;
		}
break;
case 79:
#line 669 "pas.y"
{ 
		 yyval.varptr=SymtabAppendToVarlist(yyvsp[-2].varptr,yyvsp[0].varptr);
		printf("\n record_section_list, record_section");
		}
break;
case 80:
#line 674 "pas.y"
{ printf("\n record_section");
		  yyval.varptr=yyvsp[0].varptr;
		}
break;
case 81:
#line 681 "pas.y"
{ printf("\n id_list : type_denoter");
	      if(yyvsp[0].typeptr && yyvsp[-2].idptr)	
	      {	  Idptr tempid; 
		  Varptr tempvar,head=NULL;
	          tempid=yyvsp[-2].idptr;
		  while(tempid!=NULL)
		  {  tempvar=SymtabCreateNewVar(tempid->idname,yyvsp[0].typeptr);
		     head=SymtabAppendToVarlist(head,tempvar);
		     tempid=tempid->nxt;	
		  }
		yyval.varptr=head;
	       }
		else 
		{ printf("\n p2c: not inserting varlist in record defdue to ");
		  if(yyvsp[-2].idptr==NULL) printf("$1");
		  if(yyvsp[0].typeptr==NULL) printf(" and $3 ");
			yyval.varptr=NULL;
		}
				
	    }
break;
case 82:
#line 705 "pas.y"
{ printf("\n case var_selectror of var_list ;");
		 printf("\n p2c: variant records not suported yet ");
		 exit(0);
		}
break;
case 83:
#line 710 "pas.y"
{ printf("\n case var_selector of var_list");
		 printf("\n p2c: variant records not suported yet ");
		 exit(0);
		}
break;
case 84:
#line 715 "pas.y"
{ printf("\n empty variant_part");
		 printf("\n p2c:variant records  not suported yet ");
		 exit(0);
		}
break;
case 85:
#line 725 "pas.y"
{ printf("\n tag_field : tag_type");
		}
break;
case 86:
#line 728 "pas.y"
{ printf("\n tag_type");
		}
break;
case 87:
#line 734 "pas.y"
{ printf("\n variant_list ; variant");
		}
break;
case 88:
#line 737 "pas.y"
{ printf("\n variant");
		}
break;
case 89:
#line 743 "pas.y"
{ printf("\n case_const_list : (record_section_list) ");
		}
break;
case 90:
#line 747 "pas.y"
{ printf("\n case_const_list :\
			( record_section_list ;variant_part) ");
		}
break;
case 91:
#line 751 "pas.y"
{ printf("\n case_const_list : ( variant_part ) ");
		}
break;
case 92:
#line 757 "pas.y"
{ Constptr ptr;
		printf("\n case_const_list , case_const");
		if(yyvsp[-2].constptr==NULL) yyvsp[-2].constptr=yyvsp[0].constptr;
		else{
			ptr=yyvsp[-2].constptr;
			while(ptr->nxt) ptr=ptr->nxt;
			ptr->nxt=yyvsp[0].constptr;
		}
		if(yyvsp[-2].constptr->const_type==yyvsp[0].constptr->const_type)
			yyval.constptr=yyvsp[-2].constptr;		
		else yyval.constptr=NULL;
		}
break;
case 93:
#line 770 "pas.y"
{ printf("\n case_const");
		 yyval.constptr=yyvsp[0].constptr;
		}
break;
case 94:
#line 777 "pas.y"
{ printf("\n const");
		 yyval.constptr=yyvsp[0].constptr;
		}
break;
case 95:
#line 781 "pas.y"
{ printf("\n const..const");
		  yyval.constptr=MakeConstList(yyvsp[-2].constptr,yyvsp[0].constptr);
		}
break;
case 96:
#line 788 "pas.y"
{ /*printf("\n id");*/
		}
break;
case 97:
#line 794 "pas.y"
{ /*printf("\n id");*/
		}
break;
case 98:
#line 800 "pas.y"
{ printf("\n SET of base_type");
		  if(yyvsp[0].typeptr!=NULL) 
			yyval.typeptr=SymtabCreateNewType(SET_TYPE,yyvsp[0].typeptr);
		  else yyval.typeptr=NULL;
		}
break;
case 99:
#line 809 "pas.y"
{ printf("\n ordinal_type");
		  yyval.typeptr=yyvsp[0].typeptr;
		}
break;
case 100:
#line 816 "pas.y"
{ printf("\n FILE OF compo_type");
		if(yyvsp[-1].stackptr!=NULL)
			yyval.typeptr=SymtabCreateNewType(FILE_TYPE,yyvsp[0].typeptr);
		else yyval.typeptr=NULL;
		}
break;
case 101:
#line 825 "pas.y"
{ Typeptr temp;
		printf("\n ^domain_type");
		if(temp=SymtabIsTypePresent(yyvsp[0].stackptr->lexeme))
			yyval.typeptr=SymtabCreateNewType(POINTER_TYPE,temp,0);
		 else 
			yyval.typeptr=SymtabCreateNewType(POINTER_TYPE,NULL,yyvsp[0].stackptr->lexeme);	
		}
break;
case 102:
#line 836 "pas.y"
{ /*printf("\n id");*/
		yyval.stackptr=yyvsp[0].stackptr;
		}
break;
case 103:
#line 843 "pas.y"
{ printf("\n VAR var_decl_list ;");
		  SymtabAddVarDecllist(yyvsp[-1].varptr);
		  printf("\n current funcitons varlist");
		  SymtabPrintVarlist(currfun->varlist);	
		}
break;
case 104:
#line 849 "pas.y"
{ printf("\n empty var_decl_part");
		}
break;
case 105:
#line 855 "pas.y"
{ printf("\n var_decl_list ; var_decl");
		 yyval.varptr=SymtabAppendToVarlist(yyvsp[-2].varptr,yyvsp[0].varptr);
		}
break;
case 106:
#line 859 "pas.y"
{ printf("\n var_decl");
		 yyval.varptr=yyvsp[0].varptr;
		}
break;
case 107:
#line 866 "pas.y"
{ printf("\n id_list : type_denoter");
	      if(yyvsp[0].typeptr && yyvsp[-2].idptr)	
	      {	  Idptr tempid; 
		  Varptr tempvar,head=NULL;
	          tempid=yyvsp[-2].idptr;
		  while(tempid!=NULL)
		  {  tempvar=SymtabCreateNewVar(tempid->idname,yyvsp[0].typeptr);
		     if(SymtabIsNameDefined(tempid->idname))
			error(DUPLICATE_DECLARATION);
		     head=SymtabAppendToVarlist(head,tempvar);
		     tempid=tempid->nxt;	
		  }
		yyval.varptr=head;
	       }
		else 
		{ printf("\n p2c: not inserting varlist in record defdue to ");
		  if(yyvsp[-2].idptr==NULL) printf("$1");
		  if(yyvsp[0].typeptr==NULL) printf(" and $3 ");
			yyval.varptr=NULL;
		}
				
	    }
break;
case 108:
#line 892 "pas.y"
{ printf("\n proc_and_func decl ; ");
		 printf("\n------------proc adn funcdecl -------------------");
		}
break;
case 109:
#line 896 "pas.y"
{ printf("\n empty proc_or_func decl_list");
		}
break;
case 110:
#line 902 "pas.y"
{ printf("\n proc_or_func_decl ; proc_func_decl");
		}
break;
case 111:
#line 905 "pas.y"
{ printf("\n proc_or_func decl");
		}
break;
case 112:
#line 911 "pas.y"
{ printf("\n proc_decl");
		 printf("\n------------proc decl -------------------");
		    PrintConstUndef();
		   func_level--;
		   SymtabDecrCurrFuncPtr();
		}
break;
case 113:
#line 918 "pas.y"
{ printf("\n func_decl");
		 printf("\n------------func decl -------------------");
		    PrintConstUndef();
		  func_level--;	
		   SymtabDecrCurrFuncPtr();
		}
break;
case 114:
#line 928 "pas.y"
{ printf("\n proc_heading ; directive");
		  
		}
break;
case 115:
#line 932 "pas.y"
{ printf("\n proc_head ; proc_block");
		}
break;
case 116:
#line 938 "pas.y"
{ printf("\n proc_id");
		}
break;
case 117:
#line 941 "pas.y"
{ printf("\n proc_id formal_param_list");
		  SymtabAddArgDecllist(yyvsp[0].argptr);
		  SymtabPrintArglist();
		}
break;
case 118:
#line 948 "pas.y"
{ 
    	          func_level++;
		}
break;
case 119:
#line 952 "pas.y"
{ printf("\n PROCEDRE id");
		  printf("\n before procinsert procname=%s",yyvsp[0].stackptr->lexeme);
		  SymtabInsertProcedure(yyvsp[0].stackptr->lexeme);
		}
break;
case 122:
#line 965 "pas.y"
{ printf("\n ( formal_param_section_list) ");
		yyval.argptr=yyvsp[-1].argptr;
		}
break;
case 123:
#line 972 "pas.y"
{ printf("\n formal_param_section_list ; formal_param_section");
		 yyval.argptr=SymtabAppendToArglist(yyvsp[-2].argptr,yyvsp[0].argptr);
		}
break;
case 124:
#line 976 "pas.y"
{ printf("\n formal_param_section");
		yyval.argptr=yyvsp[0].argptr;
		}
break;
case 125:
#line 983 "pas.y"
{ printf("\n value_param");
		 yyval.argptr=yyvsp[0].argptr;
		}
break;
case 126:
#line 987 "pas.y"
{ printf("\n var parameter");
		 yyval.argptr=yyvsp[0].argptr;
		}
break;
case 127:
#line 991 "pas.y"
{ printf("\n procedure_param");
		yyval.argptr=NULL;
		 printf("\n p2c: procedure parametrs not suported yet ");
		 exit(0);
		}
break;
case 128:
#line 997 "pas.y"
{ printf("\n func_param");
		 printf("\n p2c: function parametrs not suported yet ");
		 exit(0);
		}
break;
case 129:
#line 1005 "pas.y"
{ printf("\n id_list : id ");
	          if(yyvsp[-2].idptr)
	       	  {  Idptr tempid;Typeptr tmp;
        	     Argptr temparg,head=NULL;
                     tempid=yyvsp[-2].idptr;
		     tmp=SymtabIsTypePresent(yyvsp[0].stackptr->lexeme);
		     if(tmp)
 		     {
                       while(tempid!=NULL)
                       {    temparg=
	                     SymtabCreateNewArg(tempid->idname,VALUE_PARAM,tmp);
                           head=SymtabAppendToArglist(head,temparg);
                           tempid=tempid->nxt;
                       }
                       yyval.argptr=head;
		      }
		      else 
		      { error(INVALID_TYPEDEF); 
		        yyval.argptr=NULL;
		      }	
                  }
                  else
                  { 
		    printf("\n p2c:not inserting varlist in record \
						defdue to $1=NULL");
                        yyval.argptr=NULL;
                   }
		}
break;
case 130:
#line 1037 "pas.y"
{ printf("\n VAR id_list : id ");
                  if(yyvsp[-2].idptr)
                  {  Idptr tempid;Typeptr tmp;
                     Argptr temparg,head=NULL;
                     tempid=yyvsp[-2].idptr;
                     tmp=SymtabIsTypePresent(yyvsp[0].stackptr->lexeme);
                     if(tmp)
                     {
                      while(tempid!=NULL)
                      {    temparg=
                             SymtabCreateNewArg(tempid->idname,VAR_PARAM,tmp);
                           head=SymtabAppendToArglist(head,temparg);
                           tempid=tempid->nxt;
                      }
                      yyval.argptr=head;
                     }
                     else
                     { error(INVALID_TYPEDEF);
                       yyval.argptr=NULL;
                     }
                  }
                  else
                  {
                    printf("\n p2c:not inserting varlist in record \
                                                defdue to $1=NULL");
                        yyval.argptr=NULL;
                   }
                }
break;
case 131:
#line 1070 "pas.y"
{ printf("\n proc_heading");
		}
break;
case 132:
#line 1076 "pas.y"
{ printf("\n func_heading");
		}
break;
case 133:
#line 1083 "pas.y"
{ printf("\n proc_block");
		}
break;
case 134:
#line 1089 "pas.y"
{ printf("\n func_heading ; directive");
		}
break;
case 135:
#line 1092 "pas.y"
{ printf("\n func_head ; func_block");
		}
break;
case 136:
#line 1098 "pas.y"
{ printf("\n FUNCTION id : result_type");
		  func_level++;
		  SymtabInsertFunction(yyvsp[-2].stackptr->lexeme);
		  SymtabAddFuncRetType(yyvsp[0].typeptr); /* check that this is not null*/
		   PrintFwdDecl();
		}
break;
case 137:
#line 1105 "pas.y"
{
		  func_level++;
		  SymtabInsertFunction(yyvsp[0].stackptr->lexeme);
		}
break;
case 138:
#line 1110 "pas.y"
{ printf("\n FUNCTION id formal_param_list : result_type");
		  SymtabAddArgDecllist(yyvsp[-2].argptr);
		  SymtabPrintArglist();
		  SymtabAddFuncRetType(yyvsp[0].typeptr); /* check that this is not null*/
		 PrintFwdDecl();	
		}
break;
case 139:
#line 1120 "pas.y"
{ /*printf("\n id");*/
		  Typeptr temp;
		   temp=SymtabIsTypePresent(yyvsp[0].stackptr->lexeme);
		 if(temp) 
			yyval.typeptr=temp;
		 else { yyval.typeptr=NULL;
			 error(INVALID_TYPEDEF);
		  }
		}
break;
case 140:
#line 1132 "pas.y"
{ printf("\n func_block");
		}
break;
case 141:
#line 1138 "pas.y"
{ printf("\n compund_statement");
		}
break;
case 142:
#line 1143 "pas.y"
{ 
		 if(BLOCK_IS_FUNC_FLAG)
		  { PrintFuncHeader();}
		PrintOpenBrace();
		++indent;
		 if(BLOCK_IS_FUNC_FLAG)
		 { PrintFuncLocalVar();
		   BLOCK_IS_FUNC_FLAG=0;		
		  }
		}
break;
case 143:
#line 1154 "pas.y"
{
		 printf("\n BEGIN stat_seq END ");
		--indent; if(indent==0) PrintFuncRetStat();
		PrintCloseBrace();	
		}
break;
case 144:
#line 1163 "pas.y"
{ printf("\n state_seq ; stat ");
		}
break;
case 145:
#line 1166 "pas.y"
{ printf("\n stat");
		   printf("\n--------------statment-------------------------");
		}
break;
case 146:
#line 1173 "pas.y"
{ printf("\n label : non_label_open_stat");
		}
break;
case 147:
#line 1176 "pas.y"
{ printf("\n non_label_open_stat");
		}
break;
case 148:
#line 1183 "pas.y"
{ printf("\n assignment stat");
		  yyval.voidptr=yyvsp[0].voidptr;
		}
break;
case 149:
#line 1187 "pas.y"
{ printf("\n procedure stat");
		}
break;
case 150:
#line 1190 "pas.y"
{ printf("\n goto stat ");
		}
break;
case 151:
#line 1193 "pas.y"
{ printf("\n compound stat");
		}
break;
case 152:
#line 1196 "pas.y"
{ printf("\n case stat");
		}
break;
case 153:
#line 1199 "pas.y"
{ printf("\n repeat stat");
		}
break;
case 154:
#line 1202 "pas.y"
{ printf("\n closed with stat ");
		}
break;
case 155:
#line 1205 "pas.y"
{ printf("\n closed if stat");
		}
break;
case 156:
#line 1208 "pas.y"
{ printf("\n closed while stat");
		}
break;
case 157:
#line 1211 "pas.y"
{ printf("\n closed_for_stat ");
		}
break;
case 158:
#line 1214 "pas.y"
{ printf("\n empty stat");
		}
break;
case 159:
#line 1220 "pas.y"
{ Print("\n");PrintIndent();Print("do{");++indent;
		}
break;
case 160:
#line 1223 "pas.y"
{ Print("\n");--indent;PrintIndent();Print("}while");
		}
break;
case 161:
#line 1226 "pas.y"
{ 
		Print("(");Print("!(");Print(yyvsp[0].chkptr->string);Print("));");
		printf("\n REPEAT stat_seq UNTIL bool_expr ");
		}
break;
case 162:
#line 1235 "pas.y"
{ Print("\n"); PrintIndent();Print("while(");
	  Print(yyvsp[-1].chkptr->string);Print(")");indent++;	
	}
break;
case 163:
#line 1239 "pas.y"
{ printf("\n WHILE bool_expr DO closed_stat");
		indent--;
		}
break;
case 164:
#line 1247 "pas.y"
{ int i;printf("\n FOR ctrl_var := init_value direction final_value DO");
	  Print("\n"); PrintIndent();
	  Print("for("); Print(yyvsp[-5].chkptr->string);Print("=");Print(yyvsp[-3].chkptr->string);
	  Print(";"); Print(yyvsp[-5].chkptr->string);
	  if((mystrcmp(yyvsp[-2].stackptr->lexeme,"to"))==0)
	  	Print("<="); 
	  else  Print(">=");
	  Print(yyvsp[-1].chkptr->string); Print(";"); Print(yyvsp[-5].chkptr->string);
	  if((mystrcmp(yyvsp[-2].stackptr->lexeme,"to"))==0) 
		Print("++");
	  else Print("--");
	  Print(")"); ++indent;
	}
break;
case 165:
#line 1261 "pas.y"
{--indent;}
break;
case 166:
#line 1267 "pas.y"
{ printf("\n WITH record_var_list DO  closed_stat");
		}
break;
case 168:
#line 1276 "pas.y"
{ Print("\n");PrintIndent(); Print("if(");  
		/*printf("after if("); getchar(); getchar();*/
		Print(yyvsp[-1].chkptr->string); Print(")"); indent++;
		}
break;
case 169:
#line 1280 "pas.y"
{ indent--;}
break;
case 170:
#line 1284 "pas.y"
{ Print("\n"); PrintIndent(); Print("else");	 indent++;
		}
break;
case 171:
#line 1287 "pas.y"
{ printf("\n IF bool_expr THEN closed_stat ELSE closed_stat");
		indent--;
		}
break;
case 173:
#line 1295 "pas.y"
{ 
		printf("\n var_acess := expr "); getchar();
  if((yyvsp[-2].chkptr->type->type_type==yyvsp[0].chkptr->type->type_type)||
    ((yyvsp[-2].chkptr->type->type_type==SUBRANGE_TYPE||yyvsp[-2].chkptr->type->type_type==INTEGER_TYPE) &&
     (yyvsp[0].chkptr->type->type_type==INTEGER_TYPE ||yyvsp[0].chkptr->type->type_type==SUBRANGE_TYPE)))
		  {
			if(yyvsp[-2].chkptr->type->type_type==INTEGER_TYPE||
			   yyvsp[-2].chkptr->type->type_type==REAL_TYPE||
			   yyvsp[-2].chkptr->type->type_type==BOOLEAN_TYPE||
			   yyvsp[-2].chkptr->type->type_type==SUBRANGE_TYPE||
			   yyvsp[-2].chkptr->type->type_type==POINTER_TYPE||
			   (yyvsp[-2].chkptr->type->type_type==RECORD_TYPE && 
			mystrcmp(yyvsp[-2].chkptr->type->typename,yyvsp[0].chkptr->type->typename)==0))
			{ Print("\n");PrintIndent();
			  Print(yyvsp[-2].chkptr->string); Print("=");
			  Print(yyvsp[0].chkptr->string); Print(";");
			}
			else tperror(ASSIGNMENT_STAT_WRONG_TYPE);
		  }
		  else tperror(ASSIGNMENT_STAT_TYPE_MISMATCH);	
		}
break;
case 174:
#line 1321 "pas.y"
{ /*printf("\n id"); */
	      int currlevel,foundlevel,i,type,j;
	      char buf[128];	
              yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));yyval.chkptr->nxt=NULL;
	      yyval.chkptr->type=TpCheckGetTypePtr(
		 yyvsp[0].stackptr->lexeme,&currlevel,&foundlevel,&type,buf);
	     if(yyval.chkptr->type)
	     {	
		if(foundlevel!=0 && type!=6){ /* i.e. not a global var*/
						/* and not enum value*/
		  j=currlevel-foundlevel;
		  i=(currlevel-foundlevel)*8+(type==2)*3;
		  yyval.chkptr->string=(char *)malloc(strlen(yyvsp[0].stackptr->lexeme)+1+i);
		  strcpy(yyval.chkptr->string,""); /* for strcat to be useful*/
		  if(type==2 && yyval.chkptr->type->type_type!=ARRAY_TYPE) 
			strcat(yyval.chkptr->string,"(*");
		  while(j--)
		    strcat(yyval.chkptr->string,"SCP->");	
		  if(type==1) 
			{   if(currlevel==foundlevel) strcat(yyval.chkptr->string,"W.");
			strcat(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);}
		  else if(type==2 || type==3 || type==4) 
			strcat(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);
		  else if(type==5) 
			strcat(yyval.chkptr->string,buf);
		  if(type==2 && yyval.chkptr->type->type_type!=ARRAY_TYPE) 
			strcat(yyval.chkptr->string,")");	
		}
		else { 
			  yyval.chkptr->string=(char *)malloc(strlen(yyvsp[0].stackptr->lexeme)+1);
			  strcpy(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);
		}
	     }
	     else tperror(DECL_NOT_FOUND,yyvsp[0].stackptr->lexeme);
	   }
break;
case 175:
#line 1357 "pas.y"
{ printf("\n indexed var ");
		 yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 176:
#line 1361 "pas.y"
{ printf("\n field designator ");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 177:
#line 1365 "pas.y"
{ printf("\n var_access ^ ");
		 if(yyvsp[-1].chkptr->type->type_type!=POINTER_TYPE)
			tperror(TYPE_IS_NOT_POINTER,yyvsp[-1].chkptr->string);	
		 yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck)); yyval.chkptr->nxt=NULL;
		 yyval.chkptr->type=yyvsp[-1].chkptr->type->typeptr;
		 yyval.chkptr->string=(char *)malloc(strlen(yyvsp[-1].chkptr->string)+5);
		 strcpy(yyval.chkptr->string,"(*");
		 strcat(yyval.chkptr->string,yyvsp[-1].chkptr->string);
		 strcat(yyval.chkptr->string,")");
		}
break;
case 178:
#line 1379 "pas.y"
{ 
		  Typecheckptr temp;int count=0,strlencount=0;
		  char *chptr,buf[120];	
		printf("\n var_acess [ index_expr_list ] "); getchar();
		  if(yyvsp[-3].chkptr->type->type_type!=ARRAY_TYPE)
			tperror(TYPE_IS_NOT_ARRAY,yyvsp[-3].chkptr->string);	
		  temp=yyvsp[-1].chkptr;
		  while(temp) 
		  {     
			++count; 
			strlencount+=strlen(temp->string)+3+32;
			/*+32 for adding the string for substracting lower bound*/
			if(!SymtabIsOrdinalType(temp->type->type_type)) 
		  	    tperror(ARRAY_SUBSCR_NOT_INTEGER); 	  
			temp=temp->nxt; 
		  }
		  if(count!=yyvsp[-3].chkptr->type->no_of_dimn)
			tperror(ARRAY_WRONG_NO_OF_INDEX);	
		  yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));	yyval.chkptr->nxt=NULL;
		  yyval.chkptr->type=yyvsp[-3].chkptr->type->elemtype;
		  yyval.chkptr->string=(char *)malloc(strlencount+1);
		  strcpy(yyval.chkptr->string,yyvsp[-3].chkptr->string);
		  temp=yyvsp[-1].chkptr; count=0;
		  while(temp)
		  { 
		    strcat(yyval.chkptr->string,"[(");
		    strcat(yyval.chkptr->string,temp->string);		
		    strcat(yyval.chkptr->string,")");	
		    TpCheckGetArrayLimitDiff(yyvsp[-3].chkptr->type,count,buf);
		    strcat(yyval.chkptr->string,buf);	
		    strcat(yyval.chkptr->string,"]");
			++count; 
		    temp=temp->nxt;
		  }
		}
break;
case 179:
#line 1418 "pas.y"
{ 
		  Typecheckptr temp;
		  printf("\n index_expr_list , index_expr");
		  if(yyvsp[-2].chkptr==NULL) yyvsp[-2].chkptr=yyvsp[0].chkptr;
		  else 
		  { temp=yyvsp[-2].chkptr;
		    while(temp->nxt) 
			temp=temp->nxt;	
		    temp->nxt=yyvsp[0].chkptr; 
		 } 
		    yyval.chkptr=yyvsp[-2].chkptr;
		}
break;
case 180:
#line 1431 "pas.y"
{ printf("\n index_expr");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 181:
#line 1438 "pas.y"
{ printf("\n expr");
		 yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 182:
#line 1445 "pas.y"
{ Typeptr temp;
	  printf("\n var_access . id ");
	  if(yyvsp[-2].chkptr->type->type_type!=RECORD_TYPE)
	 	tperror(TYPE_IS_NOT_RECORD);
	  temp=TpCheckIsRecField(yyvsp[-2].chkptr->type,yyvsp[0].stackptr->lexeme);
	  if(temp)
	  {  yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck)); 
	     yyval.chkptr->nxt=NULL;
	     yyval.chkptr->type=temp;
	     yyval.chkptr->string=(char*)malloc(strlen(yyvsp[-2].chkptr->string)+strlen(yyvsp[0].stackptr->lexeme)+3);
	     strcpy(yyval.chkptr->string,yyvsp[-2].chkptr->string);strcat(yyval.chkptr->string,yyvsp[-1].stackptr->lexeme);
	     strcat(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);			
	      printf("right here "); getchar(); getchar();	
	  } 
	  else 
		tperror(RECORD_FIELD_NOT_EXIST,yyvsp[-2].chkptr->string,yyvsp[0].stackptr->lexeme);
	}
break;
case 183:
#line 1466 "pas.y"
{ /*printf("\n id");*/
	   int currlevel,proclevel,i,no_of_arg,is_func; 
	   Argptr aptr;Typeptr tptr;
	   Typecheckptr temp; int count=0;
	  if(!TpCheckIsStdFunc(yyvsp[-1].stackptr->lexeme))
	 {
	   if(aptr=TpCheckIsProcInScope(yyvsp[-1].stackptr->lexeme,&currlevel,
			&proclevel,&no_of_arg,&is_func,&tptr))
	   {	Print("\n"); PrintIndent();Print(yyvsp[-1].stackptr->lexeme);Print("(");
		temp=yyvsp[0].chkptr;
		while(temp) { ++count; temp=temp->nxt;}
		if(count!=no_of_arg)
			tperror(PROC_WRONG_NO_OF_ARG);
		temp=yyvsp[0].chkptr;
		while(temp)
		{ if((mystrcmp(aptr->type->typename,temp->type->typename)==0)||
			(temp->type->type_type==SUBRANGE_TYPE 
			&& aptr->type->type_type==INTEGER_TYPE)||
			(temp->type->type_type==INTEGER_TYPE 
			&& aptr->type->type_type==SUBRANGE_TYPE))
		  {	
			  if(aptr->arg_type==VAR_PARAM && 
				aptr->type->type_type!=ARRAY_TYPE)
			    Print("&");
			  Print(temp->string);	 
			  if(temp->nxt) Print(",");
		   }
		  else tperror(PROC_WRONG_TYPE_ARG);		
		  aptr=aptr->nxt; temp=temp->nxt;
		}
		if(currlevel)
		{
			if(currlevel==proclevel-1)  /* child called*/
			{	if(no_of_arg) Print(",");  
				Print("&W");Print(");");
			 }
			else{ 
			 if(proclevel>1){
			   i=currlevel-proclevel+1;
			   if(no_of_arg)	Print(",");
			   while(--i)
				Print("SCP->");
			   Print("SCP);");	
			  } else Print(");");	
			}
		}
	       else { Print(");");
		}
	    }
	   else tperror(FUNC_NOT_IN_SCOPE,yyvsp[-1].stackptr->lexeme);	
	 } 
	 else PrintStdFuncCall(yyvsp[-1].stackptr->lexeme,yyvsp[0].chkptr,NO);
	 }
break;
case 184:
#line 1520 "pas.y"
{ /*printf("\n id");*/
	   int currlevel,proclevel,i;
	 if(!TpCheckIsStdFunc(yyvsp[0].stackptr->lexeme))
	 {	
	   if(TpCheckIsProcInScope(yyvsp[0].stackptr->lexeme,&currlevel,&proclevel))
	   {	Print("\n"); PrintIndent();Print(yyvsp[0].stackptr->lexeme);
		if(currlevel){
			if(currlevel==proclevel-1)  /* child called*/
				{ Print("("); Print("&W");Print(");");}
			else{ Print("(");
			  if(proclevel>1)
			 {
			 	  i=currlevel-proclevel+1; 
				   while(--i)
					Print("SCP->");
				   Print("SCP);");	
			  } else Print(");");
			}
		}
	       else { Print("();");
		}
	    }
	   else tperror(FUNC_NOT_IN_SCOPE,yyvsp[0].stackptr->lexeme);	
	 } else 
	  PrintStdFuncCall(yyvsp[0].stackptr->lexeme,NULL,NO);
	 }
break;
case 185:
#line 1550 "pas.y"
{ printf("\n ( act_param_list )");
		 yyval.chkptr=yyvsp[-1].chkptr;
		}
break;
case 186:
#line 1557 "pas.y"
{ 
		  Typecheckptr temp;
		   printf("\n act_param_list , act_param");
		  if(yyvsp[-2].chkptr==NULL) yyvsp[-2].chkptr=yyvsp[0].chkptr;
		  else 
		  { temp=yyvsp[-2].chkptr;
		    while(temp->nxt) 
			temp=temp->nxt;	
		    temp->nxt=yyvsp[0].chkptr; 
		 } 
		    yyval.chkptr=yyvsp[-2].chkptr;
		}
break;
case 187:
#line 1570 "pas.y"
{ printf("\n act_param");
		yyval.chkptr=yyvsp[0].chkptr;	yyval.chkptr->nxt=NULL;
		}
break;
case 188:
#line 1582 "pas.y"
{ printf("\n expr ");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 189:
#line 1586 "pas.y"
{ printf("\n expr : expr ");
		  printf("\n line:%d field widths not handled yet",line_no);
		  exit(0);	
		}
break;
case 190:
#line 1591 "pas.y"
{ printf("\n expr : expr : expr ");
		  printf("\n line:%d field widths not handled yet",line_no);
		  exit(0);	
		}
break;
case 191:
#line 1599 "pas.y"
{ printf("\n GOTO label ");
		   Print("\n");PrintIndent();Print("goto   x");
		   Print(yyvsp[0].stackptr->lexeme);	Print(";");
		}
break;
case 193:
#line 1608 "pas.y"
{
		Print("\n");PrintIndent();
		Print("switch(");Print(yyvsp[-1].chkptr->string);Print(")");
		PrintOpenBrace();indent++;
		}
break;
case 194:
#line 1615 "pas.y"
{ printf("\n CASE case_index OF case_list_elem_list END ");
		 --indent;PrintCloseBrace();
		}
break;
case 195:
#line 1619 "pas.y"
{ printf("\n CASE case_index OF case_list_elem_list ; END ");
		 --indent;PrintCloseBrace();
		}
break;
case 196:
#line 1624 "pas.y"
{Print("\n");PrintIndent();Print("default:");indent++;}
break;
case 197:
#line 1626 "pas.y"
{ printf("\n  case_list_elem_list ;otherwise_part stat END ");
		  	
		 --indent;PrintCloseBrace();
		}
break;
case 198:
#line 1634 "pas.y"
{ printf("\n expr ");
		 yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 199:
#line 1641 "pas.y"
{ printf("\n case_list_elem_list ; case_list_elem ");
		}
break;
case 200:
#line 1644 "pas.y"
{ printf("\n case_list_elem ");
		}
break;
case 201:
#line 1650 "pas.y"
{ Constptr ptr; char buf[120];
		  ptr=yyvsp[-1].constptr;
		  while(ptr)
		  { Print("\n");PrintIndent(); Print("case ");
		    if(ptr->const_type==CONST_INT)
		    {	 sprintf(buf,"%d",(int)ptr->value);
			Print(buf); Print(":");
		    }
		    else 
		    { Print("'");Print(ptr->string);Print("':");
		    }
			ptr=ptr->nxt;
		   }
		indent++;
		}
break;
case 202:
#line 1666 "pas.y"
{ printf("\n case_const_list : stat ");
		indent--; Print("\n");PrintIndent();Print("break;");
		}
break;
case 203:
#line 1672 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 204:
#line 1673 "pas.y"
{yyval.stackptr=yyvsp[-1].stackptr;}
break;
case 205:
#line 1678 "pas.y"
{   Typeptr temp;
		      int currlevel,foundlevel,i,j,type;
		char buf[120];
              yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck)); yyval.chkptr->nxt=NULL;
	      yyval.chkptr->type=TpCheckGetTypePtr(
		yyvsp[0].stackptr->lexeme,&currlevel,&foundlevel,&type,buf);
	    if(yyval.chkptr)
	   {
	      if(yyval.chkptr->type->type_type==INTEGER_TYPE)
	     {	
		if(foundlevel!=0)		 /* i.e. not a global var*/
		{
		  j=currlevel-foundlevel;
		  i=(currlevel-foundlevel)*8+(type==2)*3;
		  yyval.chkptr->string=(char *)malloc(strlen(yyvsp[0].stackptr->lexeme)+1+i);
		  strcpy(yyval.chkptr->string,""); /* for strcat to be useful*/
		  if(type==2) strcat(yyval.chkptr->string,"*(");
		  while(j--)
		    strcat(yyval.chkptr->string,"SCP->");	
		  if(type==1) 
			{   if(currlevel==foundlevel) strcat(yyval.chkptr->string,"W.");
			strcat(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);}
		  else if(type==2 || type==3 || type==4) 
			strcat(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);
		  else if(type==5) 
			strcat(yyval.chkptr->string,buf);
		  if(type==2) strcat(yyval.chkptr->string,")");	
		}
		else { 
			  yyval.chkptr->string=(char *)malloc(strlen(yyvsp[0].stackptr->lexeme)+1);
			  strcpy(yyval.chkptr->string,yyvsp[0].stackptr->lexeme);
		}
	     }		
	     else tperror(FOR_LOOP_WRONG_CTRL_VAR_TYPE);
	   } else tperror(DECL_NOT_FOUND,yyvsp[0].stackptr->lexeme);
/*	  temp=SymtabIsTypePresent($1->lexeme);
	   if(temp) 
		if(temp->type_type==INTEGER_TYPE)
			$$=$1;	
		else tperror(FOR_LOOP_WRONG_CTRL_VAR_TYPE);*/
	}
break;
case 206:
#line 1723 "pas.y"
{ printf("\n expr ");
		if(yyvsp[0].chkptr->type->type_type==INTEGER_TYPE)
		  yyval.chkptr=yyvsp[0].chkptr;
		 else tperror(FOR_LOOP_VAR_INVALID_VALUE);
		}
break;
case 207:
#line 1731 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 208:
#line 1732 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 209:
#line 1737 "pas.y"
{ printf("\n expr ");
		if(yyvsp[0].chkptr->type->type_type==INTEGER_TYPE ||
			yyvsp[0].chkptr->type->type_type==SUBRANGE_TYPE)
		  yyval.chkptr=yyvsp[0].chkptr;
		 else tperror(FOR_LOOP_VAR_INVALID_VALUE);
		}
break;
case 210:
#line 1747 "pas.y"
{ printf("\n record_var_list , var_access ");	
		}
break;
case 211:
#line 1750 "pas.y"
{ printf("\n var_access ");
		}
break;
case 212:
#line 1756 "pas.y"
{ printf("\n expr "); getchar();
		  printf("\n --------------expr---------"); getchar();
		printf("\n expr string= %s", yyvsp[0].chkptr->string); getchar(); getchar();
		printf("\n expr type= %d",yyvsp[0].chkptr->type->type_type); getchar();
		if(yyvsp[0].chkptr->type->type_type==BOOLEAN_TYPE)
		{  printf("yes.. boolean"); getchar();
			yyval.chkptr=yyvsp[0].chkptr;
		}
		else tperror(BOOLEAN_EXPR_WRONG_TYPE);
		}
break;
case 213:
#line 1770 "pas.y"
{ printf("\n simple_expr ");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 214:
#line 1774 "pas.y"
{  printf("\n simple_expr relop simple_expr ");
           if( ((yyvsp[-2].chkptr->type->type_type==INTEGER_TYPE ||
	        yyvsp[-2].chkptr->type->type_type==REAL_TYPE 	||
	        yyvsp[-2].chkptr->type->type_type==SUBRANGE_TYPE	) &&
	        (yyvsp[0].chkptr->type->type_type==INTEGER_TYPE ||
		 yyvsp[0].chkptr->type->type_type==REAL_TYPE	||
		 yyvsp[0].chkptr->type->type_type==SUBRANGE_TYPE)) ||
		(yyvsp[-2].chkptr->type->type_type==POINTER_TYPE && 
		 yyvsp[0].chkptr->type->type_type==POINTER_TYPE))
	    {
	      yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
	      yyval.chkptr->nxt=NULL;
	      yyval.chkptr->type=basic_types+3;	
	      yyval.chkptr->string=
	      (char *)malloc(strlen(yyvsp[-2].chkptr->string)+strlen(yyvsp[0].chkptr->string)+3);
	      strcpy(yyval.chkptr->string,yyvsp[-2].chkptr->string);
	      switch (yyvsp[-1].stackptr->type)
		{ case EQUAL: strcat(yyval.chkptr->string,"=="); break;
		  case NOTEQUAL: strcat(yyval.chkptr->string,"!=");break;
		  case GT: case LT: case GE: case LE:
			strcat(yyval.chkptr->string,yyvsp[-1].stackptr->lexeme);
			break;
		}
		strcat(yyval.chkptr->string,yyvsp[0].chkptr->string);
	    }
	    else tperror(COMPARISON_INVALID_OPERANDS);
	}
break;
case 215:
#line 1805 "pas.y"
{ printf("\n term ");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 216:
#line 1809 "pas.y"
{ printf("\n simple_expr addop term ");
		yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck)); yyval.chkptr->nxt=NULL;
		yyval.chkptr->string=
		(char *)malloc(strlen(yyvsp[-2].chkptr->string)+strlen(yyvsp[0].chkptr->string)+3);
		strcpy(yyval.chkptr->string,yyvsp[-2].chkptr->string);
		switch(yyvsp[-1].stackptr->type){
		   case PLUS: 
		   case MINUS:
		       if( (yyvsp[-2].chkptr->type->type_type==INTEGER_TYPE ||
			      yyvsp[-2].chkptr->type->type_type==REAL_TYPE  ||
			    yyvsp[-2].chkptr->type->type_type==SUBRANGE_TYPE) &&	
			    (yyvsp[0].chkptr->type->type_type==INTEGER_TYPE ||
			     yyvsp[0].chkptr->type->type_type==REAL_TYPE||
			    yyvsp[0].chkptr->type->type_type==SUBRANGE_TYPE))	
			strcat(yyval.chkptr->string,yyvsp[-1].stackptr->lexeme); 
			else tperror(ADD_OP_INVALID_OPERANDS);
			if(yyvsp[-2].chkptr->type->type_type==REAL_TYPE || 
			   yyvsp[0].chkptr->type->type_type==REAL_TYPE)
			  yyval.chkptr->type=basic_types+1;	
			else yyval.chkptr->type=basic_types;
			break;
		   case OR: 
			if(yyvsp[-2].chkptr->type->type_type!=BOOLEAN_TYPE||
			   yyvsp[0].chkptr->type->type_type!=BOOLEAN_TYPE)
			tperror(OR_INVALID_OPERANDS);	
			else strcat(yyval.chkptr->string,"||");
			yyval.chkptr->type=basic_types+3;
			break;
		}
		strcat(yyval.chkptr->string,yyvsp[0].chkptr->string);
		}
break;
case 217:
#line 1844 "pas.y"
{ printf("\n factor ");
		yyval.chkptr=yyvsp[0].chkptr;	
		}
break;
case 218:
#line 1848 "pas.y"
{ printf("\n term mulop factor ");
		yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));yyval.chkptr->nxt=NULL;
		yyval.chkptr->string=
		(char *)malloc(strlen(yyvsp[-2].chkptr->string)+strlen(yyvsp[0].chkptr->string)+3);
		strcpy(yyval.chkptr->string,yyvsp[-2].chkptr->string);
		switch(yyvsp[-1].stackptr->type){
		   case SLASH: 
		   case STAR:
		       if( (yyvsp[-2].chkptr->type->type_type==INTEGER_TYPE ||
			      yyvsp[-2].chkptr->type->type_type==REAL_TYPE || 	
			    yyvsp[-2].chkptr->type->type_type==SUBRANGE_TYPE) &&	
			    (yyvsp[0].chkptr->type->type_type==INTEGER_TYPE ||
			     yyvsp[0].chkptr->type->type_type==REAL_TYPE||
			    yyvsp[0].chkptr->type->type_type==SUBRANGE_TYPE))	
			strcat(yyval.chkptr->string,yyvsp[-1].stackptr->lexeme); 
			else tperror(MUL_OP_INVALID_OPERANDS);
			if(yyvsp[-2].chkptr->type->type_type==REAL_TYPE || 
			   yyvsp[0].chkptr->type->type_type==REAL_TYPE)
			  yyval.chkptr->type=basic_types+1;	
			else yyval.chkptr->type=basic_types;
			break;
		   case DIV: 
			if(yyvsp[-2].chkptr->type->type_type!=INTEGER_TYPE||
			   yyvsp[0].chkptr->type->type_type!=INTEGER_TYPE)
			tperror(DIV_INVALID_OPERANDS);	
			else strcat(yyval.chkptr->string,"/");
			yyval.chkptr->type=basic_types;
			break;
		   case MOD: 
			if(yyvsp[-2].chkptr->type->type_type!=INTEGER_TYPE||
			   yyvsp[0].chkptr->type->type_type!=INTEGER_TYPE)
			tperror(MOD_INVALID_OPERANDS);	
			else strcat(yyval.chkptr->string,"/");
			yyval.chkptr->type=basic_types;
			break;
		   case AND: 
			if(yyvsp[-2].chkptr->type->type_type!=BOOLEAN_TYPE||
			   yyvsp[0].chkptr->type->type_type!=BOOLEAN_TYPE)
			tperror(AND_INVALID_OPERANDS);	
			else strcat(yyval.chkptr->string,"&&");
			yyval.chkptr->type=basic_types+3;
			break;
		}
		strcat(yyval.chkptr->string,yyvsp[0].chkptr->string);
    	}
break;
case 219:
#line 1897 "pas.y"
{ printf("\n sign factor ");
		yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));yyval.chkptr->nxt=NULL;
		yyval.chkptr->string=(char*)malloc(strlen(yyvsp[0].chkptr->string)+4);
		strcpy(yyval.chkptr->string,yyvsp[-1].stackptr->lexeme);
		strcat(yyval.chkptr->string,yyvsp[0].chkptr->string);
		yyval.chkptr->type=yyvsp[0].chkptr->type;
		}
break;
case 220:
#line 1905 "pas.y"
{ printf("\n exponentiation ");
		yyval.chkptr=yyvsp[0].chkptr;	
		}
break;
case 221:
#line 1912 "pas.y"
{ printf("\n primary ");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 222:
#line 1916 "pas.y"
{  printf("\n primary ** exponentioan ");
	       if( (yyvsp[-2].chkptr->type->type_type==INTEGER_TYPE ||
		      yyvsp[-2].chkptr->type->type_type==REAL_TYPE ) &&	
		    (yyvsp[0].chkptr->type->type_type==INTEGER_TYPE ||
		     yyvsp[0].chkptr->type->type_type==REAL_TYPE))	
	       {
			yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));yyval.chkptr->nxt=NULL;
			yyval.chkptr->string=
			(char *)malloc(strlen(yyvsp[-2].chkptr->string)+strlen(yyvsp[0].chkptr->string)+8);
			strcpy(yyval.chkptr->string,"pwr(");
			strcat(yyval.chkptr->string,yyvsp[-2].chkptr->string);
			strcat(yyval.chkptr->string,",");
			strcat(yyval.chkptr->string,yyvsp[0].chkptr->string);
			if(yyvsp[-2].chkptr->type->type_type==REAL_TYPE || 
			   yyvsp[0].chkptr->type->type_type==REAL_TYPE)
			  yyval.chkptr->type=basic_types+1;	
			else yyval.chkptr->type=basic_types;
	       }
		else	tperror(PWR_INVALID_OPERANDS);	
	    }
break;
case 223:
#line 1940 "pas.y"
{ printf("\n var_access ");
		yyval.chkptr=yyvsp[0].chkptr;
		}
break;
case 224:
#line 1944 "pas.y"
{ char buf[120]; int len;
		  printf("\n unsinged const ");
		  yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck)); yyval.chkptr->nxt=NULL;
		  if(yyvsp[0].constptr->const_type==CONST_INT){
			sprintf(buf,"%d",(int)yyvsp[0].constptr->value);
			len=strlen(buf);
		   	yyval.chkptr->string=(char *)malloc(len+1);
		   	strcpy(yyval.chkptr->string,buf);	
			yyval.chkptr->type=basic_types;
			}
		   else if(yyvsp[0].constptr->const_type==CONST_REAL){
			sprintf(buf,"%f",yyvsp[0].constptr->value);
			len=strlen(buf);
		   	yyval.chkptr->string=(char *)malloc(len+1);
		   	strcpy(yyval.chkptr->string,buf);	
			yyval.chkptr->type=basic_types+1;
		   }
		   else { len=strlen(yyvsp[0].constptr->string);
		   	yyval.chkptr->string=(char *)malloc(len+1);
		   	strcpy(yyval.chkptr->string,yyvsp[0].constptr->string);
			yyval.chkptr->type=basic_types+2;	
		   }
		}
break;
case 225:
#line 1968 "pas.y"
{ printf("\n func_designator has not been handeled yet");
		  printf("\n In line no %d ",line_no);yyval.chkptr=yyvsp[0].chkptr;
		 /*exit(0);	*/
		}
break;
case 226:
#line 1973 "pas.y"
{ printf("\n Set Constructor has not been handeled yet");
		  printf("\n In line no %d ",line_no);
		 exit(0);	
		}
break;
case 227:
#line 1978 "pas.y"
{ printf("\n (expr)");
		 yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
	      yyval.chkptr->nxt=NULL;
		 yyval.chkptr->type=yyvsp[-1].chkptr->type;
		 yyval.chkptr->string=(char *)malloc(strlen(yyvsp[-1].chkptr->string)+3);
		 strcpy(yyval.chkptr->string,"("); strcat(yyval.chkptr->string,yyvsp[-1].chkptr->string);
		 strcat(yyval.chkptr->string,")");	
		}
break;
case 228:
#line 1987 "pas.y"
{ printf("\n !primary");
		   if(yyvsp[0].chkptr->type->type_type==BOOLEAN_TYPE)
		   {
		 	yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck)); 
			yyval.chkptr->nxt=NULL;
			 yyval.chkptr->string=(char *)malloc(strlen(yyvsp[0].chkptr->string)+5);
			 strcpy(yyval.chkptr->string,"!(");
			 strcat(yyval.chkptr->string,yyvsp[0].chkptr->string);
			strcat(yyval.chkptr->string,")");
			 yyval.chkptr->type=basic_types+3;
		  } 
			else 
			tperror(NOT_INVALID_OPERAND);
			
		}
break;
case 229:
#line 2003 "pas.y"
{ yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
		  yyval.chkptr->string=(char *)malloc(3);
		  strcpy(yyval.chkptr->string,"1");
		  yyval.chkptr->type=basic_types+3;
		  yyval.chkptr->nxt=NULL;		
		}
break;
case 230:
#line 2010 "pas.y"
{ yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
		  yyval.chkptr->string=(char *)malloc(3);
		  strcpy(yyval.chkptr->string,"0");
		  yyval.chkptr->type=basic_types+3;
		  yyval.chkptr->nxt=NULL;		
		}
break;
case 231:
#line 2017 "pas.y"
{  printf("nil");
		yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
		  yyval.chkptr->nxt=NULL;
		  yyval.chkptr->type=(Typeptr)malloc(sizeof(Type));
		  yyval.chkptr->type->type_type=POINTER_TYPE;
		  yyval.chkptr->string=(char *)malloc(6);
		  strcpy(yyval.chkptr->string,"NULL");
		 yyval.chkptr->type->typeptr=NULL;
		}
break;
case 232:
#line 2030 "pas.y"
{ printf("\n unsinged no ");
		yyval.constptr=yyvsp[0].constptr;
		}
break;
case 233:
#line 2034 "pas.y"
{ yyval.constptr=SymtabCreateNewConst(CONST_CHAR,yyvsp[0].stackptr->lexeme);
		free(yyvsp[0].stackptr);
		}
break;
case 234:
#line 2041 "pas.y"
{ printf("\n unsigned int ");
		   yyval.constptr=SymtabCreateNewConst(CONST_INT,yyvsp[0].stackptr->lexeme);	
		  free(yyvsp[0].stackptr);
		}
break;
case 235:
#line 2046 "pas.y"
{ printf("\n unsinged real ");
		  yyval.constptr=SymtabCreateNewConst(CONST_REAL,yyvsp[0].stackptr->lexeme);
		  free(yyvsp[0].stackptr);
		}
break;
case 236:
#line 2053 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 237:
#line 2057 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 238:
#line 2063 "pas.y"
{ /*printf("\n id");*/
	   int currlevel,proclevel,i,no_of_arg,is_func=0; Typeptr tptr;
	   Argptr aptr; char buf[1224];
	   Typecheckptr temp; int count=0; strcpy(buf,"");
	   if(!TpCheckIsStdFunc(yyvsp[-1].stackptr->lexeme))
	   {
	      if(aptr=TpCheckIsProcInScope(yyvsp[-1].stackptr->lexeme,&currlevel,
			&proclevel,&no_of_arg,&is_func,&tptr))
	        if(is_func)
	        {   strcat(buf,yyvsp[-1].stackptr->lexeme);strcat(buf,"(");
		    temp=yyvsp[0].chkptr;
		    while(temp) { ++count; temp=temp->nxt;}
		    if(count!=no_of_arg)
			tperror(PROC_WRONG_NO_OF_ARG);
		    temp=yyvsp[0].chkptr;
		    while(temp)
		    { if(mystrcmp(aptr->type->typename,temp->type->typename)==0)
		      {	
			  if(aptr->arg_type==VAR_PARAM && 
				aptr->type->type_type!=ARRAY_TYPE)
			    strcat(buf,"&");
			  strcat(buf,temp->string);	 
			  if(temp->nxt) strcat(buf,",");
		       }
		       else tperror(PROC_WRONG_TYPE_ARG);		
		       aptr=aptr->nxt; temp=temp->nxt;
		    }
		    if(currlevel)
	 	    {
			if(currlevel==proclevel-1)  /* child called*/
			{	if(no_of_arg) strcat(buf,",");  
				strcat(buf,"&W");strcat(buf,")");
			 }
			else{ 
			 if(proclevel>1){
			   i=currlevel-proclevel+1;
			   if(no_of_arg)	strcat(buf,",");
			   while(--i)
				strcat(buf,"SCP->");
			   strcat(buf,"SCP)");	
			  } else strcat(buf,")");	
			}
		    }
	            else { 
			strcat(buf,")");
		    }
		    yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
		    yyval.chkptr->nxt=NULL;
		    yyval.chkptr->type=tptr;
		    yyval.chkptr->string=(char *)malloc(strlen(buf)+1);
	 	    strcpy(yyval.chkptr->string,buf);
	        } 
	        else tperror(ID_NOT_FUNC,yyvsp[-1].stackptr->lexeme);
	   else tperror(FUNC_NOT_IN_SCOPE,yyvsp[-1].stackptr->lexeme);	
	 } 
	 else 
		yyval.chkptr=PrintStdFuncCall(yyvsp[-1].stackptr->lexeme,yyvsp[0].chkptr,YES);
        }
break;
case 239:
#line 2122 "pas.y"
{ int currlevel,proclevel,i,no_of_arg,is_func=0; Typeptr tptr;
	   Argptr aptr; char buf[1224];
	   Typecheckptr temp; int count=0; strcpy(buf,"");
	   if(!TpCheckIsStdFunc(yyvsp[-2].stackptr->lexeme))
	   {
	      if(aptr=TpCheckIsProcInScope(yyvsp[-2].stackptr->lexeme,&currlevel,
			&proclevel,&no_of_arg,&is_func,&tptr))
		{ yyval.chkptr=(Typecheckptr)malloc(sizeof(Typecheck));
		  yyval.chkptr->nxt=NULL; yyval.chkptr->type=tptr;
		  yyval.chkptr->string=(char *)malloc(strlen(yyvsp[-2].stackptr->lexeme)+5);
		  strcpy(yyval.chkptr->string,yyvsp[-2].stackptr->lexeme);strcat(yyval.chkptr->string,"()");
		}
	      else tperror(FUNC_NOT_IN_SCOPE,yyvsp[-2].stackptr->lexeme);	
	  } else 
		yyval.chkptr=PrintStdFuncCall(yyvsp[-2].stackptr->lexeme,NULL,YES);	
	}
break;
case 240:
#line 2142 "pas.y"
{ printf("\n [ member_designator_list ] ");
		}
break;
case 241:
#line 2145 "pas.y"
{ printf("\n [ ] ");
		}
break;
case 242:
#line 2151 "pas.y"
{ printf("\n member_designator_list , member_designator ");
		}
break;
case 243:
#line 2154 "pas.y"
{ printf("\n member_designator ");
		}
break;
case 244:
#line 2160 "pas.y"
{ printf("\n member_desigantor .. expr ");
		}
break;
case 245:
#line 2163 "pas.y"
{ printf("\n expr ");
		  printf("\n --------------expr ----------");
		}
break;
case 246:
#line 2168 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 247:
#line 2169 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 248:
#line 2170 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 249:
#line 2173 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 250:
#line 2174 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 251:
#line 2175 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 252:
#line 2176 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 253:
#line 2177 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 254:
#line 2180 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 255:
#line 2181 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 256:
#line 2182 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 257:
#line 2183 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 258:
#line 2184 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 259:
#line 2185 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 260:
#line 2186 "pas.y"
{yyval.stackptr=yyvsp[0].stackptr;}
break;
case 261:
#line 2191 "pas.y"
{ yyval.stackptr=yyvsp[0].stackptr; 
		/*printf("\n id= %s",$1->lexeme); getchar();*/
		}
break;
case 262:
#line 2198 "pas.y"
{ yyval.stackptr=yyvsp[0].stackptr;
		}
break;
case 263:
#line 2203 "pas.y"
{ yyval.stackptr=yyvsp[0].stackptr; 
		}
break;
#line 3309 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
