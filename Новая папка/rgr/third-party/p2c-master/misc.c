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
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include "data_struct.h"
#include "prototype.h"


long
GetRange (long low, long high)
{
  if (low < 0)
    if (high < 0)
      return abs (abs (high) - abs (low))+1;
    else
      return abs (low) + high;
  else if (high < 0)
    return abs (high) + low;
  else
    return high - low+1;
}
int mystrcmp(char *str1,char *str2)
{  
	while(*str1!='\0' && *str2!='\0')
	{ 
	     if((*str1)==(*str2)|| (*str1-32)==(*str2) || (*str2-32)==(*str1))
	     { str1++; 
	       str2++;
	      }
	   else { 
		   return((*str1)-(*str2));	
	   }
	}
   if((*str1=='\0') && (*str2=='\0')) return 0;	
   else if(*str1 && (*str2=='\0')) return -(*str1);
   else if(*str2 && (*str1=='\0')) return (*str2);   
}
int GetSetRange(char *buff,long no)
{   long temp;
    temp=no/(32);
    if(temp==0) temp=1;
    sprintf(buff,"%d",temp);	
}
