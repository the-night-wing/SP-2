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

extern Funptr symtab;
extern Funptr currfun;
extern Typeptr currtype;
extern Varptr currvar;
extern Constptr currconst;
extern Argptr currarg;
extern Idptr currid, curridlist;	//curridlist is current list of identifiers 
			 // currid points to the last node in the current list

extern Type basic_types[4];

extern Funptr tempfun;
extern Typeptr temptype;
extern Varptr tempvar;
extern Argptr temparg;
extern Idptr tempid;

extern int func_level;
extern int prev_func_level;

/*  Creates a Constant record. 
 *  This record is added to the current list of constants for the current
 *  function . 
 */

int
SymtabInsertConst (char *lexeme, Constptr ptr)
{
  Constptr temp;

  ++(currfun->no_of_consts);

  temp = (Constptr) malloc (sizeof (Constant));
  temp->name = (char *) malloc (strlen (lexeme) + 1);
  strcpy (temp->name, lexeme);
  temp->value = ptr->value;
  temp->nxt = NULL;
  temp->const_type = ptr->const_type;
  temp->func=currfun;
  if (currfun->constlist == NULL)
    {
      currfun->constlist = temp;
      currconst = temp;
    }
  else
    {
      currconst->nxt = temp;
      currconst = temp;
    }

}

/*--------------------------------------------------------------------*/
/* print the list of constants defined for the current function
 */
int
SymtabPrintConstlist ()
{
  Constptr temp;
  int i = 0;
  printf ("\n No. of constants = %d", currfun->no_of_consts);
  temp = currfun->constlist;
  while (temp != NULL)
    {
      i++;
      printf ("\n %d) id= %s value= %f ", i, temp->name, temp->value);
      temp = temp->nxt;
    }

}

Constptr
SymtabIsConstPresent (char *name)
{
  Constptr tempconst;
  Funptr tempfun;
  tempfun = currfun;
  while (tempfun != NULL)
    {
      tempconst = tempfun->constlist;
      while (tempconst != NULL)
	{
	  if (mystrcmp (tempconst->name, name) == 0)
	    {
	      return tempconst;
	    }
	  else
	    tempconst = tempconst->nxt;
	}
      tempfun = tempfun->parent;
    }
  printf ("\n IsConstPresent : %s not found", name);
  return NULL;
}

Constptr
SymtabCreateNewConst (int type, ...)
{
  va_list ap;
  Constptr temp;
  temp = (Constptr) malloc (sizeof (Constant));
  temp->name = NULL;
  temp->nxt = NULL;
  temp->const_type = type;

  va_start (ap, type);
  switch (type)
    {
    case CONST_CHAR:
      {
	char *tmp;
	tmp = va_arg (ap, char *);
	temp->string = (char *) malloc (strlen (tmp) + 1);
	strcpy (temp->string, tmp + 1);	// +1 for eliminating the '
	temp->string[strlen (temp->string) - 1] = '\0';
	printf ("\n CreateNewConst : string= %s ", tmp);
      }
      break;
    case CONST_INT:
      {
	char *tmp;
	tmp = va_arg (ap, char *);
	temp->value = (float) atoi (tmp);
	printf ("\n CreateNewConst: string= %s value= %d ", tmp,
		(int) temp->value);
      }
      break;
    case CONST_REAL:
      {
	char *tmp;
	tmp = va_arg (ap, char *);
	temp->value = (double)atof (tmp);
	printf ("\n CreateNewConst: string= %s value= %g ", tmp, temp->value);
      }
      break;
    case CONST_ID:
      {
	Constptr tmp;
	char *tmpch;
	tmpch = va_arg (ap, char *);
	tmp = SymtabIsConstPresent (tmpch);
	if (tmp != NULL)
	  {
	    temp->value = tmp->value;
	    temp->const_type = tmp->const_type;
	    temp->nxt = NULL;
	  }
	else
	  {
	    free (temp);
	    return NULL;
	  }
      }
      break;
    default:
      break;
    }
  va_end (ap);
  return temp;
}
