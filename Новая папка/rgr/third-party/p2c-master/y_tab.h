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
extern YYSTYPE yylval;
