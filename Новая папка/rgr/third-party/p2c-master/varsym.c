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

extern int func_level;
extern int prev_func_level;



/* Create a new node of type Idnode of given name and return a pointer to it*/
Idptr
SymtabCreateNewId (char *name)
{
  Idptr temp;
  temp = (Idptr) malloc (sizeof (Idnode));
  temp->idname = (char *) malloc (strlen (name) + 1);
  strcpy (temp->idname, name);
  temp->nxt = NULL;
  return temp;
}

/*--------------------------------------------------------------------*/
/* Append the Idnode pointed by ptr2 to the idlist pointed to by ptr1*/
Idptr
SymtabAppendToIdlist (Idptr ptr1, Idptr ptr2)
{
  Idptr temp;
  if (ptr1 == NULL)
    ptr1 = ptr2;
  else
    {
      temp = ptr1;
      while (temp->nxt != NULL)
	temp = temp->nxt;
      temp->nxt = ptr2;
    }
  return ptr1;
}

/*--------------------------------------------------------------------*/
/* Print the list of ids from the ptr given as argument*/
SymtabPrintIdlist (Idptr ptr)
{
  int i = 0;
  while (ptr != NULL)
    {
      ++i;
      printf (" %d) %s", i, ptr->idname);
      ptr = ptr->nxt;
      //    printf("hi"); getchar(); getchar();
    }
}

/*---------------------------------------------------------------*/
Varptr
SymtabCreateNewVar (char *name, Typeptr type)
{
  Varptr temp;
  temp = (Varptr) malloc (sizeof (Var));
  temp->name = (char *) malloc (strlen (name) + 1);
  strcpy (temp->name, name);
  temp->type = type;
  temp->nxt = NULL;
  return temp;
}

/*---------------------------------------------------------------*/
Varptr
SymtabAppendToVarlist (Varptr ptr1, Varptr ptr2)
{
  Varptr temp;
  if (ptr1 == NULL)
    ptr1 = ptr2;
  else
    {
      temp = ptr1;
      while (temp->nxt != NULL)
	temp = temp->nxt;
      temp->nxt = ptr2;
    }
  return ptr1;
}

/*---------------------------------------------------------------*/
SymtabPrintVarlist (Varptr ptr)
{
  Varptr temp;
  int i = 0;
  printf ("\n Printing varlist");
  temp = ptr;
  while (temp)
    {
      ++i;
      printf ("\n %d) %s type=%s", i, temp->name, temp->type->typename);
      temp = temp->nxt;
    }
}

/*---------------------------------------------------------------*/
int
SymtabAddVarDecllist (Varptr temp)
{ Varptr ptr;
  currfun->varlist = temp;
  ptr=temp;
  while(ptr)
  {   ptr->func=currfun;
	 ptr=ptr->nxt;
  }
}

/*---------------------------------------------------------------*/
Argptr
SymtabCreateNewArg (char *name, int argtype, Typeptr type)
{
  Argptr temp;
  temp = (Argptr) malloc (sizeof (Arg));
  temp->name = (char *) malloc (strlen (name) + 1);
  strcpy (temp->name, name);
  temp->type = type;
  temp->arg_type = argtype;
  temp->nxt = NULL;
  return temp;
}

/*---------------------------------------------------------------*/
Argptr
SymtabAppendToArglist (Argptr ptr1, Argptr ptr2)
{
  Argptr temp;
  if (ptr1 == NULL)
    ptr1 = ptr2;
  else
    {
      temp = ptr1;
      while (temp->nxt != NULL)
	temp = temp->nxt;
      temp->nxt = ptr2;
    }
  return ptr1;
}

int
SymtabAddArgDecllist (Argptr temp)
{ Argptr ptr; int count=0;
  currfun->arglist = temp;
  ptr=temp;
  while(ptr)
  {    ptr->func=currfun;
	 ptr=ptr->nxt; ++ count;
  }
  currfun->no_of_arg=count;
}

int
SymtabPrintArglist ()
{
  Argptr temp;
  int i = 1;
  temp = currfun->arglist;
  printf ("\n Printing Argument list");
  while (temp != NULL)
    {
      printf ("\n %d ) name= %s  vartype= %s",
	      i, temp->name, temp->type->typename);
      printf (" arg_type = ");
      switch (temp->arg_type)
	{
	case VALUE_PARAM:
	  printf (" value param ");
	  break;
	case VAR_PARAM:
	  printf ("var param ");
	  break;
	case PROC_PARAM:
	  printf ("procdure param ");
	  break;
	case FUNC_PARAM:
	  printf ("function param ");
	  break;
	}

      ++i;
      temp = temp->nxt;
    }
}
