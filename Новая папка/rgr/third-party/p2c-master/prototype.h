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


#ifndef _PROTOTYPES_
#define _PROTOTYPES_
#include "data_struct.h"
#define YES 1
#define NO 0
#define getchar() ;
//from pas.y
YaccRetptr StringCat (int, ...);
int yyerror (char *);
Constptr MakeConstList(Constptr,Constptr);
// from pas.l
int commenterror ();
int yywrap ();
int MakeRetRec ();

// from main.c
int GetcFilename (char *, char *);
int main (int argc, char *argv[]);

// from funcsym.c
int SymtabInit ();
int SymtabInsertFunction ();
int SymtabInsertProcedure (char *name);
int SymtabDecrCurrFuncPtr ();
int SymtabTraverseFuncTree (Funptr);

//from typesym.c
Typeptr SymtabCreateNewType (int type_type, ...);
int SymtabInsertType ();
Typeptr SymtabIsTypePresent (char *typename);
int SymtabIsOrdinalType (int);
int SymtabPrintTypeList ();
int SymtabPrintType(Typeptr);	
int SymtabInsertFwdTypeRef(char *name);
int SymtabVerifyFwdRef();	
int SymtabAddTypeAtBegin(Typeptr);
//from varsym.c 
Idptr SymtabCreateNewId (char *name);
Idptr SymtabAppendToIdlist (Idptr, Idptr);
int SymtabPrintIdlist (Idptr ptr);
Varptr SymtabCreateNewVar(char *name,Typeptr type);
Varptr SymtabAppendToVarlist(Varptr ptr1,Varptr ptr2);
int SymtabPrintVarlist(Varptr );	
int SymtabAddVarDecllist(Varptr temp);
Argptr SymtabCreateNewArg(char *name,int argtype,Typeptr type);
Argptr SymtabAppendToArglist(Argptr ptr1,Argptr ptr2);
int SymtabAddArgDecllist(Argptr temp);
	

//from constsym.c
int SymtabInsertConst (char *, Constptr);
int SymtabPrintConstlist ();
Constptr SymtabIsConstPresent (char *name);
Constptr SymtabCreateNewConst(int type,...);
	
//from declprint.c
int PrintHeader ();
int PrintTypelist ();
int PrintAllDeclarations ();
int PrintVarlist ();
int PrintConstlist ();
int PrintConstUndef();
int PrintTypeDef(Typeptr);
int IsRecursionReqd(Typeptr ptr);
int PrintAuxTypes(Typeptr ptr,char *);
int PrintIndent();	
int PrintFuncHeader();
// from statprint.c

//for error handling #defines
//from error.c
#define INVALID_TYPEDEF 1
#define NON_ORDINAL_TYPE 2
#define DUPLICATE_DECLARATION 3
#define INVALID_STRING_OPR 4
#define INVALID_SUBRANGE_TYPE 5
#define UNDEFINED_FWD_REF 6
#define CONST_NOT_FOUND 7
#define WRONG_FUNC_RET_TYPE 8

int error(int,...);
#define DECL_NOT_FOUND 9
#define NOT_INVALID_OPERAND 10
#define PWR_INVALID_OPERANDS 11
#define MUL_OP_INVALID_OPERANDS 12
#define DIV_INVALID_OPERANDS 13
#define MOD_INVALID_OPERANDS 14
#define AND_INVALID_OPERANDS 15
#define COMPARISON_INVALID_OPERANDS 16
#define BOOLEAN_EXPR_WRONG_TYPE 17
#define ADD_OP_INVALID_OPERANDS 18
#define OR_INVALID_OPERANDS 19
#define FOR_LOOP_VAR_INVALID_VALUE 20
#define FOR_LOOP_WRONG_CTRL_VAR_TYPE 21
#define ASSIGNMENT_STAT_TYPE_MISMATCH 22
#define ASSIGNMENT_STAT_WRONG_TYPE 23
#define OUT_OF_SCOPE_REF 24
#define PROCEDURE_RET_TYPE_REF 25
#define TYPE_IS_NOT_ARRAY 26
#define ARRAY_WRONG_NO_OF_INDEX 27
#define ARRAY_SUBSCR_NOT_INTEGER 28
#define TYPE_IS_NOT_POINTER 29
#define TYPE_IS_NOT_RECORD 30
#define RECORD_FIELD_NOT_EXIST 31
#define FUNC_NOT_IN_SCOPE 32
#define PROC_WRONG_NO_OF_ARG 33
#define PROC_WRONG_TYPE_ARG 34
#define ID_NOT_FUNC 35
int tperror(int,...);
// from misc.c
int GetSetRange(char *,long);
int mystrcmp(char *,char *);
long GetRange(long,long);

// from tpcheck.c
Typeptr TpCheckGetTypePtr(char*,int*,int*,int*,char*);
int TpCheckGetArrayLimitDiff(Typeptr,int,char *buf);
Typeptr TpCheckIsRecField(Typeptr type,char *name);
Argptr TpCheckIsFuncInScope(char*,int*,int*,int*,int *,Typeptr *);	
int TpCheckIsStdFunc(char *);
Typecheckptr PrintStdFuncCall(char *fname,Typecheckptr ptr,int);
	
#endif
