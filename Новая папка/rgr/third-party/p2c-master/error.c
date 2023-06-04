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


#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "data_struct.h"
#include "prototype.h"
extern int line_no;

int
error (int errorno, ...)
{
  va_list ap;
  char *tmp;
  va_start (ap, errorno);
  fprintf (stderr, "\n p2c: line %d : ", line_no);
  switch (errorno)
    {
    case INVALID_TYPEDEF:
      fprintf (stderr, "Invalid type definition");
      break;
    case NON_ORDINAL_TYPE:
      fprintf (stderr, "Type should be ordinal type");
      break;
    case DUPLICATE_DECLARATION:
      fprintf (stderr, "Duplicate declaration error ");
      exit(0);
      break;
    case INVALID_STRING_OPR:
      fprintf (stderr, "Operation not defined for string");
      break;
    case INVALID_SUBRANGE_TYPE:
      fprintf (stderr, "Real type not allowed for subrange");
      break;
    case UNDEFINED_FWD_REF:	// from verify fwd referece  
      tmp = va_arg (ap, char *);
      fprintf (stderr, "Forward reference %s not resolved ", tmp);
      break;
    case CONST_NOT_FOUND:
      tmp = va_arg (ap, char *);
      fprintf (stderr, "\nConstant %s not found ", tmp);
    case WRONG_FUNC_RET_TYPE:
      fprintf(stderr,"\n Wrong return type for function .. exiting");
      exit(0);
      break;
    default:
      fprintf (stderr, " : unknown error ");
      break;

    }
  va_end (ap);
}
int tperror(int errno,...)
{ va_list ap;
  char *chptr,*chptr2;	
  va_start(ap,errno);
  fprintf(stderr,"\np2c:line %d:Typecheck Error: ",line_no);
  switch(errno)
  { case DECL_NOT_FOUND:
	  chptr=va_arg(ap,char *);
	  fprintf(stderr," %s not found in any scope ",chptr);
	  exit(0);
	  break;
    case NOT_INVALID_OPERAND:
	 fprintf(stderr,"  The argument to NOT should be integer type");
          exit(0);	 
	  break;
   case MUL_OP_INVALID_OPERANDS:	  
	 fprintf(stderr,"  Operands to MUL_OP should be int or real");
         exit(0);	 
	 break;
   case ADD_OP_INVALID_OPERANDS:	  
	 fprintf(stderr,"  Operands to ADD_OP should be int or real");
         exit(0);	 
	 break;
    case PWR_INVALID_OPERANDS:
	 fprintf(stderr,"  Operands to power should be int or real");
         exit(0);	 
	 break;
     case DIV_INVALID_OPERANDS:
	 fprintf(stderr,"  Operands to DIV should be int");
         exit(0);	
	 break; 
     case MOD_INVALID_OPERANDS:
	 fprintf(stderr,"  Operands to MOD should be int");
         exit(0);	
	 break; 
     case AND_INVALID_OPERANDS:
	 fprintf(stderr,"  Operands to AND  should be boolean");
         exit(0);	
	 break; 
     case OR_INVALID_OPERANDS:
	 fprintf(stderr,"  Operands to OR  should be boolean");
         exit(0);	
	 break; 
     case COMPARISON_INVALID_OPERANDS:
	 fprintf(stderr,"  Operands to COMPARISON OP  should be int");
         exit(0);	
	 break; 
     case BOOLEAN_EXPR_WRONG_TYPE:
	 fprintf(stderr," BOOLEAN expression expected");
         exit(0);	
	 break; 
     case FOR_LOOP_VAR_INVALID_VALUE:
	 fprintf(stderr," For loop variable expects integer value");
         exit(0);	
	 break; 
     case FOR_LOOP_WRONG_CTRL_VAR_TYPE:
	 fprintf(stderr," For loop variable should be integer type");
         exit(0);	
	 break; 
     case ASSIGNMENT_STAT_TYPE_MISMATCH:
	 fprintf(stderr," Right And Left Side types should match");
         exit(0);	
	 break; 
     case ASSIGNMENT_STAT_WRONG_TYPE:
	 fprintf(stderr," Assignment for this type not supported");
         exit(0);	
	 break; 
     case OUT_OF_SCOPE_REF:
	 fprintf(stderr," Reference out of scope");
         exit(0);	
	 break; 
     case PROCEDURE_RET_TYPE_REF:
	 fprintf(stderr," Referencing procedure return type");
         exit(0);	
	 break; 
     case TYPE_IS_NOT_ARRAY:
	  chptr=va_arg(ap,char *);
	  fprintf(stderr," Type %s is not array ",chptr);
         exit(0);	
	 break; 
     case ARRAY_WRONG_NO_OF_INDEX:
	 fprintf(stderr," wrong no. of indices for array");
         exit(0);	
	 break; 
     case ARRAY_SUBSCR_NOT_INTEGER:
	 fprintf(stderr," Array subscript should be integer type");
         exit(0);	
	 break; 
     case TYPE_IS_NOT_POINTER:
	  chptr=va_arg(ap,char *);
	 fprintf(stderr," Dereferening non pointer type %s",chptr);
         exit(0);	
	 break; 
     case TYPE_IS_NOT_RECORD:
	  chptr=va_arg(ap,char *);
	 fprintf(stderr," Type %s is not record ",chptr);
         exit(0);	
	 break; 
     case RECORD_FIELD_NOT_EXIST:
	  chptr=va_arg(ap,char *);
	  chptr2=va_arg(ap,char *);
	 fprintf(stderr," Record %s doesnt have field %s",chptr,chptr2);
         exit(0);	
	 break; 
     case FUNC_NOT_IN_SCOPE:
	  chptr=va_arg(ap,char *);
	 fprintf(stderr," Function/Proc %s is not in current scope ",chptr);
         exit(0);	
	 break; 
     case PROC_WRONG_NO_OF_ARG:
	 fprintf(stderr," Incorrect No of Arguments to func/proc");
         exit(0);	
	 break; 
     case PROC_WRONG_TYPE_ARG:
	 fprintf(stderr," Incorrect Type variable being passed");
         exit(0);	
	 break; 
     case ID_NOT_FUNC:
	  chptr=va_arg(ap,char *);
	 fprintf(stderr,"  %s is not a function ",chptr);
         exit(0);	
	 break; 
    default:
	  fprintf(stderr,"This Error Type is not defined ");
	  break;
  }
}
