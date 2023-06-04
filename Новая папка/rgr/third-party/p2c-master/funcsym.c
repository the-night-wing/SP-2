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

Funptr symtab;
Funptr currfun;
Typeptr currtype, FwdRefList = NULL;
Varptr currvar;
Constptr currconst;
Argptr currarg;
Idptr currid, curridlist;	//curridlist is current list of identifiers 
			 // currid points to the last node in the current list

extern Type basic_types[4];

extern Funptr tempfun;
extern Typeptr temptype;
extern Varptr tempvar;
extern Argptr temparg;
extern Idptr tempid;

extern int func_level;
extern int prev_func_level;

/*****************************************************************************/
char *std_func_list[]={"append",	"assign",	"close",
			"dispose",	"new",		"pack",
			"read",		"readln",	"reset",
			"rewrite",	"unpack",	"write",
			"writeln",	"abs",		"arctan",
			"chr",		"cos",		"eof",
			"eoln",		"exp",		"ln",
			"odd",		"ord",		"pred",
			"round",	"sin",		"sqr",
			"sqrt",		"succ",		"trunc"};
			


/*****************************************************************************/

/* Initiates the symbol table.. outtermost block i.e. main is cretaed
 * and its return type set to integer; psedo function. only placeholder as root
 */
int
SymtabInit ()
{
  symtab = (Funptr) malloc (sizeof (Function));
  symtab->fname = (char *) malloc (7);
  strcpy (symtab->fname, "main");

  symtab->level = 0;
  symtab->ret_type = basic_types;

  symtab->no_of_types = symtab->no_of_arg = symtab->no_of_vars = 0;
  symtab->no_of_consts = symtab->no_of_children = 0;

  symtab->typelist = NULL;
  symtab->varlist = NULL;
  symtab->constlist = NULL;
  symtab->arglist = NULL;
  symtab->parent = NULL;
  symtab->children = NULL;

  currfun = symtab;

  currconst = symtab->constlist;
  currvar = symtab->varlist;
  currtype = symtab->typelist;
  currarg = symtab->arglist;
}

/*****************************************************************************/

int
SymtabInsertFunction (char *name)
{
  SymtabInsertProcedure (name);
  // note : add code to modify return type
}

/*--------------------------------------------------------------------*/

/*Inserting a functio of procedure in the current tree of functions and proc . 
 * creates a new function with given name as arg. with all pointers =NULL
 * that is inserted as child of current function. 
 *  The no. of childs of the current function are manipulated accordingly
 */
int
SymtabInsertProcedure (char *name)
{
  Funptr temp;
  //  printf("\n in SIProc"); getchar();
  temp = (Funptr) malloc (sizeof (Function));
  temp->fname = (char *) malloc (strlen (name) + 1);
  strcpy (temp->fname, name);
  temp->no_of_arg = temp->no_of_vars = temp->no_of_types = 0;
  temp->no_of_consts = 0;
  temp->level = func_level;
  temp->arglist = NULL;
  temp->varlist = NULL;
  temp->constlist = NULL;
  temp->typelist = NULL;
  temp->children = NULL;
  temp->ret_type = NULL;	//indicates procedure

  //  printf("\n in SIProc"); getchar();
  temp->parent = currfun;
  currfun->no_of_children = currfun->no_of_children + 1;
  if (currfun->no_of_children == 1)
    currfun->children = (Funptr *) malloc (sizeof (Funptr));
  else
    currfun->children =
      (Funptr *) realloc (currfun->children, currfun->no_of_children);
  currfun->children[currfun->no_of_children - 1] = temp;
  currfun = temp;
}

/*--------------------------------------------------------------------*/
/* Called when the definition of a procedure or function is totally parsed
 * Hence the parent s becomes the current function after this function
 *  is called
 */
int
SymtabDecrCurrFuncPtr ()
{
  currfun = currfun->parent;
}

/*--------------------------------------------------------------------*/

static int level = 0;

/*  Printing of the current tree of functions  .. NICELY WRITTEN!!  */
int
SymtabTraverseFuncTree (Funptr temp)
{
  int i, j;
  level++;
  printf ("\n");
  for (j = 0; j < level; j++)
    printf ("\t");
  printf ("%s", temp->fname);
  for (i = 0; i < temp->no_of_children; i++)
    SymtabTraverseFuncTree (temp->children[i]);

  level--;
}

// note: this function might set the ret_type to null also
SymtabAddFuncRetType (Typeptr ptr)
{ if(ptr==NULL) 
	{printf("\n\nSetting function %s rettype to NULL",currfun->fname);
	getchar();}
  if(  ptr->type_type==INTEGER_TYPE
    || ptr->type_type==CHAR_TYPE
    || ptr->type_type==REAL_TYPE
    || ptr->type_type==BOOLEAN_TYPE
    || ptr->type_type==ENUM_TYPE
    || ptr->type_type==SUBRANGE_TYPE)
  currfun->ret_type = ptr;
  else 
	  error(WRONG_FUNC_RET_TYPE);
}
int SymtabIsNameDefined(char *name)
{ Constptr cptr;
  Varptr vptr;
  Typeptr tptr;

  cptr= currfun->constlist;
  while(cptr)
  { if(mystrcmp(cptr->name,name)==0)
	 return 1;
    else cptr=cptr->nxt;
  }
  vptr= currfun->varlist;
  while(vptr)
  { if(mystrcmp(vptr->name,name)==0)
	 return 1;
    else vptr=vptr->nxt;
  }
  tptr= currfun->typelist;
  while(tptr)
  { if(mystrcmp(tptr->typename,name)==0)
	 return 1;
    else tptr=tptr->nxt;
  }
  if(mystrcmp(currfun->fname,name)==0)
	  return 1;
  return 0;
}
