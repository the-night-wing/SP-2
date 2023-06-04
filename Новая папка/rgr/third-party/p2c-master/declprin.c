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



#include <stdio.h>
#include "data_struct.h"
#include "prototype.h"

extern FILE *cfile;
extern char pasfilename[];
extern Funptr symtab;
extern Funptr currfun;
extern Typeptr currtype;
extern Varptr currvar;
extern Constptr currconst;
extern Varptr currarg;
//#define getchar() ;
int indent = 0;
/*-------------------------------------------------------------------------*/
int
PrintHeader ()
{
  fprintf (cfile, "/*Output of p2c-1.1 by Rahil Mirza & Abhijit Kadlag */");
  fprintf (cfile, "\n/* From input file %s*/", pasfilename);
  fprintf (cfile, "\n\n#include \"/home/abhijit/p2c/p2c.h\"\n");
}

/*-------------------------------------------------------------------------*/
int
PrintAllDeclarations ()
{
  PrintConstlist ();
  PrintTypelist ();
  PrintVarlist ();
  printf ("\n After PrintAllDeclarations ");
  SymtabPrintTypeList ();
  printf ("\n After Printtypelist in Printalldecl");
}

/*-------------------------------------------------------------------------*/
int
PrintConstlist ()
{
  Constptr temp;
  temp = currfun->constlist;
  printf ("\n Printing Constlist ");
  getchar ();
  while (temp != NULL)
    {
      char tmp[128];
      if (temp->const_type == CONST_REAL)
	{
	  sprintf (tmp, "%f", temp->value);
	  fprintf (cfile, "\n#define %s (%s)", temp->name, tmp);
	}
      else if (temp->const_type == CONST_INT)
	{
	  int i;
	  i = (int) (temp->value);
	  sprintf (tmp, "%d", i);
	  fprintf (cfile, "\n#define %s (%s)", temp->name, tmp);
	}
      else if (temp->const_type == CONST_CHAR)
	fprintf (cfile, "\n#define %s \"%s\"", temp->name, temp->string);
      temp = temp->nxt;
    }
  printf ("..done");
  getchar ();
}

/*-------------------------------------------------------------------------*/
int
PrintTypelist ()
{
  Typeptr temp;
  temp = currfun->typelist;
  fprintf (cfile, "\n");
  printf ("\n Printing Typelist");
  getchar ();
  while (temp != NULL)
    {
      PrintTypeDef (temp);
      fprintf (cfile, "\n");
      temp = temp->nxt;
    }
  printf ("Typelist printing ..done");
  getchar ();
}

/*-------------------------------------------------------------------------*/
static int level = 1;
int
PrintVarlist ()
{
  Varptr varptr; Typeptr tmptype;
  varptr = currfun->varlist;
  if (currfun->level == 0)	// for main block all globals in C
    {
      while (varptr)
	{
	  tmptype = varptr->type;
	  if (tmptype->typename != NULL)
	    {
	      fprintf (cfile, "\nstatic\t%s\t", tmptype->typename);
	      fprintf (cfile, "%s;", varptr->name);

	      fprintf (stdout, "\n\t%s\t", tmptype->typename);
	      fprintf (stdout, "%s;", varptr->name);
	      getchar ();
	    }
	  else
	    PrintType (varptr);

	  varptr = varptr->nxt;
	}

    }
  else		// for nested function declare within LOCAL_struct
    {  fprintf(cfile,"\n/*Local variables for function %s */",currfun->fname);
      fprintf (cfile, "\ntypedef\tstruct\tLOCAL_%s{", currfun->fname);
      fprintf (stdout, "\ntypedef\tstruct\tLOCAL_%s{", currfun->fname);
      while (varptr)
	{
	  tmptype = varptr->type;
	  if (tmptype->typename != NULL)
	    {
	      fprintf (cfile, "\n\t%s\t", tmptype->typename);
	      fprintf (cfile, "%s;", varptr->name);

	      fprintf (stdout, "\n\t%s\t", tmptype->typename);
	      fprintf (stdout, "%s;", varptr->name);
	      getchar ();
	    }
	  else
	    PrintType (varptr);

	  varptr = varptr->nxt;
	}
      if(currfun->level>1)
      fprintf(cfile,"\n\tLOCAL_%s *SCP;",currfun->parent->fname);
      fprintf (cfile, "\n}LOCAL_%s;\n", currfun->fname);
      fprintf (stdout, "\n}LOCAL_%s;", currfun->fname);
    }
}

/*-------------------------------------------------------------------------*/
int
PrintConstUndef ()
{
  Constptr temp;
  temp = currfun->constlist;
  printf ("\n Printing Constant undef ");
  getchar ();
  while (temp != NULL)
    {
      char tmp[128];
      if (temp->const_type == CONST_REAL)
	{
	  sprintf (tmp, "%f", temp->value);
	  fprintf (cfile, "\n#undef %s ", temp->name);
	}
      else if (temp->const_type == CONST_INT)
	{
	  int i;
	  i = (int) (temp->value);
	  sprintf (tmp, "%d", i);
	  fprintf (cfile, "\n#undef %s ", temp->name);
	}
      else if (temp->const_type == CONST_CHAR)
	fprintf (cfile, "\n#undef %s ", temp->name);
      temp = temp->nxt;
    }
  printf ("...done");
  getchar ();
}

/*-------------------------------------------------------------------------*/
PrintTypeDef (Typeptr ptr)
{
  Varptr varptr;
  Typeptr tmptype;
  Idptr tmpid;
  int count;
  printf ("\n In Printtypedef , ptr= %s", ptr->typename);
  getchar ();
  switch (ptr->type_type)
    {
    case INTEGER_TYPE:
      fprintf (cfile, "\ntypedef\tlong\t%s;", ptr->typename);
      fprintf (stdout, "\ntypedef\tlong\t%s;", ptr->typename);
      break;
    case CHAR_TYPE:
      fprintf (cfile, "\ntypedef\tchar\t%s;", ptr->typename);
      fprintf (stdout, "\ntypedef\tchar\t%s;", ptr->typename);
      break;
    case BOOLEAN_TYPE:
      fprintf (cfile, "\ntypedef\tboolean\t%s;", ptr->typename);
      fprintf (stdout, "\ntypedef\tboolean\t%s;", ptr->typename);
      break;
    case REAL_TYPE:
      fprintf (cfile, "\ntypedef\tfloat\t%s;", ptr->typename);
      fprintf (stdout, "\ntypedef\tfloat\t%s;", ptr->typename);
      break;
    case SET_TYPE:
      { char buff[128];
       fprintf(cfile,"\ntypedef\t");
       GetSetRange(buff,ptr->no_of_elem);
       printf("\n no.of elm of set = %d = %s ",ptr->no_of_elem,buff);
       getchar();
       fprintf(cfile,"long\t%s[%s];",ptr->typename,buff);
      } 
      break;
    case ENUM_TYPE:
      {
	Idptr tmpid;
	int count;
	fprintf (cfile, "\ntypedef\tenum %s{\n\t", ptr->typename);
	fprintf (stdout, "\ntypedef\tenum %s{\n\t", ptr->typename);
	tmpid = ptr->idlist;
	count = ptr->no_of_member - 1;
	while (count--)
	  {
	    fprintf (cfile, "%s,", tmpid->idname);
	    fprintf (stdout, "%s,", tmpid->idname);
	    tmpid = tmpid->nxt;
	  }
	fprintf (cfile, "%s\n}%s;", tmpid->idname, ptr->typename);
	fprintf (stdout, "%s\n}%s;", tmpid->idname, ptr->typename);
      }
      break;
    case SUBRANGE_TYPE:
      fprintf (cfile, "\ntypedef\tlong\t%s;", ptr->typename);
      break;
    case ARRAY_TYPE:
      {
	int count;
	int finished = 0;
	Dimension *dmnptr;

	if (IsRecursionReqd (ptr))
	  PrintAuxTypes (ptr, ptr->typename);
	fprintf (cfile, "\ntypedef");
	fprintf (stdout, "\ntypedef");
	switch (ptr->elemtype->type_type)
	  {
	  case POINTER_TYPE:
	    fprintf (cfile, "\t%s\t*", ptr->elemtype->typeptr->typename);
	    fprintf (stdout, "\t%s\t*", ptr->elemtype->typeptr->typename);
	    break;
	  case SET_TYPE:
	    fprintf (cfile, "\t%s\t", "long");
	    fprintf (stdout, "\t%s\t", "long");
	    break;
	  case RECORD_TYPE:
	  case INTEGER_TYPE:
	  case REAL_TYPE:
	  case BOOLEAN_TYPE:
	  case CHAR_TYPE:
	  case ARRAY_TYPE:
	  case ENUM_TYPE:
	    fprintf (cfile, "\t%s\t", ptr->elemtype->typename);
	    fprintf (stdout, "\t%s\t", ptr->elemtype->typename);
	    break;
	  }

	fprintf (cfile, "%s", ptr->typename);

	while (!finished)
	  {
	    count = ptr->no_of_dimn;
	    dmnptr = ptr->dimensions;
	    while (count--)
	      {
		switch (dmnptr->type_flag)
		  {
		  case CHAR_TYPE:
		    fprintf (cfile, "[256]");
		    fprintf (stdout, "[256]");
		    break;
		  case INTEGER_TYPE:
		    fprintf (cfile, "[65535]");
		    fprintf (stdout, "[65535]");
		    break;
		  case SUBRANGE_TYPE:
		    if(dmnptr->low->const_type==CONST_CHAR)
		    { fprintf(cfile,"[%d]",
			    *(dmnptr->high->string)-*(dmnptr->low->string)+1);
		    }
		    else fprintf (cfile, "[%d]",
			     GetRange ((int) dmnptr->low->value,
				       (int) dmnptr->high->value));
		    fprintf (stdout, "[%d]",
			     GetRange ((int) dmnptr->low->value,
				       (int) dmnptr->high->value));
		    break;
		  case ENUM_TYPE:
		    fprintf (cfile, "[%d]", dmnptr->no_of_ids);
		    fprintf (stdout, "[%d]", dmnptr->no_of_ids);
		    break;
		  case BOOLEAN_TYPE:
		    fprintf (cfile, "[2]");
		    fprintf (stdout, "[2]");
		    break;
		  }
		++dmnptr;
	      }
	    if (ptr->elemtype->type_type == ARRAY_TYPE)
	      if (IsRecursionReqd (ptr->elemtype))
		ptr = ptr->elemtype;
	      else
		finished = 1;
	    else
	      finished = 1;
	  }
	fprintf (cfile, ";");
	fprintf (stdout, ";");
      }
      break;
    case RECORD_TYPE:
      if (IsRecursionReqd (ptr))
	PrintAuxTypes (ptr, ptr->typename);
      fprintf (cfile, "\ntypedef\tstruct\t%s{", ptr->typename);
      fprintf (stdout, "\ntypedef\tstruct\t%s{", ptr->typename);
      varptr = ptr->varlist;
      while (varptr)
	{
	  tmptype = varptr->type;
	  if (tmptype->typename != NULL)
	    {
	      fprintf (cfile, "\n\t%s\t", tmptype->typename);
	      fprintf (cfile, "%s;", varptr->name);

	      fprintf (stdout, "\n\t%s\t", tmptype->typename);
	      fprintf (stdout, "%s;", varptr->name);
	      getchar ();
	    }
	  else
	    PrintType (varptr);

	  varptr = varptr->nxt;
	}
      fprintf (cfile, "\n}%s;\n", ptr->typename);
      fprintf (stdout, "\n}%s;", ptr->typename);
      break;
    case POINTER_TYPE:
      fprintf (cfile, "\ntypedef\t");
      if (ptr->is_fwd_ref)
	switch (ptr->typeptr->type_type)
	  {
	  case RECORD_TYPE:
	    fprintf (cfile, "struct\t%s\t*", ptr->typeptr->typename);
	    break;
	  case INTEGER_TYPE:
	  case CHAR_TYPE:
	  case BOOLEAN_TYPE:
	  case REAL_TYPE:
	    fprintf (cfile, "%s\t*", ptr->typeptr->typename);
	    break;
	  case ARRAY_TYPE:

	    break;
	  case POINTER_TYPE:
	    fprintf (cfile, "%s\t*", ptr->typeptr->typename);
	    break;
	  case ENUM_TYPE:
	    fprintf (cfile, "%s\t*", ptr->typeptr->typename);
	    break;
	  }
      else
	fprintf (cfile, "%s\t*", ptr->typeptr->typename);
      fprintf (cfile, "%s;", ptr->typename);
      fprintf (stdout, "\ntypedef\t%s\t*", ptr->typeptr->typename);
      fprintf (stdout, "%s;", ptr->typename);
      break;
    case FILE_TYPE:
      break;
    default:
      printf ("\n PrintType: this type is not supported ");
      break;
    }
}

/*-------------------------------------------------------------------------*/
int
IsRecursionReqd (Typeptr ptr)
{
  Typeptr temp;
  Varptr tmpvar;
  int found;
  printf ("\n In IsrecursionReqd ptr= %s", ptr->typename);
  switch (ptr->type_type)
    {
    case RECORD_TYPE:
      tmpvar = ptr->varlist;
      while (tmpvar)
	{
	  printf ("\nchecking for variable %s", tmpvar->name);
	  if (tmpvar->type->typename == NULL)
	    {
	      if (tmpvar->type->type_type == RECORD_TYPE)
		{
		  printf ("..ans= yes ");
		  return YES;
		}
	      else if (tmpvar->type->type_type == ARRAY_TYPE)
		{
		  printf ("\nvar of array");
		  if (IsRecursionReqd (tmpvar->type))
		    return YES;
		}
	    }
	  tmpvar = tmpvar->nxt;
	}
      printf ("ans=no after all variables of %s ", ptr->typename);
      return NO;
      break;
    case ARRAY_TYPE:
      found = 0;
      temp = ptr->elemtype;
      if (ptr->elemtype->typename != NULL)	// not null means that the 
	//type was previously defined hence printed in C file 
	{
	  printf ("ans= no due to typename def");
	  return NO;
	}
      while (!found)
	{
	  if (temp->type_type == RECORD_TYPE)
	    {
	      printf ("ans= yes");
	      return YES;
	    }
	  else if (temp->type_type == ARRAY_TYPE)
	    {
	      printf ("array of array");
	      temp = temp->elemtype;
	    }
	  else if (temp->type_type == INTEGER_TYPE
		   || temp->type_type == CHAR_TYPE
		   || temp->type_type == REAL_TYPE
		   || temp->type_type == BOOLEAN_TYPE
		   || temp->type_type == SUBRANGE_TYPE
		   || temp->type_type == ENUM_TYPE
		   || temp->type_type == POINTER_TYPE
		   || temp->type_type == SET_TYPE
		   || temp->type_type == FILE_TYPE)
	    {
	      printf ("ans=no due to terminal type %d", temp->type_type);
	      return NO;
	    }
	  else
	    {
	      printf ("IsRecursionReqd: undefined type ... exitining");
	      exit (0);
	    }
	}
      break;
    default:
      printf ("IsRecursionReqd :default case type = %d", ptr->type_type);
      return NO;
      break;
    }
}

/*-------------------------------------------------------------------------*/
PrintAuxTypes (Typeptr ptr, char *name)
{
  Typeptr temp;
  Varptr varptr;
  printf ("\n In PrintAuxTypes.. name= %s", name);
  getchar ();
  switch (ptr->type_type)
    {
    case ARRAY_TYPE:
      printf (" type= array");
      getchar ();
      temp = ptr->elemtype;
      while (temp->type_type == ARRAY_TYPE)
	{
	  temp->typename = (char *) malloc (strlen (name) + 11);
	  strcpy (temp->typename, "RECORD_");
	  strcat (temp->typename, name);
	  while (SymtabIsTypePresent (temp->typename))
	    strcat (temp->typename, "_");
	  temp = temp->elemtype;
	}

      temp->typename = (char *) malloc (strlen (name) + 11);
      strcpy (temp->typename, "RECORD_");
      strcat (temp->typename, name);
      while (SymtabIsTypePresent (temp->typename))
	strcat (temp->typename, "_");
      if (IsRecursionReqd (temp))
	PrintAuxTypes (temp, temp->typename);
      SymtabAddTypeAtBegin (temp);
      PrintTypeDef (temp);
      break;
    case RECORD_TYPE:
      printf (" type= record ");
      getchar ();
      varptr = ptr->varlist;
      while (varptr)
	{
	  if (varptr->type->type_type != POINTER_TYPE)
	    {
	      if (varptr->type->typename == NULL)
		{
		  printf ("\n variable = %s", varptr->name);
		  if (IsRecursionReqd (varptr->type))
		    {
		      printf ("\n going to print auxtypes");
		      getchar ();
		      PrintAuxTypes (varptr->type, varptr->name);
		      printf ("\n after print auxtypes");
		      getchar ();
		      varptr->type->typename =
			(char *) malloc (strlen (varptr->name) + 11);
		      strcpy (varptr->type->typename, "RECORD_");
		      strcat (varptr->type->typename, varptr->name);
		      while (SymtabIsTypePresent (varptr->type->typename))
			strcat (varptr->type->typename, "_");
		      SymtabAddTypeAtBegin (varptr->type);
		      printf ("\n going to print typedef %s",
			      varptr->type->typename);
		      PrintTypeDef (varptr->type);
		    }
		  else if (varptr->type->type_type == RECORD_TYPE)
		    {
		      varptr->type->typename =
			(char *) malloc (strlen (varptr->name) + 11);
		      strcpy (varptr->type->typename, "RECORD_");
		      strcat (varptr->type->typename, varptr->name);
		      while (SymtabIsTypePresent (varptr->type->typename))
			strcat (varptr->type->typename, "_");
		      SymtabAddTypeAtBegin (varptr->type);
		      PrintTypeDef (varptr->type);
		    }
		}
	    }
	  varptr = varptr->nxt;
	}
      break;

    default:
      printf ("\nPrintAuxTypes: %d This type cant have aux types .. exiting",
	      ptr->type_type);
      exit (0);
      break;
    }
}
/*-------------------------------------------------------------------------*/

PrintType (Varptr vptr)
{
  Varptr varptr;
  Typeptr ptr;
  printf ("\n In Printtype , ptr= %s", vptr->name);
  getchar ();
  ptr = vptr->type;
  switch (ptr->type_type)
    {
    case INTEGER_TYPE:
      fprintf (cfile, "\n\tlong ");
      fprintf (stdout, "\n\tlong ");
      break;
    case CHAR_TYPE:
      fprintf (cfile, "\n\tchar");
      fprintf (stdout, "\n\tchar");
      break;
    case BOOLEAN_TYPE:
      fprintf (cfile, "\n\tboolean");
      fprintf (stdout, "\n\tboolean");
      break;
    case REAL_TYPE:
      fprintf (cfile, "\n\tfloat");
      fprintf (stdout, "\n\tfloat");
      break;
    case SET_TYPE:
      break;
    case ENUM_TYPE:
      {
	Idptr tmpid;
	int count;
	fprintf (cfile, "\n\tenum %s{\n\t", ptr->typename);
	fprintf (stdout, "\n\tenum %s{\n\t", ptr->typename);
	tmpid = ptr->idlist;
	count = ptr->no_of_member - 1;
	while (count--)
	  {
	    fprintf (cfile, "%s,", tmpid->idname);
	    fprintf (stdout, "%s,", tmpid->idname);
	    tmpid = tmpid->nxt;
	  }
	fprintf (cfile, "%s\n}", tmpid->idname);
	fprintf (stdout, "%s\n}", tmpid->idname);
      }
      break;
    case SUBRANGE_TYPE:
      fprintf (cfile, "\n\tlong\t%s;", ptr->typename);
      break;
    case ARRAY_TYPE:
      {
	int count;
	int finished = 0;
	Dimension *dmnptr;

	switch (ptr->elemtype->type_type)
	  {
	  case POINTER_TYPE:
	    fprintf (cfile, "\t%s\t*", ptr->elemtype->typeptr->typename);
	    break;
	  case SET_TYPE:
	    fprintf (cfile, "\t%s\t", "long");
	    break;
	  case ENUM_TYPE:
	    {
	      Idptr tmpid;
	      int count;
	      fprintf (cfile, "\n\tenum{\n\t");
	      fprintf (stdout, "\n\tenum{\n\t");
	      tmpid = ptr->elemtype->idlist;
	      count = (ptr->elemtype->no_of_member) - 1;
	      printf("\n count= %d", count); getchar();
	      while (count--)
		{ 
		  fprintf (cfile, "%s,", tmpid->idname);
		  fprintf (stdout, "%s,", tmpid->idname); getchar();
		  tmpid = tmpid->nxt;
		}
	      fprintf (cfile, "%s\n}", tmpid->idname);
	      fprintf (stdout, "%s\n}", tmpid->idname);
	    }
	    break;
	  case INTEGER_TYPE:
	  case REAL_TYPE:
	  case BOOLEAN_TYPE:
	  case CHAR_TYPE:
	  case RECORD_TYPE:
	    fprintf(cfile,"\n\t%s",ptr->elemtype->typename);
	    break;
	  case ARRAY_TYPE:
	    {
	      Typeptr tmp;
	      tmp = vptr->type;
	      vptr->type = vptr->type->elemtype;
	      PrintType (vptr);
	      vptr->type = tmp;
	      return;
	      break;
	    }
	  default:
	    printf ("\nPrintType: error how %d type comes here?",
		    ptr->type_type);
	    break;
	  }

	fprintf (cfile, "\t%s", vptr->name);
	while (!finished)
	  {
	    count = ptr->no_of_dimn;
	    dmnptr = ptr->dimensions;
	    while (count--)
	      {
		switch (dmnptr->type_flag)
		  {
		  case CHAR_TYPE:
		    fprintf (cfile, "[256]");
		    break;
		    fprintf (stdout, "[256]");
		    break;
		  case INTEGER_TYPE:
		    fprintf (cfile, "[65535]");
		    break;
		    fprintf (stdout, "[65535]");
		    break;
		  case SUBRANGE_TYPE:
		    fprintf (cfile, "[%d]",
			     GetRange ((int) dmnptr->low->value,
				       (int) dmnptr->high->value));
		    fprintf (stdout, "[%d]",
			     GetRange ((int) dmnptr->low->value,
				       (int) dmnptr->high->value));
		    break;
		  case ENUM_TYPE:
		    
		    fprintf (stdout, "[%d]", dmnptr->no_of_ids);
		    fprintf (cfile, "[%d]", dmnptr->no_of_ids);
		    fprintf (stdout, "[%d]", dmnptr->no_of_ids);
		    break;
		  case BOOLEAN_TYPE:
		    fprintf (cfile, "[2]");
		    break;
		    fprintf (stdout, "[2]");
		    break;
		  }
		++dmnptr;
	      }
	    if (ptr->elemtype->type_type == ARRAY_TYPE)
	      if (IsRecursionReqd (ptr->elemtype))
		ptr = ptr->elemtype;
	      else
		finished = 1;
	    else
	      finished = 1;
	  }
	fprintf (cfile, ";");
	fprintf (stdout, ";");
      }
      break;
    case POINTER_TYPE:
      fprintf (cfile, "\n\t%s\t*", ptr->typeptr->typename);
      fprintf (cfile, "%s;", vptr->name);
      fprintf (stdout, "\n\t%s\t*", ptr->typeptr->typename);
      fprintf (stdout, "%s;", vptr->name);
      break;
    case FILE_TYPE:
      break;
    default:
      printf ("\n PrintType: this type is not supported ");
      break;
    }
  fprintf (cfile, "\n");
}

/*-------------------------------------------------------------------------*/
int PrintFuncHeader()
{ Argptr argptr;
  char *chptr;
  printf("In Printfuncheader"); getchar(); 
  if(currfun->ret_type)
  fprintf(cfile,"\n%s",currfun->ret_type->typename);
  else fprintf(cfile,"\nvoid");		// for procedure 
  fprintf(cfile,"\t%s(",currfun->fname);  
  if(currfun->level)
  {
    argptr=currfun->arglist;
    while(argptr)
    {
       fprintf(cfile,"%s  ",argptr->type->typename);
       if(argptr->arg_type==VAR_PARAM &&
		       argptr->type->type_type!=ARRAY_TYPE)
       { 
/*         chptr=(char *)malloc(strlen(argptr->name)+3);
         strcpy(chptr,argptr->name);
	 argptr->name=(char *)malloc(strlen(argptr->name)+3);
         strcpy(argptr->name,"*");
         strcat(argptr->name,chptr);*/
	       fprintf(cfile,"*");
       }
       if(argptr->nxt) 
	    fprintf(cfile,"%s,",argptr->name);
       else  
	    fprintf(cfile,"%s",argptr->name);  
       argptr=argptr->nxt;	  
    }
  }
  else fprintf(cfile,"long argc,char *argv[]");
  if(currfun->level>1)
  { fprintf(cfile,",LOCAL_%s  *SCP",currfun->parent->fname);
  }
  fprintf(cfile,")");
}
/*-------------------------------------------------------------------------*/
int PrintFuncLocalVar()
{  if(currfun->level)
   {
	fprintf(cfile,"\n");
	PrintIndent();
	fprintf(cfile,"LOCAL_%s\t W;",currfun->fname);
  }
   if(currfun->ret_type!=NULL) // for function print ret_value var name
   {  currfun->ret_value_name=(char *)malloc(strlen(currfun->fname)+10);
      strcpy(currfun->ret_value_name,currfun->fname);
      strcat(currfun->ret_value_name,"_");
      while(SymtabIsNameDefined(currfun->ret_value_name))
		strcat(currfun->ret_value_name,"_");
      fprintf(cfile,"\n");
      PrintIndent();
      fprintf(cfile,"%s\t%s;",currfun->ret_type->typename,
		      currfun->ret_value_name);	  	
   }
	if(currfun->level>1) {fprintf(cfile,"\n");PrintIndent();
	fprintf(cfile,"W.SCP=SCP;");}
}
/*-------------------------------------------------------------------------*/
int PrintOpenBrace()
{	fprintf(cfile,"\n");
 	PrintIndent();
	fprintf(cfile,"{");
}
/*-------------------------------------------------------------------------*/

int PrintCloseBrace()
{	fprintf(cfile,"\n");
	PrintIndent();
	fprintf(cfile,"}");
}
/*-------------------------------------------------------------------------*/
PrintIndent ()
{
  int i;
  for (i = 0; i < indent * 3; i++)
    fprintf (cfile, " ");
}
int PrintFwdDecl()
{ Argptr argptr;
  char *chptr;
  printf("In PrintFwdDecl;"); getchar(); 
  if(currfun->ret_type)
  fprintf(cfile,"\n%s",currfun->ret_type->typename);
  else fprintf(cfile,"\nvoid");		// for procedure 
  fprintf(cfile,"\t%s(",currfun->fname);  
  if(currfun->level)
  {
    argptr=currfun->arglist;
    while(argptr)
    {
       fprintf(cfile,"%s  ",argptr->type->typename);
       if(argptr->arg_type==VAR_PARAM &&
		       argptr->type->type_type!=ARRAY_TYPE)
       { 
/*         chptr=(char *)malloc(strlen(argptr->name)+3);
         strcpy(chptr,argptr->name);
	 argptr->name=(char *)malloc(strlen(argptr->name)+3);
         strcpy(argptr->name,"*");
         strcat(argptr->name,chptr);*/
	       fprintf(cfile,"*");
       }
       if(argptr->nxt) 
	    fprintf(cfile,",",argptr->name);
  /*     else  
	    fprintf(cfile,"%s",argptr->name);  */
       argptr=argptr->nxt;	  
    }
  }
/*  else fprintf(cfile,"long argc,char *argv[]");*/
  if(currfun->level>1)
  { fprintf(cfile,",LOCAL_%s  *SCP",currfun->parent->fname);
  }
  fprintf(cfile,");");
}
