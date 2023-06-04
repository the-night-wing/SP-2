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
extern Typeptr FwdRefList;
extern Varptr currvar;
extern Constptr currconst;
extern Argptr currarg;
extern Idptr currid, curridlist;	//curridlist is current list of identifiers 
			 // currid points to the last node in the current list

Type basic_types[4] = {
  {"int", INTEGER_TYPE, 0,0},
  {"float", REAL_TYPE, 0, 0},
  {"char", CHAR_TYPE, 0, 0},
  {"boolean", BOOLEAN_TYPE, 0, 0}
};
extern int func_level;
extern int prev_func_level;

/*The type has to be created seperately using function SymtabCreateNewType below
* This function only inserts that type into current typelist of current function
*/
int
SymtabInsertType (Typeptr ptr)
{
  printf ("\n INSERTING TYPE %s", ptr->typename);
  ptr->func=currfun;
  if (currfun->typelist == NULL)
    {
      currtype = ptr;
      currfun->typelist = ptr;
    }
  else
    {
      currtype->nxt = ptr;
      currtype = ptr;
    }
  printf ("\n SymtabINsertType: After inserting printing typelist");
  SymtabPrintTypeList ();
}

/*--------------------------------------------------------------------*/

/* Creates a new type.
* The no. of arguments are interpreted from type_type value. 
*  The switch statement handled each type case seperately
*/
Typeptr
SymtabCreateNewType (int type_type, ...)
{
  Typeptr temp, temp2, temp3;
  char *tempchar;
  int count = 0;
  Idptr tempidptr;
  va_list ap;

  temp = (Typeptr) malloc (sizeof (Type));
  temp->type_type = type_type;
  temp->nxt = NULL;
  temp->typename = NULL;

  va_start (ap, type_type);

  switch (type_type)
    {
    case ENUM_TYPE:
      temp->idlist = va_arg (ap, Idptr);
      tempidptr = (Idptr) temp->idlist;
      count=0;
      while (tempidptr)
	{
	  ++count;
	  tempidptr = tempidptr->nxt;
	}
      temp->no_of_member = count;
      printf ("\n CreateNewType: created enum type... no.of.ids = %d ",
	      temp->no_of_member);
      if (temp->idlist == NULL)
	printf ("\n CreateNewType:Wonder how comes empty idlist ");
      break;

    case SUBRANGE_TYPE:
      // assumed that low value is always less than high value
      (temp->low) = va_arg (ap, Constptr);
      (temp->high) = va_arg (ap, Constptr);
      if (temp->low->const_type == CONST_REAL
	  || temp->high->const_type == CONST_REAL)
	{
	  error (INVALID_SUBRANGE_TYPE);
	  free (temp);
	  return NULL;
	}
      printf ("\n CreateNewType: subrange created ");
      printf (" low= ");
      switch (temp->low->const_type)
	{
	case CONST_INT:
	  printf ("%d ", (int) (temp->low->value));
	  break;
	case CONST_REAL:
	  printf ("%f ", temp->low->value);
	  break;
	case CONST_CHAR:
	  printf ("%s ", temp->low->string);
	  if(strlen(temp->low->string)>1)
	  {	  error(INVALID_SUBRANGE_TYPE);
		  free(temp);
		  return NULL;
	  }
	  break;
	}
      printf (" high= ");
      switch (temp->low->const_type)
	{
	case CONST_INT:
	  printf ("%d ", (int) temp->high->value);
	  break;
	case CONST_REAL:
	  printf ("%f ", temp->high->value);
	  break;
	case CONST_CHAR:
	  printf ("%s ", temp->high->string);
	  if(strlen(temp->high->string)>1)
	  {	  error(INVALID_SUBRANGE_TYPE);
		  free(temp);
		  return NULL;
	  }
	  break;
	}
      break;

    case ARRAY_TYPE:
      temp2 = va_arg (ap, Typeptr);
      temp->elemtype = va_arg (ap, Typeptr);
      temp3 = temp2;		//save for future 
      count = 0;
      while (temp2 != NULL)
	{
	  ++count;
	  temp2 = temp2->nxt;
	}
      temp->no_of_dimn = count;
      temp->dimensions = (Dimension *) malloc (count * sizeof (Dimension));
      temp2 = temp3;		// this is the future-- see above comment
      count = 0;
      while (temp2 != NULL)
	{
	  temp->dimensions[count].type_flag = temp2->type_type;
	  switch (temp2->type_type)
	    {
	    case SUBRANGE_TYPE:
	      if (temp2->low->const_type == REAL_TYPE ||
		  temp2->high->const_type == REAL_TYPE)
		{
		  printf ("\n CreateType:Real type not allowed as index ");
		  free (temp);
		  return NULL;
		}
	      temp->dimensions[count].low = temp2->low;
	      temp->dimensions[count].high = temp2->high;
	      break;
	    case ENUM_TYPE:
	      temp->dimensions[count].no_of_ids = temp2->no_of_member;
	      temp->dimensions[count].idptr = temp2->idlist;
	      break;
	    case INTEGER_TYPE:
	      temp->dimensions[count].low =
		(Constptr) malloc (sizeof (Constant));
	      temp->dimensions[count].low->name = (char *) malloc (8);
	      strcpy (temp->dimensions[count].low->name, "SHRT_MIN");
	      temp->dimensions[count].low->value = -32768;
	      temp->dimensions[count].low->const_type = CONST_INT;

	      temp->dimensions[count].high =
		(Constptr) malloc (sizeof (Constant));
	      temp->dimensions[count].high->name = (char *) malloc (8);
	      strcpy (temp->dimensions[count].high->name, "SHRT_MAX");
	      temp->dimensions[count].high->value = 32767;
	      temp->dimensions[count].high->const_type = CONST_INT;
	      break;
	    case CHAR_TYPE:
	      temp->dimensions[count].low =
		(Constptr) malloc (sizeof (Constant));
	      temp->dimensions[count].low->name = (char *) malloc (7);
	      strcpy (temp->dimensions[count].low->name, "CHAR_MIN");
	      temp->dimensions[count].low->value = (char) 0;
	      temp->dimensions[count].low->const_type = CONST_CHAR;

	      temp->dimensions[count].high =
		(Constptr) malloc (sizeof (Constant));
	      temp->dimensions[count].high->name = (char *) malloc (7);
	      strcpy (temp->dimensions[count].high->name, "CHAR_MAX");
	      temp->dimensions[count].high->value = (char) 255;
	      temp->dimensions[count].high->const_type = CONST_CHAR;
	      break;
	    case BOOLEAN_TYPE:
	      {
		char *tmp;
		Idptr idtmp;
		temp->dimensions[count].no_of_ids = 2;
		temp->dimensions[count].idptr =
		  (Idptr) malloc (sizeof (Idnode));
		temp->dimensions[count].idptr->idname = (char *) malloc (6);
		tmp = temp->dimensions[count].idptr->idname;
		idtmp = temp->dimensions[count].idptr;
		strcpy (tmp, "false");
		idtmp->nxt = (Idptr) malloc (sizeof (Idnode));
		idtmp->nxt->nxt = NULL;
		idtmp->nxt->idname = (char *) malloc (6);
		strcpy (idtmp->nxt->idname, "true");
	      }
	      break;
	    default:
	      printf ("\n in createnewtype.. array dimn type wrong");
	      break;
	    }
	  temp2 = temp2->nxt;
	  ++count;
	}
      break;

    case RECORD_TYPE:
      {
	int i;
	Varptr tempvar;
	i = va_arg (ap, int);
	switch (i)
	  {
	  case 1:
	    temp->varlist = va_arg (ap, Varptr);
	    break;
	  case 2:
	    temp->varlist = va_arg (ap, Varptr);
/*	HANDLE THIS CASE.. THIS IS VARINAT RECORD +FIXED CASE */
	    break;
	  case 3:
/*	HANDLE THIS CASE.. THIS IS VARINAT RECORD ONLY CASE */
	    break;
	  default:
	    printf ("\n p2c: record can be only of 3 types");
	    break;
	  }
      }
      break;

    case SET_TYPE:
      temp2 = va_arg (ap, Typeptr);
      temp->dimension.type_flag = temp2->type_type;
      switch (temp2->type_type)
	{
	case ENUM_TYPE:
	  temp->dimension.no_of_ids = temp2->no_of_member;
	  temp->dimension.idptr = temp2->idlist;
	  temp->no_of_elem = temp2->no_of_member;
	  break;
	case SUBRANGE_TYPE:
	  if (temp2->low->const_type == CONST_REAL ||
	      temp2->high->const_type == CONST_REAL)
	    {
	      printf ("\n CreateType: real subrange not allowed");
	      free (temp);
	      return NULL;
	    }
	  temp->dimension.low = temp2->low;
	  temp->dimension.high = temp2->high;
	  temp->no_of_elem = GetRange (temp->dimension.low->value,
				       temp->dimension.high->value);
	  break;
	case INTEGER_TYPE:
	  temp->dimension.low = (Constptr) malloc (sizeof (Constant));
	  temp->dimension.low->name = (char *) malloc (10);
	  strcpy (temp->dimension.low->name, "INT_MIN");
	  temp->dimension.low->value = (float) -32768;
	  temp->dimension.low->const_type = CONST_INT;
	  temp->dimension.low->nxt = NULL;
	  temp->dimension.high = (Constptr) malloc (sizeof (Constant));
	  temp->dimension.high->name = (char *) malloc (10);
	  strcpy (temp->dimension.high->name, "INT_MAX");
	  temp->dimension.high->value = (float) 32767;
	  temp->dimension.high->const_type = CONST_INT;
	  temp->no_of_elem = 65535;
	  break;
	case CHAR_TYPE:
	  temp->dimension.low = (Constptr) malloc (sizeof (Constant));
	  temp->dimension.low->name = (char *) malloc (10);
	  strcpy (temp->dimension.low->name, "CHAR_MIN");
	  temp->dimension.low->value = (float) 0;
	  temp->dimension.low->const_type = CONST_CHAR;

	  temp->dimension.high = (Constptr) malloc (sizeof (Constant));
	  temp->dimension.high->name = (char *) malloc (10);
	  strcpy (temp->dimension.high->name, "CHAR_MAX");
	  temp->dimension.high->value = (float) 255;
	  temp->dimension.high->const_type = CONST_CHAR;
	  temp->no_of_elem = 256;
	  break;
	  break;
	case BOOLEAN_TYPE:
	  {
	    char *tmp;
	    Idptr idtmp;
	    temp->dimension.no_of_ids = temp->no_of_elem = 2;
	    temp->dimension.idptr = (Idptr) malloc (sizeof (Idnode));
	    temp->dimension.idptr->idname = (char *) malloc (6);
	    tmp = temp->dimension.idptr->idname;
	    strcpy (tmp, "false");
	    idtmp = temp->dimension.idptr;
	    idtmp->nxt = (Idptr) malloc (sizeof (Idnode));
	    idtmp->nxt->nxt = NULL;
	    idtmp->nxt->idname = (char *) malloc (6);
	    strcpy (idtmp->nxt->idname, "true");
	  }
	  break;
	default:
	  printf ("\n CreateNewType:not an ordinal type for set ");
	  break;
	}
      break;

    case FILE_TYPE:
      // do nothing .. all has been done
      break;

    case POINTER_TYPE:
      {
	char *tmp;
	temp->typeptr = va_arg (ap, Typeptr);
	if (temp->typeptr == NULL)
	  {
	    temp->is_fwd_ref = 1;
	    tmp = va_arg (ap, char *);
	    temp->fwd_ref_name = (char *) malloc (strlen (tmp) + 1);
	    strcpy (temp->fwd_ref_name, tmp);
	  }
	else
	  temp->is_fwd_ref = 0;
      }
      break;

    case INTEGER_TYPE:
      // do nothing?
      break;

    case REAL_TYPE:
      // do nothing?
      break;

    case CHAR_TYPE:
      // do nothing?
      break;

    case BOOLEAN_TYPE:
      // do nothing?
      break;


    case EXISTING:
      {
	Typeptr tmp;
	tmp = va_arg (ap, Typeptr);
	*temp = *tmp;
	temp->nxt = NULL;
	temp->typename = NULL;
      }
      break;
    default:
      printf ("\nSymtabCreateNewType: wrong argument for type_type");
    }
  va_end (ap);
  return temp;
}

/*--------------------------------------------------------------------*/
/* Check if type definition of  given name is present
 * If YES return a pointer to that defn , return NULL otherwise
 *  if type is basic one then a pointer to predefined array member is returned
 */
Typeptr
SymtabIsTypePresent (char *typename)
{
  Typeptr temp;
  Funptr tempfun;
  tempfun = currfun;
  if (mystrcmp (typename, "integer") == 0)
    return basic_types;
  if (mystrcmp (typename, "real") == 0)
    return basic_types + 1;
  if (mystrcmp (typename, "char") == 0)
    return basic_types + 2;
  if (mystrcmp (typename, "boolean") == 0)
    return basic_types + 3;
  while (tempfun != NULL)
    {
      temp = tempfun->typelist;
      while (temp != NULL)
	{
	  if (mystrcmp (temp->typename, typename) == 0)
	    {
	      //currtype = temp;  this stat is GREAT MISTAKE TOOK 2 HOURS
	      return temp;
	    }
	  else
	    temp = temp->nxt;
	}
      tempfun = tempfun->parent;
    }
  printf ("\n IsTypePresent(): %s not found", typename);
  return NULL;
}

/*--------------------------------------------------------------------*/
/* print current list of types in the current function */
int
SymtabPrintTypeList ()
{
  Typeptr temp;
  int i = 0, count = 0, j;
  Dimension *dmnptr;

  temp = currfun->typelist;
  printf ("\nPrinting Typelist ");
  while (temp != NULL)
    {
      ++i;
      printf ("\n %d ) %s ", i, temp->typename);
      switch (temp->type_type)
	{
	case INTEGER_TYPE:
	  printf ("\nTYPE= integer");
	  break;
	case REAL_TYPE:
	  printf ("\nTYPE= real");
	  break;
	case CHAR_TYPE:
	  printf ("\nTYPE=char");
	  break;
	case BOOLEAN_TYPE:
	  printf ("\nTYPE=boolean");
	  break;
	case ENUM_TYPE:
	  printf ("\nTYPE= enum");
	  printf ("  idlist=");
	  SymtabPrintIdlist (temp->idlist);
	  break;
	case SUBRANGE_TYPE:
	  printf ("\nTYPE=subrange type");
	  switch (temp->low->const_type)
	    {
	    case CONST_INT:
	      printf ("low= %d  ", (int) temp->low->value);
	      break;
	    case CONST_CHAR:
	      printf ("low= %s  ", temp->low->string);
	      break;
	    default:
	      printf ("\n PrintType:invalid type for subrange ");
	    }
	  switch (temp->high->const_type)
	    {
	    case CONST_INT:
	      printf ("high= %d ", (int) temp->high->value);
	      break;
	    case CONST_CHAR:
	      printf ("high= %s ", temp->high->string);
	      break;
	    default:
	      printf ("\n PrintType:invalid type for subrange ");
	    }
	  break;
	case ARRAY_TYPE:
	  printf ("\nTYPE=array type");
	  printf ("\n no of subscripts = %d  ARRAY of %s", temp->no_of_dimn,
		  temp->elemtype->typename);
	  dmnptr = temp->dimensions;
	  count = 0;
	  j = temp->no_of_dimn;
	  printf ("\n subscipts are ");
	  while (count < (j))
	    {
	      switch (dmnptr[count].type_flag)
		{
		case SUBRANGE_TYPE:
		  {
		    printf ("\nsubrange ");
		    switch (dmnptr[count].low->const_type)
		      {
		      case CONST_INT:
			printf ("low= %d  ", (int) dmnptr[count].low->value);
			break;
		      case CONST_CHAR:
			printf ("low= %s  ", dmnptr[count].low->string);
			break;
		      default:
			printf ("\n PrintType:invalid type for subrange ");
		      }
		    switch (dmnptr[count].high->const_type)
		      {
		      case CONST_INT:
			printf ("high= %d ", (int) dmnptr[count].high->value);
			break;
		      case CONST_CHAR:
			printf ("high= %s ", dmnptr[count].high->string);
			break;
		      default:
			printf ("\n PrintType:invalid type for subrange ");
		      }
		  }
		  break;

		case ENUM_TYPE:
		  printf ("\nenum ");
		  SymtabPrintIdlist (dmnptr[count].idptr);
		  break;
		case INTEGER_TYPE:
		  printf (" integer ");
		  printf (" %d..%d",
			  dmnptr[count].low->value,
			  dmnptr[count].high->value);
		  break;
		case CHAR_TYPE:
		  printf (" char ");
		  printf (" %d..%d",
			  dmnptr[count].low->value,
			  dmnptr[count].high->value);
		  break;
		case BOOLEAN_TYPE:
		  printf ("bool ");
		  SymtabPrintIdlist (dmnptr[count].idptr);
		  break;
		default:
		  printf ("\n SymtabPrintTypelist: invalid array subsr type");
		  break;
		}
	      ++count;
	    }
	  break;
	case RECORD_TYPE:
	  {
	    Varptr tempvar;
	    int i = 0;
	    printf ("\n TYPE= record type");
	    printf ("\n record fields are:\n");
	    tempvar = temp->varlist;
	    while (tempvar != NULL)
	      {
		++i;
		printf ("\n %d) %s ", i, tempvar->name);
		printf ("type info = ");
		SymtabPrintType (tempvar->type);
		tempvar = tempvar->nxt;
	      }
	  }
	  break;
	case SET_TYPE:
	  switch (temp->dimension.type_flag)
	    {
	    case ENUM_TYPE:
	      printf ("\n set of enumerations ");
	      printf ("\n idlist= ");
	      SymtabPrintIdlist (temp->dimension.idptr);
	      printf ("\n No. of elements = %d", temp->no_of_elem);
	      break;
	    case SUBRANGE_TYPE:
	      printf ("\n set of subrange ");
	      switch (temp->dimension.low->const_type)
		{
		case CONST_INT:
		  printf ("low= %d  ", (int) temp->dimension.low->value);
		  break;
		case CONST_CHAR:
		  printf ("low= %s  ", temp->dimension.low->string);
		  break;
		default:
		  printf ("\n PrintType:invalid type for set ");
		}
	      switch (temp->dimension.high->const_type)
		{
		case CONST_INT:
		  printf ("high= %d ", (int) temp->dimension.high->value);
		  break;
		case CONST_CHAR:
		  printf ("high= %s ", temp->dimension.high->string);
		  break;
		default:
		  printf ("\n PrintType:invalid type for set ");
		}
	      printf ("\n No. of elements = %d", temp->no_of_elem);
	      break;
	    case INTEGER_TYPE:
	      printf ("\n set of integers ");
	      printf ("\n limits are %d %d", (int) temp->dimension.low->value,
		      (int) temp->dimension.high->value);
	      printf ("\n No. of elements = %d", temp->no_of_elem);
	      break;
	    case CHAR_TYPE:
	      printf ("\n set of characters ");
	      printf ("\n limits are %d %d", (int) temp->dimension.low->value,
		      (int) temp->dimension.high->value);
	      printf ("\n No. of elements = %d", temp->no_of_elem);
	      break;
	    case BOOLEAN_TYPE:
	      printf ("\n set of boolean ");
	      printf ("\n idlist= ");
	      SymtabPrintIdlist (temp->dimension.idptr);
	      printf ("\n No. of elements = %d", temp->no_of_elem);
	      break;
	    default:
	      printf ("\n PrintTypelist: non ordinal type for set ");
	      break;
	    }
	  break;
	case FILE_TYPE:
	  break;
	case POINTER_TYPE:
	  printf (" TYPE=pointer type");
	  if (temp->is_fwd_ref)
	    printf ("\n forward reference ");
	  else
	    printf ("\n %s = pointer to %s ",
		    temp->typename, temp->typeptr->typename);
	  break;
	}
      temp = temp->nxt;
    }
}

/*****************************************************************************/
int
SymtabPrintType (Typeptr temp)
{
  printf ("\n %d", temp->type_type);
}

/*--------------------------------------------------------------------*/
int
SymtabIsOrdinalType (int type)
{
  if (type == ENUM_TYPE || type == SUBRANGE_TYPE || type == CHAR_TYPE
      || type == INTEGER_TYPE || type == BOOLEAN_TYPE)
    return 1;
  else
    return 0;
}

/*--------------------------------------------------------------------*/

int
SymtabVerifyFwdRef ()
{
  Typeptr temp1, temp2, temp3;
  int found;
  temp1 = currfun->typelist;
  while (temp1)
    {
      if (temp1->type_type == POINTER_TYPE)
	if (temp1->is_fwd_ref == 1)
	  {
	    temp2 = currfun->typelist;
	    found = 0;
	    while (temp2 && found == 0)
	      {
		if (mystrcmp (temp2->typename, temp1->fwd_ref_name) == 0)
		{  temp1->typeptr=temp2;
		  found = 1;
		}
		else
		  temp2 = temp2->nxt;
	      }
	    if (found == 0)
	      error (UNDEFINED_FWD_REF, temp1->fwd_ref_name);
	  }
      temp1 = temp1->nxt;
    }
//   SymtabDeleteFwdRefList();
}
int SymtabAddTypeAtBegin(Typeptr ptr)
{ Typeptr temp;
  temp=(Typeptr)malloc(sizeof(Type));
  temp->typename=(char *)malloc(strlen(ptr->typename)+1);
 *temp=*ptr;  
 strcpy(temp->typename,ptr->typename);
 temp->nxt=currfun->typelist;
currfun->typelist=temp; 
}
