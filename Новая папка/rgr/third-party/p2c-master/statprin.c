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
extern int indent ;
extern Type basic_types[4];
/*-------------------------------------------------------------------------*/
Print(char *str)
{ fprintf(cfile,"%s",str);
}
PrintFuncRetStat()
{ if(currfun->ret_type){
   fprintf(cfile,"\n"); PrintIndent();
   fprintf(cfile,"return %s;",currfun->ret_value_name);	
   }
	
}
extern char *std_func_list[];
Typecheckptr PrintStdFuncCall(char *fname,Typecheckptr paramlist,int flag)
{
   char *ptr; int i,index=-1;
   Typecheckptr temp,ret_val;
    
    for(i=0;i<30;i++)
    {  ptr=std_func_list[i];
	if(mystrcmp(ptr,fname)==0)
	 { index=i; break;}
    }	   
    if(index==-1) 
    { printf("\n PrintStdFuncCall: %s is not a std function ",fname); 
      exit(0);
    }
    temp=paramlist;
    switch(index)
    {  
	case 0: 		// append
		break;
	case 1: 		//assign
		break;
	case 2: 		//close
		break;	
	case 3: 		//dispose
		if(temp->nxt) 
			tperror(PROC_WRONG_NO_OF_ARG);
		if(flag)  // function_designator
		{  tperror(ID_NOT_FUNC);
		}
		Print("\n");PrintIndent();Print("free(");
		Print(temp->string);Print(");");
		break;
	case 4: 		//new
		if(temp->nxt) 
			tperror(PROC_WRONG_NO_OF_ARG);
		if(flag) tperror(ID_NOT_FUNC);
		Print("\n"); PrintIndent();Print(temp->string);
		Print("=(");Print(temp->type->typename);Print(")");
		Print("malloc(sizeof(");Print(temp->type->typeptr->typename);
		Print("));");
		break;
	case 5: 		//pack
		break;
	case 7: 		//readln
	//	Print("\n");PrintIndent();Print("getchar();");Print("\n");	
	//	break;
	case 6: 		//read
	{	char buf[120]; strcpy(buf,"");
		Print("\n"); PrintIndent(); Print("scanf(\"");
		while(temp)
		{  if(temp->type->type_type==CHAR_TYPE)
		   { Print("%c"); strcat(buf,",&");
		     strcat(buf,temp->string);	
		   }
		     else if(temp->type->type_type==INTEGER_TYPE)
		     {	 strcat(buf,",&");strcat(buf,temp->string);
			 Print("%d");
		     }
		     else  if(temp->type->type_type==REAL_TYPE)
		     {	 strcat(buf,",&");strcat(buf,temp->string);
			 Print("%f");
		     }
		     else tperror(PROC_WRONG_TYPE_ARG);
 		   temp=temp->nxt;
		}	
		Print("\"");Print(buf);Print(");");
		break;
	}
	case 8: 		//reset
		break;
	case 9: 		//rewrite
		break;
	case 10:		//unpack
	       	break;
	case 12:		//writeln same as write except newline at end
	case 11:			//write
	{	char buf[120];
		Print("\n");PrintIndent();Print("printf(\"");
		strcpy(buf,"");
		while(temp)
		{    if(temp->type->type_type==CHAR_TYPE)
			 Print(temp->string);
		     else if(temp->type->type_type==INTEGER_TYPE)
		     {	 strcat(buf,",");strcat(buf,temp->string);
			 Print(" %d ");
		     }
		     else  if(temp->type->type_type==REAL_TYPE)
		     {	 strcat(buf,",");strcat(buf,temp->string);
			 Print(" %f ");
		     }
		     else if(temp->type->type_type==BOOLEAN_TYPE)
		     {	 strcat(buf,",");strcat(buf,temp->string);
			 Print(" %d ");    
		     }
		     else tperror(PROC_WRONG_TYPE_ARG);
		     temp=temp->nxt;
		} 
		if(index==12) Print("\\n");
		Print("\"");
		Print(buf); Print(");");
		 break;
	}
	case 13: 		//abs
		break;
	case 14: 		//arctan
		break;
	case 15: 		//chr
		break;
	case 16: 		//cos
		break;	
	case 17:		//eof
	       	break;
	case 18			//eoln
		: break;
	case 19:		//exp
       		break;
	case 20: 		//ln
		break;
	case 21:		//odd
	       	break;
	case 22:		//ord
	       	break;
	case 23:		//pred
	       	break;
	case 24:		//round
	       	break;
	case 25:		//sin
	       	break;
	case 26:		//sqr
	case 27:		//sqrt
		if(temp->nxt) 
			tperror(PROC_WRONG_NO_OF_ARG);
		if(flag)
		{  ret_val=(Typecheckptr)malloc(sizeof(Typecheck));
		   ret_val->nxt=NULL;
	   	   ret_val->string=(char *)malloc(strlen(temp->string)+10);
			   strcpy(ret_val->string,"sqr");
		   if(index==27) strcat(ret_val->string,"t");
		   strcat(ret_val->string,"(");
		   strcat(ret_val->string,temp->string);
		   strcat(ret_val->string,")");	   
		   ret_val->type=basic_types+1;		// float
		   return ret_val;
		}
		else {
			Print("sqrt(");Print(temp->string);Print(");");
		}
	       	break;
	case 28:		//succ
	       	break;
	case 29:		//trunc
		if(temp->nxt) 
			tperror(PROC_WRONG_NO_OF_ARG);
		if(flag)
		{  ret_val=(Typecheckptr)malloc(sizeof(Typecheck));
		   ret_val->nxt=NULL;
	   	   ret_val->string=(char *)malloc(strlen(temp->string)+12);
		   strcpy(ret_val->string,"(int)(");
		   strcat(ret_val->string,temp->string);
		   strcat(ret_val->string,"/1)");	   
		   ret_val->type=basic_types;		// int
		   return ret_val;	
		}
		else{
			Print("(");Print(temp->string);Print("/1);");
		}
	       	break;
	default:
       		printf("\n PrintStdFunc: How comes defualt case %d here ?",index);	break;		
    }
    		    
}
