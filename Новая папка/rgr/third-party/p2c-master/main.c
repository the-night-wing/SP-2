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
#include <string.h>
#include "data_struct.h"
#include "globals.h"
#include "prototype.h"
#include <signal.h>
extern FILE *yyin;
extern int line_no;
extern int level_of_nesting;

void  seghandle(int signal)
{       fflush(stdout);  fflush(cfile);
	fflush(stdout);  fflush(cfile); fclose(cfile);
	printf("\nHandled segmentation fault"); getchar(); getchar();
	exit(0);
}
main (int argc, char *argv[])
{
  yyin = fopen (argv[1], "r");
  if(signal(SIGSEGV,seghandle)==SIG_ERR)
  { perror("segm fault not handled");
    exit(0);
  }
  if (yyin == NULL)
    {
      yyin = stdin;
      cfile = fopen (".xxxxxx", "w+");
    }
  else
    {
      strcpy (pasfilename, argv[1]);
      GetcFilename (pasfilename, cfilename);
      cfile = fopen (cfilename, "w+");
      if (cfile == NULL)
	{
	  printf ("\n error opening cfile ");
	  exit (1);
	}
    }
  PrintHeader ();
  SymtabInit ();
  yyparse ();
}

int
GetcFilename (char *pasfile, char *cfile)
{
  char *p;
  int len, i;

  len = strlen (pasfile);
  p = pasfile + len - 4;
  printf ("\n *p= %c", *p);
  if ((*p == '.') && (strcmp (p + 1, "pas") == 0))
    {
      char *q = pasfile, *r = cfile;
      i = 0;
      while (i < strlen (pasfile) - 4 && pasfile[i])
	{
	  *r++ = *q++;
	  i++;
	}
      *r++ = '.';
      *r++ = 'C';
      *r = '\0';
      printf ("\n c file  = %s", cfile);
    }
  else
    printf ("\n improper pas file name %s", pasfile);

}
