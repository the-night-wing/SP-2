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
extern FILE *cfile;
extern Funptr tempfun;
extern Typeptr temptype;
extern Varptr tempvar;
extern Argptr temparg;
extern Idptr tempid;

extern int func_level;
/******************************************************************/
Typeptr TpCheckGetTypePtr(char *idname,int *currlevel,
		int *foundlevel,int *type,char *buf)
{  Argptr aptr;
   Varptr vptr;
   Constptr cptr;
   Funptr fptr;
  Typeptr tptr;
   printf("\n In TpCheckGetTypePtr"); getchar();
   fptr=currfun; 
   while(fptr)
   {  vptr=fptr->varlist;
      while(vptr)
      {   if(mystrcmp(idname,vptr->name)==0)
	  { 	*foundlevel=fptr->level;
		*currlevel=currfun->level;
		*type=1; // local var in W.
	      printf("\n %s found , in func %s variable ",idname,fptr->fname);	
	      getchar();
	        return vptr->type;
	  }
	  else vptr=vptr->nxt;
       }
      aptr=fptr->arglist;
      while(aptr)
      {   if(mystrcmp(idname,aptr->name)==0)
	  { 	*foundlevel=fptr->level;
		*currlevel=currfun->level;
		if(aptr->arg_type==VAR_PARAM) *type=2; //var param
		else *type=3; // value param
	      printf("\n %s found , in func %s arg ",idname,fptr->fname);	
	      getchar();
	        return aptr->type;
	  }
	  else aptr=aptr->nxt;
      }
      cptr=fptr->constlist;
      while(cptr)
      {  if(mystrcmp(idname,cptr->name)==0)
	  { 	*foundlevel=fptr->level;
		*currlevel=currfun->level;
		*type=4;
	      printf("\n %s found , in func %s const ",idname,fptr->fname);	
	      getchar();
		if(cptr->const_type==CONST_INT) return basic_types;
		else if(cptr->const_type==CONST_REAL) return basic_types+1;
		else if(cptr->const_type==CONST_CHAR) return basic_types+2;
	  }
	  else cptr=cptr->nxt;
      }
      tptr=currfun->typelist;
      while(tptr)
      { if(tptr->type_type==ENUM_TYPE)
	      { Idptr idptr;
		idptr=tptr->idlist;
		while(idptr)
		{ if(mystrcmp(idname,idptr->idname)==0)
			{    *foundlevel=fptr->level;
			       *currlevel=currfun->level;
		       	   *type=6;	       
				return basic_types;
			}
		  idptr=idptr->nxt;		
		}
	      }
	 tptr=tptr->nxt;     
      }
      if(mystrcmp(idname,fptr->fname)==0)
      { if(fptr==currfun)
	   if(fptr->ret_type)
	  {
		  *foundlevel=fptr->level;
		 *currlevel=currfun->level;
		 *type=5;
		 printf("\n %s found , in func %s fname itself ",
				 idname,fptr->fname);	
		 getchar();
		 strcpy(buf,fptr->ret_value_name);
		 return fptr->ret_type;
	  }
	   else tperror(PROCEDURE_RET_TYPE_REF);
	else tperror(OUT_OF_SCOPE_REF);
      }
     fptr=fptr->parent;	   
   }
   printf("\n %s not found ",idname); getchar();
   return NULL; 
}
int TpCheckGetArrayLimitDiff(Typeptr type,int count,char *buf)
{ 
      Dimension *dmnptr; char tmp[128];
      dmnptr=type->dimensions;
      if(dmnptr[count].type_flag==ENUM_TYPE)
      {      strcpy(buf,"");	// as enum by def shall start from 0 in C 
	      return;
      }
     else if(dmnptr[count].type_flag==SUBRANGE_TYPE)
     {  if(dmnptr[count].low->const_type==CONST_CHAR)
	 { strcpy(buf,"-1"); 
	   return;	     
	  }
	 else { 
		 if(dmnptr[count].low->value<=0)
	 {   strcpy(buf,"+");
		 
	     sprintf(tmp,"%d",(int)-dmnptr[count].low->value);
	     strcat(buf,tmp);
	     return;
	 } else 
	 {   strcpy(buf,"-");
	     sprintf(tmp,"%d",(int)dmnptr[count].low->value);
	     strcat(buf,tmp);
	     return;
	 }}
     }
}
Typeptr TpCheckIsRecField(Typeptr type,char *name)
{ Typeptr ptr;
  Varptr vptr;
  vptr=type->varlist;
  while(vptr)
  {     if(mystrcmp(vptr->name,name)==0)
	  {   printf("\n IsRecField: %s found",name);
		printf("\n ret_type= %d",vptr->type->type_type);  
		getchar();
		  return vptr->type;
	  }
	vptr=vptr->nxt;
  }  
  return NULL;
}
Argptr TpCheckIsProcInScope(char *name,int *currlevel,
		int *proclevel,int *no_of_arg,int *is_func,Typeptr *tptr)
{  Funptr fptr;
   int i,found;
   fptr=currfun;	
   *currlevel=currfun->level;
   // check for parent and grands
   while(fptr->level)	// i.e. dont check for outer block	
   { if(mystrcmp(fptr->fname,name)==0)
     { *proclevel=fptr->level;
	*no_of_arg=fptr->no_of_arg;     
	*is_func=(currfun->ret_type!=NULL);
	 *tptr=currfun->ret_type;
	return fptr->arglist;     
     }
    fptr=fptr->parent; 
   }
   // check for child
   fptr=currfun;
   i=currfun->no_of_children;
   while(i--)
   { if((mystrcmp(currfun->children[i]->fname,name))==0)
	   {*proclevel=fptr->level+1;
	  *no_of_arg=currfun->children[i]->no_of_arg;     
	*is_func=(currfun->ret_type!=NULL);
	 *tptr=currfun->ret_type;
	    return currfun->children[i]->arglist;	   	
	   }
   }
   // check for siblings defined before
   i=currfun->parent->no_of_children;  found=0;
   fptr=currfun->parent->children[0];
   while(--i && !found)
   {  if(mystrcmp(fptr->fname,currfun->fname)==0)
	   found=1;
      else {
	      if(mystrcmp(fptr->fname,name)==0)
	      { *proclevel=currfun->level;
		 *no_of_arg=fptr->no_of_arg;     
	*is_func=(currfun->ret_type!=NULL);
	 *tptr=currfun->ret_type;
		 return fptr->arglist;     
	      }
   	}	      
   }
   return NULL;
}
extern char *std_func_list[];
TpCheckIsStdFunc(char *name)
{   char *ptr; int i=0;
    for(i=0;i<30;i++)
    {  ptr=std_func_list[i];
	if(mystrcmp(ptr,name)==0)
	{	printf("\n stdfunc case %d found",i); getchar();
		return 1;
	}
    }	   
   return 0; 
}
