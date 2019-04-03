#include <MODEL.h>

/* Global Shared parameters main Program <---> ArgumentControl() */
#include "extern.h"

void ArgumentControl(int argc, char **argv)
{
  int argcount, skip;
  int n_Dummy;

  FILE * fp = stdout;

  for(argcount=1; argcount<argc; argcount+=skip)
    {
      if(argv[argcount][0] == '-')
	{
	  skip = 1;
	  switch(argv[argcount][1])
	    {

#include <include.Parameter_Model.argumentControl.c>
#include <include.Parameter_Space.argumentControl.c>

  	    default:
	      printf("**invalid command line argument >%c< \n",
		     argv[argcount][1]);
	    case 'h':
              printf(" Program argument options:\n");

#include <include.Parameter_Model.report.c>
#include <include.Parameter_Space.report.c>
	      
	      printf("\n");
	      printf(" As an example,\n");
	      printf("        >> %s -sP 2 -sN 1000 \n\n",  argv[0]);

	      exit(0);
	    }
	}
      else
	{
	  printf("**invalid command line flag >%c<\n",argv[argcount][0]);
	  printf("try -h for help.\n");
	  exit(0);
	}
    }
}
