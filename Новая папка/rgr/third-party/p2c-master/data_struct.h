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


/*  all the data structure definations for the symbol table management..
 *  Functions are stored as atree with the symbol table of each function managed
 *  seperately.. polongers drawn from each function definition for the local vars
 *  and the local typedefs + constants .the Tree is has 2 way polongers ( from
 *  child to parent also.
 */

#ifndef __data_structures_
#define __data_structures_

typedef struct yacc_return_type *YaccRetptr;
typedef struct yacc_return_type
{
  char *lexeme;
  unsigned long type;
  unsigned long no_of_children;
  struct return_type **ptrptr;
}
YaccRettype;
 /************************************************************************/
typedef struct type *Typeptr;
typedef struct function *Funptr;
typedef struct var *Varptr;
typedef struct arg *Argptr;
typedef struct constant *Constptr;
/************************************************************************/

typedef struct  typecheck *Typecheckptr;
typedef struct typecheck{
	char *string;
	Typeptr type;
	Typecheckptr nxt;
}Typecheck;
 /************************************************************************/
// All type definitions 
#define ENUM_TYPE  	201
#define SUBRANGE_TYPE   202
#define ARRAY_TYPE 	203
#define RECORD_TYPE 	204
#define SET_TYPE 	205
#define FILE_TYPE 	206
#define POINTER_TYPE 	207

#define INTEGER_TYPE	208
#define REAL_TYPE	209
#define CHAR_TYPE	210
#define BOOLEAN_TYPE	211
#define EXISTING 	213	// for better modularity

 /************************************************************************/
// for function declarations
#undef FORWARD
#define FORWARD	   	 0x01
#undef CURRENT
#define CURRENT   	 0x02
#undef EXTERNAL
#define EXTERNAL 	 0x04
typedef struct function
{
  char *fname;
  long level;

  unsigned long no_of_arg;
  Argptr arglist;

  long directive_flag;

  Typeptr ret_type;		// set to NULL for procedure 
  char *ret_value_name;

  unsigned long no_of_types;
  Typeptr typelist;

  unsigned long no_of_vars;
  Varptr varlist;

  unsigned long no_of_consts;
  Constptr constlist;

  unsigned long no_of_children;
  Funptr *children;		// as many no. of children  can be allowed

  Funptr parent;		//polonger to parent
}
Function;
/************************************************************************/


typedef struct idnode *Idptr;
typedef struct idnode
{
  char *idname;
  Idptr nxt;
}
Idnode;

 /************************************************************************/
typedef struct dimension
{
  long type_flag;//either subrange or enumerated or integer or char or bool
  union
  {
    struct
    {
      Constptr low;
      Constptr high;
    };
    struct
    {
      unsigned long no_of_ids;
      Idptr idptr;
    };
  };
}
Dimension;

 /************************************************************************/
typedef struct var
{
  char *name;
  Typeptr type;
  Funptr func;
  Varptr nxt;
}
Var;

 /************************************************************************/
#define VALUE_PARAM   	401
#define VAR_PARAM	402
#define PROC_PARAM	403
#define FUNC_PARAM	404
typedef struct arg
{
  char *name;
  unsigned long arg_type;		// one of above 4 #defines
  Typeptr type;
  Funptr func;
  Argptr nxt;
}
Arg;

 /************************************************************************/
#define CONST_INT 501		// these #defines used for both constant struct
#define CONST_REAL 502		// and the subrange type also
#define CONST_CHAR 503
#define CONST_ID 504
typedef struct constant
{
  char *name;
  unsigned int const_type;	//either int or real or char const
/*  float value;  // this is due to a great mistake .. it should have been within the union but now all the const expression evaluation things have been written out and you cant afford to change them */
  Funptr func;
  union
  { float value;
    char *string;
  };
  Constptr nxt;
}
Constant;
/*-----------------------------------------------------------------------*/
typedef struct type
{
  char *typename;		// set to NULL if no name is given
  unsigned long type_type;	// see the above #defines 
  Funptr func;
  union
  {
    struct enum_type
    {
      Idptr idlist;		// list of all enum ids
      unsigned long no_of_member;
    };
    struct subrange_type
    {
      Constptr low;
      Constptr high;
    };
    struct array_type
    {
      unsigned long no_of_dimn;
      Typeptr elemtype;		//type of array elem
      Dimension *dimensions;	//array of each dimension record
    };
    struct record_type
    {
      unsigned long no_of_elem;
      //use same index for type and var       
      //Typeptr *typeptrptr;  array of each type
      Varptr varlist;	// array of each var of each type
    };
    struct var_record_type
    {
      Varptr selector;

    };
    struct set_type
    {
      unsigned long no_of_elem;
      Dimension dimension;
      //set can be only enumeration or subrange
    };
    struct file_type
    {
      Typeptr type;
    };
    struct pointer_type
    {
      Typeptr typeptr;
      unsigned int is_fwd_ref;	// denotes fwd ref for a pointer type
      				// finally it should be zero
      char *fwd_ref_name;	// could have been a union
    };
  };	// union end
  Typeptr nxt;
}
Type;


/************************************************************************/

#endif // **  data_struct.h **
