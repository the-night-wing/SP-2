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


%{
#include <stdio.h>
#include <stdarg.h>
#include "prototype.h"
#include "data_struct.h"

int func_level=0;
Funptr tempfun;
Typeptr temptype;
Argptr temparg;
Idptr tempid;
int BLOCK_IS_FUNC_FLAG=0;

extern int line_no;
extern Funptr symtab,currfun;
extern int indent;
extern Type basic_types[4];
#define free(args) ;
//#undef getchar
%}
%union {
   YaccRetptr stackptr;
   Typeptr typeptr;	
   Varptr  varptr;
    Idptr idptr;
    Constptr constptr;
   void *voidptr;
   Argptr argptr;
   Typecheckptr chkptr;
};
%token <stackptr> AND ARRAY ASSIGNMENT CASE CHARACTER_STRING COLON COMMA 
%token <stackptr> CONST DIGSEQ DIV DO DOT DOTDOT DOWNTO ELSE END EQUAL 
%token <stackptr> EXTERNAL FOR FORWARD FUNCTION GE GOTO GT IDENTIFIER IF IN 
%token <stackptr> LABEL LBRAC LE LPAREN LT MINUS MOD NIL NOT NOTEQUAL OF OR 
%token <stackptr> OTHERWISE PACKED _BEGIN _FILE PLUS PROCEDURE PROGRAM RBRAC
%token <stackptr> REALNUMBER RECORD REPEAT RPAREN SEMICOLON SET SLASH STAR 
%token <stackptr> STARSTAR THEN TO TYPE UNTIL UPARROW VAR WHILE WITH NEW DELETE
%token <stackptr> TRUE FALSE

%type <stackptr> mulop relop identifier semicolon comma
%type <stackptr> sign non_string  unsigned_integer
%type <stackptr> unsigned_real domain_type direction 

%type <stackptr> file program  program_heading block 
%type <stackptr> module label_declaration_part label_list label
%type <stackptr> procedure_and_function_declaration_part
%type <stackptr> proc_or_func_declaration_list  proc_or_func_declaration
%type <stackptr> procedure_declaration procedure_heading directive
%type <stackptr> procedure_identification
%type <stackptr> procedure_block function_declaration function_heading
%type <stackptr>  function_block

%type <stackptr> statement_part compound_statement  statement_sequence
%type <stackptr> goto_statement case_statement 
%type <stackptr> case_list_element_list  case_list_element otherwisepart
%type <stackptr> record_variable_list addop 

%type <chkptr>  actual_parameter control_variable case_index
%type <chkptr>  variable_access indexed_variable 
%type <chkptr> index_expression_list index_expression field_designator
%type <chkptr> boolean_expression expression initial_value final_value
%type <chkptr> simple_expression term factor exponentiation primary
%type <chkptr> function_designator set_constructor actual_parameter_list 
%type <chkptr> member_designator_list member_designator params 

%type <voidptr> assignment_statement 
%type <voidptr> statement  
%type <voidptr>  non_labeled_statement
%type <voidptr> repeat_statement while_statement 
%type <voidptr> for_statement 
%type <voidptr> with_statement 
%type <voidptr> if_statement 
%type <voidptr> procedure_statement 

%type <constptr>  constant_list constant_definition case_constant 
%type <constptr> case_constant_list 
%type <constptr> const_expression const_simple_expression const_term
%type <constptr> const_factor const_exponentiation const_primary constant
%type <constptr> unsigned_constant  unsigned_number constant_definition_part 

%type <idptr>  identifier_list

%type <typeptr> type_definition_list type_definition
%type <typeptr> type_denoter  new_ordinal_type enumerated_type
%type <typeptr> subrange_type new_structured_type  structured_type 
%type <typeptr>  array_type  ordinal_type new_pointer_type record_type 
%type <typeptr> component_type
%type <typeptr> type_definition_part  new_type
%type <typeptr> variant_part variant_selector variant_list variant
%type <typeptr> tag_field tag_type
%type <typeptr> set_type base_type file_type 
%type <typeptr>	index_list index_type  result_type

%type <varptr>  record_section_list record_section 
%type <varptr> variable_declaration variable_declaration_list

%type <argptr> formal_parameter_list formal_parameter_section_list
%type <argptr> formal_parameter_section value_parameter_specification
%type <argptr> variable_parameter_specification 
%type <argptr> procedural_parameter_specification
%type <argptr> functional_parameter_specification 
%%
file : 
	program
		{ printf("\n ----------------HURRAY------------\n"); 
		  SymtabTraverseFuncTree(symtab);
		  Print("\n");
		  exit(0);	
		}
 	| module
 	;

program : 
	program_heading  semicolon
 		{ printf("\n--------program head-----------"); } 
	block DOT
		{ printf("\n program head block . ");
		}
 	| block DOT
		{ printf("\n block  . ");
		}
 	;

program_heading : 
	PROGRAM identifier 
		{ 
		}
 	| PROGRAM identifier LPAREN identifier_list RPAREN  
		{  free($1); free($3); free($5);
		 SymtabPrintIdlist($4);
		}
 	;

identifier_list : 
	  identifier_list comma identifier
		{ Idptr temp;
		   printf("\n id_list");
		   temp=SymtabCreateNewId($3->lexeme);	
		   $$=SymtabAppendToIdlist($1,temp);	
		}
	 | identifier
		{ //printf("\n id");
		   $$=SymtabCreateNewId($1->lexeme);	
		}
 	;

block : 
	 label_declaration_part 
		{ printf("\n----label-decl-----------------");
		}
	 constant_definition_part  
		{ printf("\n-------const_def----------"); 
		}
	 type_definition_part       
		{ printf("\n------type-def-------------");
		}
	 variable_declaration_part  
		{ printf("\n---------var-def-----------");
		 printf("\n ===================definations over ============");
		getchar();
		  PrintAllDeclarations();
		}
	 procedure_and_function_declaration_part 
		{ 
		 BLOCK_IS_FUNC_FLAG=1;
		}
	 statement_part
		{ 
		  printf("\n block");
		  printf("\n*************************************************");
		} 
	
 	;

module : 
	 constant_definition_part
	 type_definition_part
	 variable_declaration_part
	 procedure_and_function_declaration_part
 ;

label_declaration_part : 
	LABEL label_list semicolon
		{ printf("\n label label_list ; ");
		}
 	|
		{ printf("\n empty label decl ");
		}
 	;

label_list : 
	   label_list comma label
		{ printf("\n label_list , label");
		}
	 | label
		{ printf("\n label");
		}
 	;

label : 
	DIGSEQ {$$=$1;}
 	;

constant_definition_part : 
	CONST 	constant_list
		{ printf("\n const const_list ");
		 //PrintConstlist();
		}
	 |
		{ printf("\n empty const list");
		//PrintConstlist();
		}
	 ;

constant_list : 
	constant_list constant_definition
		{ printf("\n const_list const_def");
		}
	 | constant_definition
		{ printf("\n const_def");
		}
 	;

constant_definition : 
	identifier EQUAL const_expression semicolon
		{ printf("\n id = cexpr ;");
		 if($3!=NULL)
		  { SymtabInsertConst($1->lexeme,$3); 
		    free($2); free($1); free($4);
		  }
		 else 
		   printf("\n Not inserting constaant def due to $3=NULL");
		}
 	;


const_expression : 
	const_simple_expression
		{ printf("\n const_simple_expr");
		 $$=$1;	
		}
	 | const_simple_expression relop const_simple_expression
             {printf("\nconst_simple_expression relop const_simple_expression");
		$$=SymtabCreateNewConst(CONST_INT,"0");
		if($1->const_type==CONST_CHAR || $3->const_type==CONST_CHAR)
		  {   
		    error(INVALID_STRING_OPR);
		       free($$); $$=NULL;
		    }
		else{
  		  switch($2->type) {
		     case EQUAL: $$->value=($1->value)==($3->value); break;
		     case NOTEQUAL: $$->value=($1->value)!=($3->value); break;
		     case GT: $$->value=($1->value)>($3->value); break;
		     case LT: $$->value=($1->value)<($3->value); break;
		     case LE: $$->value=($1->value)<=($3->value); break;
		     case GE: $$->value=($1->value)>=($3->value); break;
		  // the IN case is to be handled
		   } 
		 }
		free($1); free($3); free($2);
	      }	
 	;

const_simple_expression : 
	const_term
		{ printf("\n const_term");
		 $$=$1;	
		}
	 | const_simple_expression addop const_term
	   { printf("\n const_simple_expr addop const_term");
		$$=(Constptr)malloc(sizeof(Constant));
		if($1->const_type==CONST_CHAR || $3->const_type==CONST_CHAR)
		  {  error(INVALID_STRING_OPR);
		    free($$); 
		    $$=NULL;
		  } 
		else {
		  if($1->const_type==CONST_INT && $3->const_type==CONST_INT)
	 		$$->const_type=CONST_INT;
	          else if($1->const_type==CONST_REAL ||
			 $3->const_type==CONST_REAL)
				$$->const_type=CONST_REAL;
		   $$->nxt=NULL;
		  switch($2->type) {
			case PLUS: $$->value=$1->value+$3->value;break;
			case MINUS: $$->value=$1->value-$3->value;break;
			case OR: $$->value=(int)$1->value|(int) $3->value;break;
		   }
		}
	     free($1); free($3);	free($2);
	   }
	 ;

const_term : 
	const_factor
		{ printf("\n const_factor");
		 $$=$1;	
		}
	 | const_term mulop const_factor
	   { printf("\n const_term mulop const_factor");
		$$=(Constptr)malloc(sizeof(Constant));
		if($1->const_type==CONST_CHAR || $3->const_type==CONST_CHAR)
		  {  error(INVALID_STRING_OPR);
		    free($$); 
		    $$=NULL;
		  } 
		else {
		  if($1->const_type==CONST_INT && $3->const_type==CONST_INT)
	 		$$->const_type=CONST_INT;
	          else if($1->const_type==CONST_REAL ||
			 $3->const_type==CONST_REAL)
				$$->const_type=CONST_REAL;
		   $$->nxt=NULL;
		  switch($2->type) {
			case STAR: $$->value=$1->value*$3->value;break;
			case SLASH: $$->value=$1->value/$3->value;break;
			case DIV: 
			    (int)$$->value=$1->value/ $3->value;break;
			case MOD: 
			    $$->value=(int)$1->value%(int)$3->value;break;
			case AND: 
			    $$->value=(int)$1->value &(int) $3->value;break;
		   }
		}
	     free($1); free($3);	free($2);
	 }
 	;

const_factor : 
	sign const_factor
		{ printf("\n sign const_factor");
		 if($2->const_type==CONST_CHAR) $$=NULL;
		 else {
			$$=(Constptr)malloc(sizeof(Constant));
			if(strcmp($1->lexeme,"-")==0) 
				$$->value=-$2->value;
			else $$->value=$2->value;
			$$->nxt=NULL;
		  }
		   free($2); free($1);
		}
	 | const_exponentiation
		{ printf("\n const_exponentiation");
		 $$=$1;	
		}
 	;

const_exponentiation : 
	const_primary
		{ printf("\n const_primary");
		 $$=$1;
		}
	 | const_primary STARSTAR const_exponentiation
		{ printf("\n const_prim ** const exponentin");
		  if($1->const_type=CONST_CHAR || $3->const_type==CONST_CHAR)
		  {  error(INVALID_STRING_OPR);
		     $$=NULL;
		    }
		    else{
		      $$=(Constptr)malloc(sizeof(Constant));
		      $$->value=pwr($1->value,$3->value);
		      $$->nxt=NULL;
		    }
		 free($1); free($2); free($3);
		}
 	;

const_primary : 
	identifier
		{ //printf("\n id");
		$$=SymtabCreateNewConst(CONST_ID,$1->lexeme);
		}
	 | LPAREN const_expression RPAREN
		{ 
		 $$=$2;printf("\n (const_expr");
		}
	 | unsigned_constant
		{ printf("\n unsinged_const");
		 $$=$1;
		}
	 | NOT const_primary
		{ $2->value=~(int)$2->value;
                  $$=$2;
		  printf("\n ! const_primary");
		}
 	;

constant : 		// note: this rule is never used in defining const_expr
			// it is used only for enum_type
	non_string
		{ printf("\n non_string");
		  if($1->type==DIGSEQ) 
			$$=SymtabCreateNewConst(CONST_INT,$1->lexeme);
		  else if($1->type==REALNUMBER)
			$$=SymtabCreateNewConst(CONST_REAL,$1->lexeme);
		  else if($1->type==IDENTIFIER) 
			$$=SymtabCreateNewConst(CONST_ID,$1->lexeme);
		}
	 | sign non_string
		{ 
		  if($2->type==DIGSEQ) {
			$$=SymtabCreateNewConst(CONST_INT,$2->lexeme);
			if($1->type==MINUS)
				$$->value=-$$->value;
		  }
		  else if($2->type==REALNUMBER){
			$$=SymtabCreateNewConst(CONST_REAL,$2->lexeme);
			if($1->type==MINUS)
				$$->value=-$$->value;
		  }	
		  else if($2->type==IDENTIFIER) 
			{  $$=SymtabCreateNewConst(CONST_ID,$2->lexeme);
			   if($1->type==MINUS)
				if($$) $$->value=-$$->value;
			}
		   printf("\n sign non_string");
		}
	 | CHARACTER_STRING
		{ printf("\n char_string");
		  $$=SymtabCreateNewConst(CONST_CHAR,$1->lexeme);
		}
 	;

sign : PLUS	{$$=$1;}
 | MINUS	{$$=$1;}
 ;

non_string :	// note: this rule is used only in constant: rule's defn 
   DIGSEQ	{$$=$1;}	
 | identifier	{$$=$1;}
 | REALNUMBER		{$$=$1;}
 ;

type_definition_part : 
	TYPE	type_definition_list
		{ printf("\n type type_def_list"); 
		    SymtabVerifyFwdRef();
		    SymtabPrintTypeList();
		}
	 |
		{ printf("\n empty type_def_list");
		}
	 ;

type_definition_list : 
	type_definition_list type_definition
		{ printf("\n type_def_list type_def"); 
		}
	 | type_definition
		{
		 printf("\n type_def");
		}
	 ;

type_definition : 
	identifier EQUAL type_denoter semicolon  //typeptr
		{ printf("\n id %s= type_denoter ;",$1->lexeme);
		   if($3!=NULL)
		   { if(SymtabIsNameDefined($1->lexeme))
			error(DUPLICATE_DECLARATION);
		     else{	
		      $3->typename=(char*)malloc(strlen($1->lexeme)+1);
		      strcpy($3->typename,$1->lexeme);
		      SymtabInsertType($3);
		     }	
		   }
		    else printf("\n Not inserting type due to error in defn");	
		}
	 ;

type_denoter : 				//typeptr
	  new_type
		{ printf("\n new type ");
		  $$ = $1;
		}
	| identifier
		{ //printf("\n id");
		  Typeptr temp;
		  temp=SymtabIsTypePresent($1->lexeme);
		  if(temp!=NULL) 
		  {  $$=(Typeptr)malloc(sizeof(Type));
		      *$$=*temp; 
		     $$->nxt=NULL;
		   }
		   else
		   {  error(INVALID_TYPEDEF); 
			$$=NULL;
		    }
		}
	 ;

new_type : 			//typeptr
	new_ordinal_type
		{ printf("\n new_ordinal_type");
		  $$=$1;
		}
	 | new_structured_type
		{ printf("\n new_structured_type");
		 $$=$1;
		}
	 | new_pointer_type
		{ printf("\n new_pointer_type");
		 $$=$1;
		}
	 ;

new_ordinal_type : 	//typeptr
	enumerated_type
		{ printf("\n enum_type");
		   $$=$1;	
		}
	 | subrange_type
		{ printf("\n subrange_type");
		 $$=$1;
		}
	 ;

enumerated_type : 		//typeptr
	LPAREN identifier_list RPAREN
		{ printf("\n (id_list)");
		  $$=SymtabCreateNewType(ENUM_TYPE,$2);
		  free($1); free($3);
		}
 	;

subrange_type :  //typeptr
	constant DOTDOT constant
		{ printf("\n const..const");
		  $$=SymtabCreateNewType(SUBRANGE_TYPE,$1,$3);
		  free($2);
		}
	 ;

new_structured_type : 	//typeptr
	structured_type
		{ printf("\n structured_type");
		 $$=$1;
		}
	 | PACKED structured_type
		{ printf("\n packed structured_type");
		$$=$2;
		}
		
	 ;

structured_type : 	//typeptr
	array_type
		{ printf("\n array_type");
		  $$=$1;
		}
	 | record_type
		{ printf("\n record_type");
		$$=$1;
		}
	 | set_type
		{ printf("\n set_type");
		$$=$1;
		}
	 | file_type
		{ printf("\n file_type");
		$$=$1;
		}
	 ;

array_type : 		//typeptr
	ARRAY LBRAC index_list RBRAC OF component_type
		{ printf("\n array[index_list] of compo_type");
		  if($3 && $6 ) 
			$$=SymtabCreateNewType(ARRAY_TYPE,$3,$6);
		  else 
			$$=NULL; 
		 free($1); free($2); free($4); free($5);
		}
	 ;

index_list : 	//typeptr
	index_list comma index_type
		{ printf("\n index_list , index_type");
		temptype=$1;
		  if(temptype!=NULL)
		  {
	        	while(temptype->nxt!=NULL) 
				temptype=temptype->nxt;
			temptype->nxt=$3;
			$$=$1;
		  } else 
			$$=$3;
		}
	 | index_type
		{ 
		  printf("\n index_type");
  		   $$=$1;
		}

	 ;

index_type : 			//typeptr
	ordinal_type 
		{ printf("\n ordinal_type");
		 $$=$1;  
		}
	;

ordinal_type : 			//typeptr
	new_ordinal_type
		{ printf("\n new_ordinal_type");
		 $$=$1;
		}
	 | identifier
		{ Typeptr temp;  // this id should be prev_defined ordinal_type
			//	   printf("\n----id= %s ---",$1->lexeme);
			//	  SymtabPrintTypeList();
		  temp=SymtabIsTypePresent($1->lexeme);
		  if(temp!=NULL)
		  {    if(SymtabIsOrdinalType(temp->type_type))
			  $$=SymtabCreateNewType(EXISTING,temp);
		        else{
			  error(NON_ORDINAL_TYPE);	
			  $$=NULL;
			}
		   }
                   else {
			error(INVALID_TYPEDEF);
			$$=NULL;
		   }
		 }
	 ;

component_type : 		//typeptr
	type_denoter 
		{ printf("\n type_denoter");
		  $$=$1;
		}
	;

record_type : 			//typeptr
	RECORD record_section_list END
		{
		  printf("\n record record_section_list end");
		 if($2)
		  $$=SymtabCreateNewType(RECORD_TYPE,1,$2);
		 else 
		   $$=NULL;
		SymtabPrintVarlist($2);
 		}	
 	|  RECORD record_section_list semicolon	variant_part END
		{
		  printf("\n record record_section_list;variant_part end");
		if($2)
		  $$=SymtabCreateNewType(RECORD_TYPE,2,$2,$4);
		else 
		  $$=NULL;
		SymtabPrintVarlist($2);
		}
	| RECORD  variant_part 	 END
		{ 
		  printf("\n record variant_part end");
		 if($2)
		   $$=SymtabCreateNewType(RECORD_TYPE,3,$2);
		 else 
		   $$=NULL;
		}
	 ;


record_section_list : 			//returns varptr
	record_section_list semicolon record_section
		{ 
		 $$=SymtabAppendToVarlist($1,$3);
		printf("\n record_section_list, record_section");
		}
	 | record_section
		{ printf("\n record_section");
		  $$=$1;
		}
	 ;

record_section : 			//returns varptr
	identifier_list COLON type_denoter
	    { printf("\n id_list : type_denoter");
	      if($3 && $1)	
	      {	  Idptr tempid; 
		  Varptr tempvar,head=NULL;
	          tempid=$1;
		  while(tempid!=NULL)
		  {  tempvar=SymtabCreateNewVar(tempid->idname,$3);
		     head=SymtabAppendToVarlist(head,tempvar);
		     tempid=tempid->nxt;	
		  }
		$$=head;
	       }
		else 
		{ printf("\n p2c: not inserting varlist in record defdue to ");
		  if($1==NULL) printf("$1");
		  if($3==NULL) printf(" and $3 ");
			$$=NULL;
		}
				
	    }
	 ;

variant_part : 		
	CASE variant_selector OF variant_list semicolon
		{ printf("\n case var_selectror of var_list ;");
		 printf("\n p2c: variant records not suported yet ");
		 exit(0);
		}
	 | CASE variant_selector OF variant_list
		{ printf("\n case var_selector of var_list");
		 printf("\n p2c: variant records not suported yet ");
		 exit(0);
		}
	 |
		{ printf("\n empty variant_part");
		 printf("\n p2c:variant records  not suported yet ");
		 exit(0);
		} 
// is above rule really needed? 
		
 	;

variant_selector : 
	tag_field COLON tag_type
		{ printf("\n tag_field : tag_type");
		}
	 | tag_type
		{ printf("\n tag_type");
		}
 ;

variant_list : 
	variant_list semicolon variant
		{ printf("\n variant_list ; variant");
		}
	 | variant
		{ printf("\n variant");
		}
	 ;

variant : 
	case_constant_list COLON LPAREN record_section_list RPAREN
		{ printf("\n case_const_list : (record_section_list) ");
		}
	 | case_constant_list COLON LPAREN record_section_list semicolon
	  variant_part RPAREN
		{ printf("\n case_const_list :\
			( record_section_list ;variant_part) ");
		}	
	 | case_constant_list COLON LPAREN variant_part RPAREN
		{ printf("\n case_const_list : ( variant_part ) ");
		}
	 ;

case_constant_list : 
	case_constant_list comma case_constant
		{ Constptr ptr;
		printf("\n case_const_list , case_const");
		if($1==NULL) $1=$3;
		else{
			ptr=$1;
			while(ptr->nxt) ptr=ptr->nxt;
			ptr->nxt=$3;
		}
		if($1->const_type==$3->const_type)
			$$=$1;		
		else $$=NULL;
		}
	 | case_constant
		{ printf("\n case_const");
		 $$=$1;
		}
	 ;

case_constant : 
	constant
		{ printf("\n const");
		 $$=$1;
		}
	 | constant DOTDOT constant
		{ printf("\n const..const");
		  $$=MakeConstList($1,$3);
		}
	 ;

tag_field : 
	identifier 
		{ //printf("\n id");
		}
	;

tag_type : 
	identifier 
		{ //printf("\n id");
		}
	;

set_type : 
	SET  OF base_type
		{ printf("\n SET of base_type");
		  if($3!=NULL) 
			$$=SymtabCreateNewType(SET_TYPE,$3);
		  else $$=NULL;
		}
 	;

base_type : 
	ordinal_type 
		{ printf("\n ordinal_type");
		  $$=$1;
		}
	;

file_type : 
	_FILE OF component_type
		{ printf("\n FILE OF compo_type");
		if($2!=NULL)
			$$=SymtabCreateNewType(FILE_TYPE,$3);
		else $$=NULL;
		}
	 ;

new_pointer_type : 
	UPARROW domain_type
		{ Typeptr temp;
		printf("\n ^domain_type");
		if(temp=SymtabIsTypePresent($2->lexeme))
			$$=SymtabCreateNewType(POINTER_TYPE,temp,0);
		 else 
			$$=SymtabCreateNewType(POINTER_TYPE,NULL,$2->lexeme);	
		}
	 ;

domain_type : 
	identifier 
		{ //printf("\n id");
		$$=$1;
		}
	;

variable_declaration_part : 
	VAR variable_declaration_list semicolon
		{ printf("\n VAR var_decl_list ;");
		  SymtabAddVarDecllist($2);
		  printf("\n current funcitons varlist");
		  SymtabPrintVarlist(currfun->varlist);	
		}
	 |
		{ printf("\n empty var_decl_part");
		}
 	;

variable_declaration_list :
	variable_declaration_list semicolon variable_declaration
		{ printf("\n var_decl_list ; var_decl");
		 $$=SymtabAppendToVarlist($1,$3);
		}
	| variable_declaration
		{ printf("\n var_decl");
		 $$=$1;
		}
 	;

variable_declaration : 
	identifier_list COLON type_denoter
	    { printf("\n id_list : type_denoter");
	      if($3 && $1)	
	      {	  Idptr tempid; 
		  Varptr tempvar,head=NULL;
	          tempid=$1;
		  while(tempid!=NULL)
		  {  tempvar=SymtabCreateNewVar(tempid->idname,$3);
		     if(SymtabIsNameDefined(tempid->idname))
			error(DUPLICATE_DECLARATION);
		     head=SymtabAppendToVarlist(head,tempvar);
		     tempid=tempid->nxt;	
		  }
		$$=head;
	       }
		else 
		{ printf("\n p2c: not inserting varlist in record defdue to ");
		  if($1==NULL) printf("$1");
		  if($3==NULL) printf(" and $3 ");
			$$=NULL;
		}
				
	    }
	 ;

procedure_and_function_declaration_part :
	  proc_or_func_declaration_list semicolon
		{ printf("\n proc_and_func decl ; ");
		 printf("\n------------proc adn funcdecl -------------------");
		}
	 |
		{ printf("\n empty proc_or_func decl_list");
		}
 ;

proc_or_func_declaration_list :
	 proc_or_func_declaration_list semicolon proc_or_func_declaration
		{ printf("\n proc_or_func_decl ; proc_func_decl");
		}
	 | proc_or_func_declaration
		{ printf("\n proc_or_func decl");
		}
	 ;

proc_or_func_declaration : 
	procedure_declaration
		{ printf("\n proc_decl");
		 printf("\n------------proc decl -------------------");
		    PrintConstUndef();
		   func_level--;
		   SymtabDecrCurrFuncPtr();
		}
	 | function_declaration
		{ printf("\n func_decl");
		 printf("\n------------func decl -------------------");
		    PrintConstUndef();
		  func_level--;	
		   SymtabDecrCurrFuncPtr();
		}
	 ;

procedure_declaration : 
	procedure_heading semicolon directive
		{ printf("\n proc_heading ; directive");
		  
		}
	 | procedure_heading semicolon procedure_block
		{ printf("\n proc_head ; proc_block");
		}
	 ;

procedure_heading : 
	procedure_identification
		{ printf("\n proc_id");
		}
	 | procedure_identification formal_parameter_list
		{ printf("\n proc_id formal_param_list");
		  SymtabAddArgDecllist($2);
		  SymtabPrintArglist();
		}
	 ;
procedure_identification :
	PROCEDURE 
		{ 
    	          func_level++;
		}
	identifier 
		{ printf("\n PROCEDRE id");
		  printf("\n before procinsert procname=%s",$3->lexeme);
		  SymtabInsertProcedure($3->lexeme);
		}
	;

directive : 
	FORWARD
	 | EXTERNAL
 	;

formal_parameter_list :
	LPAREN formal_parameter_section_list RPAREN 
		{ printf("\n ( formal_param_section_list) ");
		$$=$2;
		}
	;
	
formal_parameter_section_list : 
	formal_parameter_section_list semicolon formal_parameter_section
		{ printf("\n formal_param_section_list ; formal_param_section");
		 $$=SymtabAppendToArglist($1,$3);
		}
	 | formal_parameter_section
		{ printf("\n formal_param_section");
		$$=$1;
		}
 	;

formal_parameter_section : 
	value_parameter_specification
		{ printf("\n value_param");
		 $$=$1;
		}
	 | variable_parameter_specification
		{ printf("\n var parameter");
		 $$=$1;
		}
	 | procedural_parameter_specification
		{ printf("\n procedure_param");
		$$=NULL;
		 printf("\n p2c: procedure parametrs not suported yet ");
		 exit(0);
		}
	 | functional_parameter_specification
		{ printf("\n func_param");
		 printf("\n p2c: function parametrs not suported yet ");
		 exit(0);
		}
	 ;

value_parameter_specification : 
	identifier_list COLON identifier
		{ printf("\n id_list : id ");
	          if($1)
	       	  {  Idptr tempid;Typeptr tmp;
        	     Argptr temparg,head=NULL;
                     tempid=$1;
		     tmp=SymtabIsTypePresent($3->lexeme);
		     if(tmp)
 		     {
                       while(tempid!=NULL)
                       {    temparg=
	                     SymtabCreateNewArg(tempid->idname,VALUE_PARAM,tmp);
                           head=SymtabAppendToArglist(head,temparg);
                           tempid=tempid->nxt;
                       }
                       $$=head;
		      }
		      else 
		      { error(INVALID_TYPEDEF); 
		        $$=NULL;
		      }	
                  }
                  else
                  { 
		    printf("\n p2c:not inserting varlist in record \
						defdue to $1=NULL");
                        $$=NULL;
                   }
		}
 	;

variable_parameter_specification : 
	VAR identifier_list COLON identifier
		{ printf("\n VAR id_list : id ");
                  if($2)
                  {  Idptr tempid;Typeptr tmp;
                     Argptr temparg,head=NULL;
                     tempid=$2;
                     tmp=SymtabIsTypePresent($4->lexeme);
                     if(tmp)
                     {
                      while(tempid!=NULL)
                      {    temparg=
                             SymtabCreateNewArg(tempid->idname,VAR_PARAM,tmp);
                           head=SymtabAppendToArglist(head,temparg);
                           tempid=tempid->nxt;
                      }
                      $$=head;
                     }
                     else
                     { error(INVALID_TYPEDEF);
                       $$=NULL;
                     }
                  }
                  else
                  {
                    printf("\n p2c:not inserting varlist in record \
                                                defdue to $1=NULL");
                        $$=NULL;
                   }
                }

	 ;

procedural_parameter_specification : 
	procedure_heading 
		{ printf("\n proc_heading");
		}
	;

functional_parameter_specification : 
	function_heading
		{ printf("\n func_heading");
		}
	;


procedure_block : 
	block 
		{ printf("\n proc_block");
		}
	;

function_declaration : 
	function_heading semicolon directive
		{ printf("\n func_heading ; directive");
		}
	 | function_heading semicolon function_block
		{ printf("\n func_head ; func_block");
		}
	 ;

function_heading : 
	FUNCTION identifier COLON result_type
		{ printf("\n FUNCTION id : result_type");
		  func_level++;
		  SymtabInsertFunction($2->lexeme);
		  SymtabAddFuncRetType($4); // check that this is not null
		   PrintFwdDecl();
		}
	 | FUNCTION identifier 
		{
		  func_level++;
		  SymtabInsertFunction($2->lexeme);
		}
	formal_parameter_list COLON result_type
		{ printf("\n FUNCTION id formal_param_list : result_type");
		  SymtabAddArgDecllist($4);
		  SymtabPrintArglist();
		  SymtabAddFuncRetType($6); // check that this is not null
		 PrintFwdDecl();	
		}
	 ;

result_type : 
	identifier 
		{ //printf("\n id");
		  Typeptr temp;
		   temp=SymtabIsTypePresent($1->lexeme);
		 if(temp) 
			$$=temp;
		 else { $$=NULL;
			 error(INVALID_TYPEDEF);
		  }
		}
	;
function_block : 
	block 
		{ printf("\n func_block");
		}
	;

statement_part : 
	compound_statement 
		{ printf("\n compund_statement");
		}
	;

compound_statement : 
	_BEGIN { 
		 if(BLOCK_IS_FUNC_FLAG)
		  { PrintFuncHeader();}
		PrintOpenBrace();
		++indent;
		 if(BLOCK_IS_FUNC_FLAG)
		 { PrintFuncLocalVar();
		   BLOCK_IS_FUNC_FLAG=0;		
		  }
		} 
	statement_sequence
	END   {
		 printf("\n BEGIN stat_seq END ");
		--indent; if(indent==0) PrintFuncRetStat();
		PrintCloseBrace();	
		}
	;

statement_sequence :
	statement_sequence semicolon statement
		{ printf("\n state_seq ; stat ");
		}
	 | statement
		{ printf("\n stat");
		   printf("\n--------------statment-------------------------");
		}
 	;

statement : 
	label COLON non_labeled_statement
		{ printf("\n label : non_label_open_stat");
		}
	 | non_labeled_statement
		{ printf("\n non_label_open_stat");
		}
	 ;


non_labeled_statement :
	assignment_statement
		{ printf("\n assignment stat");
		  $$=$1;
		}
	 | procedure_statement
		{ printf("\n procedure stat");
		}
	 | goto_statement
		{ printf("\n goto stat ");
		}
	 | compound_statement
		{ printf("\n compound stat");
		}
	 | case_statement
		{ printf("\n case stat");
		}
	 | repeat_statement
		{ printf("\n repeat stat");
		}
	 | with_statement
		{ printf("\n closed with stat ");
		}
	 | if_statement
		{ printf("\n closed if stat");
		}
	 | while_statement
		{ printf("\n closed while stat");
		}
	 | for_statement
		{ printf("\n closed_for_stat ");
		}
	 |
		{ printf("\n empty stat");
		}
	 ;


repeat_statement : 
	REPEAT { Print("\n");PrintIndent();Print("do{");++indent;
		}
	statement_sequence UNTIL
		{ Print("\n");--indent;PrintIndent();Print("}while");
		} 
	boolean_expression
		{ 
		Print("(");Print("!(");Print($6->string);Print("));");
		printf("\n REPEAT stat_seq UNTIL bool_expr ");
		}
	 ;


while_statement : 
	WHILE boolean_expression DO 
	{ Print("\n"); PrintIndent();Print("while(");
	  Print($2->string);Print(")");indent++;	
	}
	statement
		{ printf("\n WHILE bool_expr DO closed_stat");
		indent--;
		}
	 ;

for_statement :
	 FOR control_variable ASSIGNMENT initial_value direction
	   final_value DO 
	{ int i;printf("\n FOR ctrl_var := init_value direction final_value DO");
	  Print("\n"); PrintIndent();
	  Print("for("); Print($2->string);Print("=");Print($4->string);
	  Print(";"); Print($2->string);
	  if((mystrcmp($5->lexeme,"to"))==0)
	  	Print("<="); 
	  else  Print(">=");
	  Print($6->string); Print(";"); Print($2->string);
	  if((mystrcmp($5->lexeme,"to"))==0) 
		Print("++");
	  else Print("--");
	  Print(")"); ++indent;
	}	
	statement
	{--indent;}
	 ;


with_statement : 
	WITH record_variable_list DO statement
		{ printf("\n WITH record_var_list DO  closed_stat");
		}
	 ;

if_statement :  
	if_part else_part
	;
if_part:  
	IF boolean_expression THEN 
		{ Print("\n");PrintIndent(); Print("if(");  
		/*printf("after if("); getchar(); getchar();*/
		Print($2->string); Print(")"); indent++;
		}
	statement { indent--;}
	;
else_part:  
	ELSE 
		{ Print("\n"); PrintIndent(); Print("else");	 indent++;
		}
	statement
		{ printf("\n IF bool_expr THEN closed_stat ELSE closed_stat");
		indent--;
		}
	 |
	;

assignment_statement : 
	variable_access ASSIGNMENT expression
		{ 
		printf("\n var_acess := expr "); getchar();
  if(($1->type->type_type==$3->type->type_type)||
    (($1->type->type_type==SUBRANGE_TYPE||$1->type->type_type==INTEGER_TYPE) &&
     ($3->type->type_type==INTEGER_TYPE ||$3->type->type_type==SUBRANGE_TYPE)))
		  {
			if($1->type->type_type==INTEGER_TYPE||
			   $1->type->type_type==REAL_TYPE||
			   $1->type->type_type==BOOLEAN_TYPE||
			   $1->type->type_type==SUBRANGE_TYPE||
			   $1->type->type_type==POINTER_TYPE||
			   ($1->type->type_type==RECORD_TYPE && 
			mystrcmp($1->type->typename,$3->type->typename)==0))
			{ Print("\n");PrintIndent();
			  Print($1->string); Print("=");
			  Print($3->string); Print(";");
			}
			else tperror(ASSIGNMENT_STAT_WRONG_TYPE);
		  }
		  else tperror(ASSIGNMENT_STAT_TYPE_MISMATCH);	
		}
	
	 ;

variable_access :
	 identifier
	   { //printf("\n id"); 
	      int currlevel,foundlevel,i,type,j;
	      char buf[128];	
              $$=(Typecheckptr)malloc(sizeof(Typecheck));$$->nxt=NULL;
	      $$->type=TpCheckGetTypePtr(
		 $1->lexeme,&currlevel,&foundlevel,&type,buf);
	     if($$->type)
	     {	
		if(foundlevel!=0 && type!=6){ // i.e. not a global var
						// and not enum value
		  j=currlevel-foundlevel;
		  i=(currlevel-foundlevel)*8+(type==2)*3;
		  $$->string=(char *)malloc(strlen($1->lexeme)+1+i);
		  strcpy($$->string,""); // for strcat to be useful
		  if(type==2 && $$->type->type_type!=ARRAY_TYPE) 
			strcat($$->string,"(*");
		  while(j--)
		    strcat($$->string,"SCP->");	
		  if(type==1) 
			{   if(currlevel==foundlevel) strcat($$->string,"W.");
			strcat($$->string,$1->lexeme);}
		  else if(type==2 || type==3 || type==4) 
			strcat($$->string,$1->lexeme);
		  else if(type==5) 
			strcat($$->string,buf);
		  if(type==2 && $$->type->type_type!=ARRAY_TYPE) 
			strcat($$->string,")");	
		}
		else { 
			  $$->string=(char *)malloc(strlen($1->lexeme)+1);
			  strcpy($$->string,$1->lexeme);
		}
	     }
	     else tperror(DECL_NOT_FOUND,$1->lexeme);
	   }
	 | indexed_variable
		{ printf("\n indexed var ");
		 $$=$1;
		}
	 | field_designator
		{ printf("\n field designator ");
		$$=$1;
		}
	 | variable_access UPARROW
		{ printf("\n var_access ^ ");
		 if($1->type->type_type!=POINTER_TYPE)
			tperror(TYPE_IS_NOT_POINTER,$1->string);	
		 $$=(Typecheckptr)malloc(sizeof(Typecheck)); $$->nxt=NULL;
		 $$->type=$1->type->typeptr;
		 $$->string=(char *)malloc(strlen($1->string)+5);
		 strcpy($$->string,"(*");
		 strcat($$->string,$1->string);
		 strcat($$->string,")");
		}
	 ;

indexed_variable :
	variable_access LBRAC index_expression_list RBRAC
		{ 
		  Typecheckptr temp;int count=0,strlencount=0;
		  char *chptr,buf[120];	
		printf("\n var_acess [ index_expr_list ] "); getchar();
		  if($1->type->type_type!=ARRAY_TYPE)
			tperror(TYPE_IS_NOT_ARRAY,$1->string);	
		  temp=$3;
		  while(temp) 
		  {     
			++count; 
			strlencount+=strlen(temp->string)+3+32;
			//+32 for adding the string for substracting lower bound
			if(!SymtabIsOrdinalType(temp->type->type_type)) 
		  	    tperror(ARRAY_SUBSCR_NOT_INTEGER); 	  
			temp=temp->nxt; 
		  }
		  if(count!=$1->type->no_of_dimn)
			tperror(ARRAY_WRONG_NO_OF_INDEX);	
		  $$=(Typecheckptr)malloc(sizeof(Typecheck));	$$->nxt=NULL;
		  $$->type=$1->type->elemtype;
		  $$->string=(char *)malloc(strlencount+1);
		  strcpy($$->string,$1->string);
		  temp=$3; count=0;
		  while(temp)
		  { 
		    strcat($$->string,"[(");
		    strcat($$->string,temp->string);		
		    strcat($$->string,")");	
		    TpCheckGetArrayLimitDiff($1->type,count,buf);
		    strcat($$->string,buf);	
		    strcat($$->string,"]");
			++count; 
		    temp=temp->nxt;
		  }
		}
	 ;

index_expression_list :
	index_expression_list comma index_expression
		{ 
		  Typecheckptr temp;
		  printf("\n index_expr_list , index_expr");
		  if($1==NULL) $1=$3;
		  else 
		  { temp=$1;
		    while(temp->nxt) 
			temp=temp->nxt;	
		    temp->nxt=$3; 
		 } 
		    $$=$1;
		}
	 | index_expression
		{ printf("\n index_expr");
		$$=$1;
		}
	 ;

index_expression :
	expression
		{ printf("\n expr");
		 $$=$1;
		}
	;

field_designator : 
	variable_access DOT identifier
	{ Typeptr temp;
	  printf("\n var_access . id ");
	  if($1->type->type_type!=RECORD_TYPE)
	 	tperror(TYPE_IS_NOT_RECORD);
	  temp=TpCheckIsRecField($1->type,$3->lexeme);
	  if(temp)
	  {  $$=(Typecheckptr)malloc(sizeof(Typecheck)); 
	     $$->nxt=NULL;
	     $$->type=temp;
	     $$->string=(char*)malloc(strlen($1->string)+strlen($3->lexeme)+3);
	     strcpy($$->string,$1->string);strcat($$->string,$2->lexeme);
	     strcat($$->string,$3->lexeme);			
	      printf("right here "); getchar(); getchar();	
	  } 
	  else 
		tperror(RECORD_FIELD_NOT_EXIST,$1->string,$3->lexeme);
	}
	 ;

procedure_statement : 
	identifier 	params
	 { //printf("\n id");
	   int currlevel,proclevel,i,no_of_arg,is_func; 
	   Argptr aptr;Typeptr tptr;
	   Typecheckptr temp; int count=0;
	  if(!TpCheckIsStdFunc($1->lexeme))
	 {
	   if(aptr=TpCheckIsProcInScope($1->lexeme,&currlevel,
			&proclevel,&no_of_arg,&is_func,&tptr))
	   {	Print("\n"); PrintIndent();Print($1->lexeme);Print("(");
		temp=$2;
		while(temp) { ++count; temp=temp->nxt;}
		if(count!=no_of_arg)
			tperror(PROC_WRONG_NO_OF_ARG);
		temp=$2;
		while(temp)
		{ if((mystrcmp(aptr->type->typename,temp->type->typename)==0)||
			(temp->type->type_type==SUBRANGE_TYPE 
			&& aptr->type->type_type==INTEGER_TYPE)||
			(temp->type->type_type==INTEGER_TYPE 
			&& aptr->type->type_type==SUBRANGE_TYPE))
		  {	
			  if(aptr->arg_type==VAR_PARAM && 
				aptr->type->type_type!=ARRAY_TYPE)
			    Print("&");
			  Print(temp->string);	 
			  if(temp->nxt) Print(",");
		   }
		  else tperror(PROC_WRONG_TYPE_ARG);		
		  aptr=aptr->nxt; temp=temp->nxt;
		}
		if(currlevel)
		{
			if(currlevel==proclevel-1)  // child called
			{	if(no_of_arg) Print(",");  
				Print("&W");Print(");");
			 }
			else{ 
			 if(proclevel>1){
			   i=currlevel-proclevel+1;
			   if(no_of_arg)	Print(",");
			   while(--i)
				Print("SCP->");
			   Print("SCP);");	
			  } else Print(");");	
			}
		}
	       else { Print(");");
		}
	    }
	   else tperror(FUNC_NOT_IN_SCOPE,$1->lexeme);	
	 } 
	 else PrintStdFuncCall($1->lexeme,$2,NO);
	 }
	 | identifier
	 { //printf("\n id");
	   int currlevel,proclevel,i;
	 if(!TpCheckIsStdFunc($1->lexeme))
	 {	
	   if(TpCheckIsProcInScope($1->lexeme,&currlevel,&proclevel))
	   {	Print("\n"); PrintIndent();Print($1->lexeme);
		if(currlevel){
			if(currlevel==proclevel-1)  // child called
				{ Print("("); Print("&W");Print(");");}
			else{ Print("(");
			  if(proclevel>1)
			 {
			 	  i=currlevel-proclevel+1; 
				   while(--i)
					Print("SCP->");
				   Print("SCP);");	
			  } else Print(");");
			}
		}
	       else { Print("();");
		}
	    }
	   else tperror(FUNC_NOT_IN_SCOPE,$1->lexeme);	
	 } else 
	  PrintStdFuncCall($1->lexeme,NULL,NO);
	 }
	 ;

params : 
	LPAREN actual_parameter_list RPAREN
		{ printf("\n ( act_param_list )");
		 $$=$2;
		}
	;

actual_parameter_list : 
	actual_parameter_list comma actual_parameter
		{ 
		  Typecheckptr temp;
		   printf("\n act_param_list , act_param");
		  if($1==NULL) $1=$3;
		  else 
		  { temp=$1;
		    while(temp->nxt) 
			temp=temp->nxt;	
		    temp->nxt=$3; 
		 } 
		    $$=$1;
		}
	 | actual_parameter
		{ printf("\n act_param");
		$$=$1;	$$->nxt=NULL;
		}
	 ;

/*
 * this forces you to check all this to be sure that only write and
 * writeln use the 2nd and 3rd forms, you really can't do it easily in
 * the grammar, especially since write and writeln aren't reserved
 */
actual_parameter :
	 expression
		{ printf("\n expr ");
		$$=$1;
		}
	 | expression COLON expression
		{ printf("\n expr : expr ");
		  printf("\n line:%d field widths not handled yet",line_no);
		  exit(0);	
		}
	 | expression COLON expression COLON expression
		{ printf("\n expr : expr : expr ");
		  printf("\n line:%d field widths not handled yet",line_no);
		  exit(0);	
		}
	 ;

goto_statement : 
	GOTO label
		{ printf("\n GOTO label ");
		   Print("\n");PrintIndent();Print("goto   x");
		   Print($2->lexeme);	Print(";");
		}
	 ;

case_statement :  header_part case_statement_part
	;
header_part:
	CASE case_index OF {
		Print("\n");PrintIndent();
		Print("switch(");Print($2->string);Print(")");
		PrintOpenBrace();indent++;
		}
	;
case_statement_part: case_list_element_list END
		{ printf("\n CASE case_index OF case_list_elem_list END ");
		 --indent;PrintCloseBrace();
		}
	 |  case_list_element_list SEMICOLON END
		{ printf("\n CASE case_index OF case_list_elem_list ; END ");
		 --indent;PrintCloseBrace();
		}
	 | case_list_element_list semicolon
	   otherwisepart 
		  {Print("\n");PrintIndent();Print("default:");indent++;}
		statement END
		{ printf("\n  case_list_elem_list ;otherwise_part stat END ");
		  	
		 --indent;PrintCloseBrace();
		}
	 ;

case_index : 
	expression 
		{ printf("\n expr ");
		 $$=$1;
		}
	;

case_list_element_list : 
	case_list_element_list semicolon case_list_element
		{ printf("\n case_list_elem_list ; case_list_elem ");
		}
	 | case_list_element
		{ printf("\n case_list_elem ");
		}
	 ;

case_list_element : 
	case_constant_list COLON 
		{ Constptr ptr; char buf[120];
		  ptr=$1;
		  while(ptr)
		  { Print("\n");PrintIndent(); Print("case ");
		    if(ptr->const_type==CONST_INT)
		    {	 sprintf(buf,"%d",(int)ptr->value);
			Print(buf); Print(":");
		    }
		    else 
		    { Print("'");Print(ptr->string);Print("':");
		    }
			ptr=ptr->nxt;
		   }
		indent++;
		}
	statement
		{ printf("\n case_const_list : stat ");
		indent--; Print("\n");PrintIndent();Print("break;");
		}
	 ;

otherwisepart : 
	OTHERWISE {$$=$1;}
	 | OTHERWISE COLON {$$=$1;}
	 ;

control_variable : 
	identifier 
	{   Typeptr temp;
		      int currlevel,foundlevel,i,j,type;
		char buf[120];
              $$=(Typecheckptr)malloc(sizeof(Typecheck)); $$->nxt=NULL;
	      $$->type=TpCheckGetTypePtr(
		$1->lexeme,&currlevel,&foundlevel,&type,buf);
	    if($$)
	   {
	      if($$->type->type_type==INTEGER_TYPE)
	     {	
		if(foundlevel!=0)		 // i.e. not a global var
		{
		  j=currlevel-foundlevel;
		  i=(currlevel-foundlevel)*8+(type==2)*3;
		  $$->string=(char *)malloc(strlen($1->lexeme)+1+i);
		  strcpy($$->string,""); // for strcat to be useful
		  if(type==2) strcat($$->string,"*(");
		  while(j--)
		    strcat($$->string,"SCP->");	
		  if(type==1) 
			{   if(currlevel==foundlevel) strcat($$->string,"W.");
			strcat($$->string,$1->lexeme);}
		  else if(type==2 || type==3 || type==4) 
			strcat($$->string,$1->lexeme);
		  else if(type==5) 
			strcat($$->string,buf);
		  if(type==2) strcat($$->string,")");	
		}
		else { 
			  $$->string=(char *)malloc(strlen($1->lexeme)+1);
			  strcpy($$->string,$1->lexeme);
		}
	     }		
	     else tperror(FOR_LOOP_WRONG_CTRL_VAR_TYPE);
	   } else tperror(DECL_NOT_FOUND,$1->lexeme);
/*	  temp=SymtabIsTypePresent($1->lexeme);
	   if(temp) 
		if(temp->type_type==INTEGER_TYPE)
			$$=$1;	
		else tperror(FOR_LOOP_WRONG_CTRL_VAR_TYPE);*/
	}
	;

initial_value :
	expression 
		{ printf("\n expr ");
		if($1->type->type_type==INTEGER_TYPE)
		  $$=$1;
		 else tperror(FOR_LOOP_VAR_INVALID_VALUE);
		}
	;

direction : 
	TO {$$=$1;}
	 | DOWNTO {$$=$1;}
	 ;

final_value : 
	expression 
		{ printf("\n expr ");
		if($1->type->type_type==INTEGER_TYPE ||
			$1->type->type_type==SUBRANGE_TYPE)
		  $$=$1;
		 else tperror(FOR_LOOP_VAR_INVALID_VALUE);
		}
	;

record_variable_list : 
	record_variable_list comma variable_access
		{ printf("\n record_var_list , var_access ");	
		}
	 | variable_access
		{ printf("\n var_access ");
		}
	 ;

boolean_expression :
	 expression 
		{ printf("\n expr "); getchar();
		  printf("\n --------------expr---------"); getchar();
		printf("\n expr string= %s", $1->string); getchar(); getchar();
		printf("\n expr type= %d",$1->type->type_type); getchar();
		if($1->type->type_type==BOOLEAN_TYPE)
		{  printf("yes.. boolean"); getchar();
			$$=$1;
		}
		else tperror(BOOLEAN_EXPR_WRONG_TYPE);
		}
	;

expression : 
	simple_expression
		{ printf("\n simple_expr ");
		$$=$1;
		}
	 | simple_expression relop simple_expression
	{  printf("\n simple_expr relop simple_expr ");
           if( (($1->type->type_type==INTEGER_TYPE ||
	        $1->type->type_type==REAL_TYPE 	||
	        $1->type->type_type==SUBRANGE_TYPE	) &&
	        ($3->type->type_type==INTEGER_TYPE ||
		 $3->type->type_type==REAL_TYPE	||
		 $3->type->type_type==SUBRANGE_TYPE)) ||
		($1->type->type_type==POINTER_TYPE && 
		 $3->type->type_type==POINTER_TYPE))
	    {
	      $$=(Typecheckptr)malloc(sizeof(Typecheck));
	      $$->nxt=NULL;
	      $$->type=basic_types+3;	
	      $$->string=
	      (char *)malloc(strlen($1->string)+strlen($3->string)+3);
	      strcpy($$->string,$1->string);
	      switch ($2->type)
		{ case EQUAL: strcat($$->string,"=="); break;
		  case NOTEQUAL: strcat($$->string,"!=");break;
		  case GT: case LT: case GE: case LE:
			strcat($$->string,$2->lexeme);
			break;
		}
		strcat($$->string,$3->string);
	    }
	    else tperror(COMPARISON_INVALID_OPERANDS);
	}
	 ;

simple_expression : 
	term
		{ printf("\n term ");
		$$=$1;
		}
	 | simple_expression addop term
		{ printf("\n simple_expr addop term ");
		$$=(Typecheckptr)malloc(sizeof(Typecheck)); $$->nxt=NULL;
		$$->string=
		(char *)malloc(strlen($1->string)+strlen($3->string)+3);
		strcpy($$->string,$1->string);
		switch($2->type){
		   case PLUS: 
		   case MINUS:
		       if( ($1->type->type_type==INTEGER_TYPE ||
			      $1->type->type_type==REAL_TYPE  ||
			    $1->type->type_type==SUBRANGE_TYPE) &&	
			    ($3->type->type_type==INTEGER_TYPE ||
			     $3->type->type_type==REAL_TYPE||
			    $3->type->type_type==SUBRANGE_TYPE))	
			strcat($$->string,$2->lexeme); 
			else tperror(ADD_OP_INVALID_OPERANDS);
			if($1->type->type_type==REAL_TYPE || 
			   $3->type->type_type==REAL_TYPE)
			  $$->type=basic_types+1;	
			else $$->type=basic_types;
			break;
		   case OR: 
			if($1->type->type_type!=BOOLEAN_TYPE||
			   $3->type->type_type!=BOOLEAN_TYPE)
			tperror(OR_INVALID_OPERANDS);	
			else strcat($$->string,"||");
			$$->type=basic_types+3;
			break;
		}
		strcat($$->string,$3->string);
		}
	 ;

term : 
	factor
		{ printf("\n factor ");
		$$=$1;	
		}
	 | term mulop factor
	   { printf("\n term mulop factor ");
		$$=(Typecheckptr)malloc(sizeof(Typecheck));$$->nxt=NULL;
		$$->string=
		(char *)malloc(strlen($1->string)+strlen($3->string)+3);
		strcpy($$->string,$1->string);
		switch($2->type){
		   case SLASH: 
		   case STAR:
		       if( ($1->type->type_type==INTEGER_TYPE ||
			      $1->type->type_type==REAL_TYPE || 	
			    $1->type->type_type==SUBRANGE_TYPE) &&	
			    ($3->type->type_type==INTEGER_TYPE ||
			     $3->type->type_type==REAL_TYPE||
			    $3->type->type_type==SUBRANGE_TYPE))	
			strcat($$->string,$2->lexeme); 
			else tperror(MUL_OP_INVALID_OPERANDS);
			if($1->type->type_type==REAL_TYPE || 
			   $3->type->type_type==REAL_TYPE)
			  $$->type=basic_types+1;	
			else $$->type=basic_types;
			break;
		   case DIV: 
			if($1->type->type_type!=INTEGER_TYPE||
			   $3->type->type_type!=INTEGER_TYPE)
			tperror(DIV_INVALID_OPERANDS);	
			else strcat($$->string,"/");
			$$->type=basic_types;
			break;
		   case MOD: 
			if($1->type->type_type!=INTEGER_TYPE||
			   $3->type->type_type!=INTEGER_TYPE)
			tperror(MOD_INVALID_OPERANDS);	
			else strcat($$->string,"/");
			$$->type=basic_types;
			break;
		   case AND: 
			if($1->type->type_type!=BOOLEAN_TYPE||
			   $3->type->type_type!=BOOLEAN_TYPE)
			tperror(AND_INVALID_OPERANDS);	
			else strcat($$->string,"&&");
			$$->type=basic_types+3;
			break;
		}
		strcat($$->string,$3->string);
    	}	
	 ;

factor : 
	sign factor
		{ printf("\n sign factor ");
		$$=(Typecheckptr)malloc(sizeof(Typecheck));$$->nxt=NULL;
		$$->string=(char*)malloc(strlen($2->string)+4);
		strcpy($$->string,$1->lexeme);
		strcat($$->string,$2->string);
		$$->type=$2->type;
		}
	 | exponentiation
		{ printf("\n exponentiation ");
		$$=$1;	
		}
	 ;

exponentiation : 
	primary
		{ printf("\n primary ");
		$$=$1;
		}
	 | primary STARSTAR exponentiation
	    {  printf("\n primary ** exponentioan ");
	       if( ($1->type->type_type==INTEGER_TYPE ||
		      $1->type->type_type==REAL_TYPE ) &&	
		    ($3->type->type_type==INTEGER_TYPE ||
		     $3->type->type_type==REAL_TYPE))	
	       {
			$$=(Typecheckptr)malloc(sizeof(Typecheck));$$->nxt=NULL;
			$$->string=
			(char *)malloc(strlen($1->string)+strlen($3->string)+8);
			strcpy($$->string,"pwr(");
			strcat($$->string,$1->string);
			strcat($$->string,",");
			strcat($$->string,$3->string);
			if($1->type->type_type==REAL_TYPE || 
			   $3->type->type_type==REAL_TYPE)
			  $$->type=basic_types+1;	
			else $$->type=basic_types;
	       }
		else	tperror(PWR_INVALID_OPERANDS);	
	    }
	 ;

primary : 
	variable_access
		{ printf("\n var_access ");
		$$=$1;
		}
	 | unsigned_constant
		{ char buf[120]; int len;
		  printf("\n unsinged const ");
		  $$=(Typecheckptr)malloc(sizeof(Typecheck)); $$->nxt=NULL;
		  if($1->const_type==CONST_INT){
			sprintf(buf,"%d",(int)$1->value);
			len=strlen(buf);
		   	$$->string=(char *)malloc(len+1);
		   	strcpy($$->string,buf);	
			$$->type=basic_types;
			}
		   else if($1->const_type==CONST_REAL){
			sprintf(buf,"%f",$1->value);
			len=strlen(buf);
		   	$$->string=(char *)malloc(len+1);
		   	strcpy($$->string,buf);	
			$$->type=basic_types+1;
		   }
		   else { len=strlen($1->string);
		   	$$->string=(char *)malloc(len+1);
		   	strcpy($$->string,$1->string);
			$$->type=basic_types+2;	
		   }
		}
	 | function_designator
		{ printf("\n func_designator has not been handeled yet");
		  printf("\n In line no %d ",line_no);$$=$1;
		 //exit(0);	
		}
	 | set_constructor
		{ printf("\n Set Constructor has not been handeled yet");
		  printf("\n In line no %d ",line_no);
		 exit(0);	
		}
	 | LPAREN expression RPAREN
		{ printf("\n (expr)");
		 $$=(Typecheckptr)malloc(sizeof(Typecheck));
	      $$->nxt=NULL;
		 $$->type=$2->type;
		 $$->string=(char *)malloc(strlen($2->string)+3);
		 strcpy($$->string,"("); strcat($$->string,$2->string);
		 strcat($$->string,")");	
		}
	 | NOT primary
		{ printf("\n !primary");
		   if($2->type->type_type==BOOLEAN_TYPE)
		   {
		 	$$=(Typecheckptr)malloc(sizeof(Typecheck)); 
			$$->nxt=NULL;
			 $$->string=(char *)malloc(strlen($2->string)+5);
			 strcpy($$->string,"!(");
			 strcat($$->string,$2->string);
			strcat($$->string,")");
			 $$->type=basic_types+3;
		  } 
			else 
			tperror(NOT_INVALID_OPERAND);
			
		}
	| TRUE
		{ $$=(Typecheckptr)malloc(sizeof(Typecheck));
		  $$->string=(char *)malloc(3);
		  strcpy($$->string,"1");
		  $$->type=basic_types+3;
		  $$->nxt=NULL;		
		}
	| FALSE
		{ $$=(Typecheckptr)malloc(sizeof(Typecheck));
		  $$->string=(char *)malloc(3);
		  strcpy($$->string,"0");
		  $$->type=basic_types+3;
		  $$->nxt=NULL;		
		}
	 | NIL
		{  printf("nil");
		$$=(Typecheckptr)malloc(sizeof(Typecheck));
		  $$->nxt=NULL;
		  $$->type=(Typeptr)malloc(sizeof(Type));
		  $$->type->type_type=POINTER_TYPE;
		  $$->string=(char *)malloc(6);
		  strcpy($$->string,"NULL");
		 $$->type->typeptr=NULL;
		}
	 ;

unsigned_constant : 
	unsigned_number
		{ printf("\n unsinged no ");
		$$=$1;
		}
	 | CHARACTER_STRING
		{ $$=SymtabCreateNewConst(CONST_CHAR,$1->lexeme);
		free($1);
		}
	 ;

unsigned_number : 
	unsigned_integer 
		{ printf("\n unsigned int ");
		   $$=SymtabCreateNewConst(CONST_INT,$1->lexeme);	
		  free($1);
		}
	| unsigned_real 
		{ printf("\n unsinged real ");
		  $$=SymtabCreateNewConst(CONST_REAL,$1->lexeme);
		  free($1);
		}
	;

unsigned_integer : 
	DIGSEQ {$$=$1;}
 ;

unsigned_real : 
	REALNUMBER {$$=$1;}
 ;

/* functions with no params will be handled by plain identifier */
function_designator : 
	identifier params
	 { //printf("\n id");
	   int currlevel,proclevel,i,no_of_arg,is_func=0; Typeptr tptr;
	   Argptr aptr; char buf[1224];
	   Typecheckptr temp; int count=0; strcpy(buf,"");
	   if(!TpCheckIsStdFunc($1->lexeme))
	   {
	      if(aptr=TpCheckIsProcInScope($1->lexeme,&currlevel,
			&proclevel,&no_of_arg,&is_func,&tptr))
	        if(is_func)
	        {   strcat(buf,$1->lexeme);strcat(buf,"(");
		    temp=$2;
		    while(temp) { ++count; temp=temp->nxt;}
		    if(count!=no_of_arg)
			tperror(PROC_WRONG_NO_OF_ARG);
		    temp=$2;
		    while(temp)
		    { if(mystrcmp(aptr->type->typename,temp->type->typename)==0)
		      {	
			  if(aptr->arg_type==VAR_PARAM && 
				aptr->type->type_type!=ARRAY_TYPE)
			    strcat(buf,"&");
			  strcat(buf,temp->string);	 
			  if(temp->nxt) strcat(buf,",");
		       }
		       else tperror(PROC_WRONG_TYPE_ARG);		
		       aptr=aptr->nxt; temp=temp->nxt;
		    }
		    if(currlevel)
	 	    {
			if(currlevel==proclevel-1)  // child called
			{	if(no_of_arg) strcat(buf,",");  
				strcat(buf,"&W");strcat(buf,")");
			 }
			else{ 
			 if(proclevel>1){
			   i=currlevel-proclevel+1;
			   if(no_of_arg)	strcat(buf,",");
			   while(--i)
				strcat(buf,"SCP->");
			   strcat(buf,"SCP)");	
			  } else strcat(buf,")");	
			}
		    }
	            else { 
			strcat(buf,")");
		    }
		    $$=(Typecheckptr)malloc(sizeof(Typecheck));
		    $$->nxt=NULL;
		    $$->type=tptr;
		    $$->string=(char *)malloc(strlen(buf)+1);
	 	    strcpy($$->string,buf);
	        } 
	        else tperror(ID_NOT_FUNC,$1->lexeme);
	   else tperror(FUNC_NOT_IN_SCOPE,$1->lexeme);	
	 } 
	 else 
		$$=PrintStdFuncCall($1->lexeme,$2,YES);
        }
	| identifier LPAREN RPAREN
	  { int currlevel,proclevel,i,no_of_arg,is_func=0; Typeptr tptr;
	   Argptr aptr; char buf[1224];
	   Typecheckptr temp; int count=0; strcpy(buf,"");
	   if(!TpCheckIsStdFunc($1->lexeme))
	   {
	      if(aptr=TpCheckIsProcInScope($1->lexeme,&currlevel,
			&proclevel,&no_of_arg,&is_func,&tptr))
		{ $$=(Typecheckptr)malloc(sizeof(Typecheck));
		  $$->nxt=NULL; $$->type=tptr;
		  $$->string=(char *)malloc(strlen($1->lexeme)+5);
		  strcpy($$->string,$1->lexeme);strcat($$->string,"()");
		}
	      else tperror(FUNC_NOT_IN_SCOPE,$1->lexeme);	
	  } else 
		$$=PrintStdFuncCall($1->lexeme,NULL,YES);	
	}
	 ;

set_constructor : 
	LBRAC member_designator_list RBRAC
		{ printf("\n [ member_designator_list ] ");
		}
	 | LBRAC RBRAC
		{ printf("\n [ ] ");
		}
	 ;

member_designator_list : 
	member_designator_list comma member_designator
		{ printf("\n member_designator_list , member_designator ");
		}
	 | member_designator
		{ printf("\n member_designator ");
		}
	 ;

member_designator : 
	member_designator DOTDOT expression
		{ printf("\n member_desigantor .. expr ");
		}
	 | expression
		{ printf("\n expr ");
		  printf("\n --------------expr ----------");
		}
 	;

addop: PLUS {$$=$1;}
 | MINUS {$$=$1;}
 | OR {$$=$1;}
 ;

mulop : STAR {$$=$1;}
 | SLASH {$$=$1;}
 | DIV {$$=$1;}
 | MOD {$$=$1;}
 | AND {$$=$1;}
 ;

relop : EQUAL {$$=$1;}
 | NOTEQUAL {$$=$1;}
 | LT {$$=$1;}
 | GT {$$=$1;}
 | LE {$$=$1;}
 | GE {$$=$1;}
 | IN {$$=$1;}
 ;

identifier : 
	IDENTIFIER 
		{ $$=$1; 
		//printf("\n id= %s",$1->lexeme); getchar();
		}
	 ;

semicolon : 
	SEMICOLON
		{ $$=$1;
		}
	 ;

comma : COMMA
		{ $$=$1; 
		}
	 ;

%%

yyerror(char *s)
{ printf("\nline %d:  %s",line_no,s);
  yyerrok;
  return 1;	
}

YaccRetptr StringCat(int args,...)
{	
	va_list argptr;
 	int i,size=1;
	YaccRetptr temp1,temp2;
	if(args<2)
	  { printf("\n args to StringCat should be more than 1 ");
	   return;
	  }	
	va_start(argptr,args);

	temp1=(YaccRetptr)malloc(sizeof(YaccRettype));
	temp1->lexeme=(char *) malloc(sizeof(char));
	for(i=0;i<args;i++)
	{     temp2=va_arg(argptr,YaccRetptr);
	      size=size	+ sizeof(temp2->lexeme)+1;	
	      temp1->lexeme=(char *)realloc(temp1->lexeme,size);
	      strcat(temp1->lexeme,temp2->lexeme);
	}
	va_end(argptr);
	return &(*temp1);
}		
Constptr MakeConstList(Constptr ptr1,Constptr ptr2)
{ Constptr temp; int low,high;
  if(ptr1->const_type==CONST_REAL||ptr2->const_type==CONST_REAL)
 	{printf("\n constant list of real is not possible "); getchar();
	return NULL;	
	}
  if((ptr1->const_type==CONST_CHAR && strlen(ptr1->string)>1)
    ||(ptr2->const_type==CONST_CHAR && strlen(ptr2->string)>1))
   { printf("\n char constant can't  be more than one character in constlist");
	getchar();
	return NULL;
   }
  if(ptr1->const_type==CONST_INT && ptr2->const_type==CONST_INT)
  {  low=(int)ptr1->value; high=(int)ptr2->value;
     temp=ptr1;
     while(low<high-1)
    { temp->nxt=(Constptr)malloc(sizeof(Constant));
	temp->nxt->const_type=CONST_INT;
	temp->nxt->value=low+1; 
	temp=temp->nxt;
	low++;
    }
    temp->nxt=ptr2;
     temp=ptr1;
     while(temp) { printf(" %d",(int)temp->value); temp=temp->nxt;}
    return ptr1;	
  }
  if(ptr1->const_type==CONST_CHAR && ptr2->const_type==CONST_CHAR)
  {  low=(int)ptr1->string[0]; high=(int)ptr2->string[0];
     temp=ptr1;
     while(low<high-1)
    {  char buf[24];temp->nxt=(Constptr)malloc(sizeof(Constant));
	temp->const_type=CONST_CHAR;
	temp->string=(char *)malloc(2);
	sprintf(buf,"%c",low+1);
	strcpy(temp->string,buf);
	low++;
    }
    temp->nxt=ptr2;
    return ptr1;	
  }
  else { printf("\n both constants are not of same type");
	getchar();
	return NULL;
  }	
}
