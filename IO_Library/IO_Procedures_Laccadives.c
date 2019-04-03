#include <HEADERS.h>
#include "IO_Procedures_Laccadives.h"

// Commonly, the following line should be commented out

// #define CHECKING_INPUT_FILES

// You only need it for checking purposes. In that case you need 
// a specific directory named "./ATOLL_FEEDING_STRATEGY_STD_DATA/"
// to save new files created

void Reading_Matrix_East_West_from_File(char * File_Name,  double ** Presence__Data, 
					char ** Species_Name,
					char ** Guild_Name, 
					int N_row, int N_column)
{
  int    i,j;
  double   y;

  FILE * fp;
  printf("\n[Entering function Reading_Matrix_from_File(...)]\n  Reading File %s...\n",  
	 File_Name); 
  printf("Press any key to continue...\n"); // getchar();
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    exit(1);
  }

  for(i=0; i < N_row; i++){
    fscanf(fp, "%s\t", Species_Name[i] );

    fscanf(fp, "%s\t", Guild_Name[i]   );

    for(j=2; j < N_column; j++) { 
      if( j == (N_column-1) ) fscanf(fp, "%lf\n", &y); 
      else                    fscanf(fp, "%lf\t", &y); 
      Presence__Data[i][j-2] = y; 
    }
  }

  fclose(fp);
  printf("    File %s has been read successfully\n", File_Name); 
  
  printf("[Exiting function Reading_Matrix_from_File(...)]\n\n");

  printf("Press any key to continue...\n"); 
}

void Writing_Matrix_East_West(double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      int N_row, int N_column)
{
  int i,j;

  for(i=0; i < N_row; i++){
    fprintf(stdout, "%s\t", Species_Name[i] );

    fprintf(stdout, "%s\t", Guild_Name[i]   );

    for(j=2; j < N_column; j++) { 
        fprintf(stdout, "%g\t", Presence__Data[i][j-2]); 
    }    
    fprintf(stdout, "\n");

  }
}

void Reading_Matrix_from_File_Header_True(char * File_Name,  double ** Presence__Data,
                              		  double * Time, 
					  char ** Species_Name,
                              		  char ** Guild_Name,
                              		  char ** Island_Name,
                              		  int N_row, int N_column)
{
  int    i,j;
  double   y;

  FILE * fp;
  printf("\n[Entering function Reading_Matrix_from_File(...)]\n  Reading File %s...\n",  File_Name);
  printf("Press any key to continue...\n"); // getchar();
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open ""%s"" file.\n", File_Name);
    exit(1);
  }
 
  char * Dummy = (char *)calloc( 50, sizeof(char) ); 
  fscanf(fp, "%s\t", Dummy ); fscanf(fp, "%s\t", Dummy ); fscanf(fp, "%s\t", Dummy );
  for(j=3; j < N_column; j++) {
      if( j == (N_column-1) ) fscanf(fp, "%lf\n", &y);
      else                    fscanf(fp, "%lf\t", &y);
      Time[j-3] = y;
  }

  for(i=0; i < N_row; i++){
    fscanf(fp, "%s\t", Species_Name[i] );

    fscanf(fp, "%s\t", Island_Name[i]  );

    fscanf(fp, "%s\t", Guild_Name[i]   );

    for(j=3; j < N_column; j++) {
      if( j == (N_column-1) ) fscanf(fp, "%lf\n", &y);
      else                    fscanf(fp, "%lf\t", &y);
      Presence__Data[i][j-3] = y;
    }
  }

  fclose(fp);
  printf("    File %s has been read successfully\n", File_Name);

  printf("[Exiting function Reading_Matrix_from_File(...)]\n\n");

  printf("Press any key to continue...\n");
  
  free(Dummy); 
}


void Reading_Matrix_from_File(char * File_Name,  double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      char ** Island_Name,
			      int N_row, int N_column)
{
  int    i,j;
  double   y;

  FILE * fp;
  printf("\n[Entering function Reading_Matrix_from_File(...)]\n  Reading File %s...\n",  File_Name); 
  printf("Press any key to continue...\n"); // getchar();
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open ""%s"" file.\n", File_Name);
    exit(1);
  }

  for(i=0; i < N_row; i++){
    fscanf(fp, "%s\t", Species_Name[i] );

    fscanf(fp, "%s\t", Island_Name[i]  );

    fscanf(fp, "%s\t", Guild_Name[i]   );

    for(j=3; j < N_column; j++) { 
      if( j == (N_column-1) ) fscanf(fp, "%lf\n", &y); 
      else                    fscanf(fp, "%lf\t", &y); 
      Presence__Data[i][j-3] = y; 
    }
  }

  fclose(fp);
  printf("    File %s has been read successfully\n", File_Name); 
  
  printf("[Exiting function Reading_Matrix_from_File(...)]\n\n");

  printf("Press any key to continue...\n"); 
}

void Writing_Matrix(double ** Presence__Data, 
		    char ** Species_Name,
		    char ** Guild_Name, 
		    char ** Island_Name,
		    int N_row, int N_column)
{
  int i,j;

  for(i=0; i < N_row; i++){
    fprintf(stdout, "%s\t", Species_Name[i] );

    fprintf(stdout, "%s\t", Guild_Name[i]   );

    fprintf(stdout, "%s\t", Island_Name[i]  );

    for(j=3; j < N_column; j++) { 
        fprintf(stdout, "%g\t", Presence__Data[i][j-3]); 
    }    
    fprintf(stdout, "\n");

  }
}

void Writing_Matrix_to_File(  char * File_Name, 
			      double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      char ** Island_Name,
			      int N_row, int N_column)
{
  int i,j;

  FILE * FP = fopen(File_Name, "w");
  for(i=0; i < N_row; i++){
    fprintf(FP, "%s\t", Species_Name[i] );

    fprintf(FP, "%s\t", Island_Name[i]  );

    fprintf(FP, "%s\t", Guild_Name[i]   );
    
    for(j=0; j < N_column-3; j++) { 
      if( Presence__Data[i][j] == 0.0 || Presence__Data[i][j] == 1.0 )
	fprintf(FP, "%g\t", Presence__Data[i][j]); 
    }    
    fprintf(FP, "\n");
  }
  fclose(FP);

}

void Writing_Single_Matrix_East_West(  double ** Presence__Data, 
				       char ** Species_Name,
				       char * Island_Name,
				       char * Site, 
				       char * Guild_Name, 
				       int N_row, int N_column )
{
  int i,j;

  for(i=0; i < N_row; i++){
    fprintf(stdout, "%s\t", Species_Name[i] );

    fprintf(stdout, "%s\t", Island_Name  );

    fprintf(stdout, "%s\t", Guild_Name   );

    fprintf(stdout, "%s\t", Site   );
    
    for(j=0; j < N_column; j++) { 
	fprintf(stdout, "%g\t", Presence__Data[i][j]); 
    }    
    fprintf(stdout, "\n");
  }
}

void Writing_Single_Matrix_East_West_to_File(  char * File_Name, 
					       double ** Presence__Data, 
					       char ** Species_Name,
					       char * Island_Name,
					       char * Site, 
					       char * Guild_Name, 
					       int N_row, int N_column)
{
  int i,j;

  FILE * FP = fopen(File_Name, "w");
  for(i=0; i < N_row; i++){
    fprintf(FP, "%s\t", Species_Name[i] );

    fprintf(FP, "%s\t", Island_Name  );

    fprintf(FP, "%s\t", Guild_Name   );

    fprintf(FP, "%s\t", Site   );
    
    for(j=0; j < N_column; j++) { 
      if( Presence__Data[i][j] == 0.0 || Presence__Data[i][j] == 1.0 )
	fprintf(FP, "%g\t", Presence__Data[i][j]); 
    }    
    fprintf(FP, "\n");
  }
  fclose(FP);

}

void Reading_Single_Matrix_East_West_from_File(  char * File_Name, 
						 double ** Presence__Data, 
						 char ** Species_Name,
						 char * Island_Name,
						 char * Site, 
						 char * Guild_Name, 
						 int N_row, int N_column )
{
  int i,j;
  double y;
  FILE * fp;

  printf("\n[Entering function Reading_Matrix_from_File(...)]\n  Reading File %s...\n",  
	 File_Name); 
  printf("Press any key to continue...\n"); // getchar();
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    exit(1);
  }

  for(i=0; i < N_row; i++){
   
    fscanf(fp, "%s\t", Species_Name[i] );

    fscanf(fp, "%s\t", Island_Name  );

    fscanf(fp, "%s\t", Guild_Name   );

    fscanf(fp, "%s\t", Site   );
    
    for(j=0; j < N_column; j++) { 
      if( j == (N_column-1) ) fscanf(fp, "%lf\n", &y); 
      else                    fscanf(fp, "%lf\t", &y); 
      
      Presence__Data[i][j] = y; 
    }    
  }
  fclose(fp);
}

void Laccadive_File_Name_Creator (char ** Name, 
					    char ** Feeding_Strategy )
{
	    char * ca;
	    int i;
	    
	    for( i=0; i<3; i++ ) Name[i]  = (char *)calloc( 50, sizeof(char  ));
	    
	    Name[0][0]='\0';   ca     = strcat( Name[0], "AGATTI");
	    Name[1][0]='\0';   ca     = strcat( Name[1], "KADMAT");
	    Name[2][0]='\0';   ca     = strcat( Name[2], "KAVARATTI");
	  
	    for( i=0; i<7; i++ ) Feeding_Strategy[i]  = (char *)calloc( 50, sizeof(char  ));

	    Feeding_Strategy[0][0]='\0'; ca=strcat( Feeding_Strategy[0], "Algal_Feeder");
	    Feeding_Strategy[1][0]='\0'; ca=strcat( Feeding_Strategy[1], "Omnivore");
	    Feeding_Strategy[2][0]='\0'; ca=strcat( Feeding_Strategy[2], "Corallivore");
	    Feeding_Strategy[3][0]='\0'; ca=strcat( Feeding_Strategy[3], "Zooplanktivore");
	    Feeding_Strategy[4][0]='\0'; ca=strcat( Feeding_Strategy[4], "Microinvertivore");
	    Feeding_Strategy[5][0]='\0'; ca=strcat( Feeding_Strategy[5], "Macroinvertivore");
	    Feeding_Strategy[6][0]='\0'; ca=strcat( Feeding_Strategy[6], "Piscivore");
}

void Reading_Total_Matrix_Data ( char * FILE_NAME, int Sp, int Nc, 
				 double ** Total_Presence )
  {
    int i;
    char ** Species_Name; char ** Guild_Name; char ** Island_Name;

    Species_Name = (char **)calloc(3*Sp, sizeof(char *) );
    Guild_Name   = (char **)calloc(3*Sp, sizeof(char *) );
    Island_Name  = (char **)calloc(3*Sp, sizeof(char *) );

    for( i=0; i<3*Sp; i++ ) {

        Species_Name[i]  = (char *)calloc(50, sizeof(char) );
        Guild_Name[i]    = (char *)calloc(50, sizeof(char) );
        Island_Name[i]   = (char *)calloc(50, sizeof(char) );
      }

      Reading_Matrix_from_File(FILE_NAME, Total_Presence,
                               Species_Name, Guild_Name, Island_Name,
                               3*Sp, Nc);

      /* BEGIN: Freeing up memory ----------------------------------------- */
      for( i=0; i<3*Sp; i++ ) {
        free(Species_Name[i]);
        free(Guild_Name[i]  );
        free(Island_Name[i] );
      }
      free(Species_Name);  free(Guild_Name); free(Island_Name);
      /*   END: ----------------------------------------------------------- */
  }

void Reading_Atoll_Feeding_Strategy_Data (double **** Presence_Data, 
					  int ** ROWS, int ** COLUMNS, 
					  char ** Name, char ** Feeding_Strategy )
  {
    int i,k,l;
    char ** Species_Name;
    char ** Guild_Name;
    char ** Island_Name;
    char * FILE_NAME = (char *)calloc(100, sizeof(char) );
    char * p_FILE;   
    double * Time_Vector = (double *)calloc(6, sizeof(double) );
    
    for( k = 0; k<3; k++ ) {
      for( l = 0; l<7; l++ ) {
	
	Species_Name = (char **)calloc(ROWS[k][l], sizeof(char *) );
	Guild_Name   = (char **)calloc(ROWS[k][l], sizeof(char *) );
	Island_Name  = (char **)calloc(ROWS[k][l], sizeof(char *) );
	
	for( i=0; i<ROWS[k][l]; i++ ) {
	  
	  Species_Name[i]  = (char *)calloc(50, sizeof(char) );
	  Guild_Name[i]    = (char *)calloc(50, sizeof(char) );
	  Island_Name[i]   = (char *)calloc(50, sizeof(char) );
	}
	
	FILE_NAME[0]='\0';
	p_FILE = strcat( FILE_NAME, "../../DATA_ILLES_LACADIVES/");
	p_FILE = strcat( FILE_NAME, Name[k] );
	p_FILE = strcat( FILE_NAME, "_"     );
	p_FILE = strcat( FILE_NAME, Feeding_Strategy[l] );
	p_FILE = strcat( FILE_NAME, ".dat"  );
	
	Reading_Matrix_from_File(FILE_NAME, Presence_Data[k][l], 
				 Species_Name, Guild_Name, Island_Name,
				 ROWS[k][l], COLUMNS[k][l]+3);
#if defined CHECKING_INPUT_FILES	
	/* B E G I N : Writing_Atoll_Feeding_Strategy_Data for checking purposes */
	// Creation of standard data files (see IO_Procedures_Standard.c)
        assert( COLUMNS[k][l] <= 6 );
               
	/*           : Empirical observational years */
	if( k<2 ){      
                Time_Vector[0] = 2000.0;
		Time_Vector[1] = 2001.0;
		Time_Vector[2] = 2002.0;
		Time_Vector[3] = 2003.0;
		Time_Vector[4] = 2010.0;
		Time_Vector[5] = 2011.0;
	}
	else{
	  Time_Vector[0] = 2001.0;                        
	  Time_Vector[1] = 2002.0;                  
	  Time_Vector[2] = 2003.0;               
	  Time_Vector[3] = 2011.0; 
	}
	/*          : ----------------------------- */ 

	FILE_NAME[0]='\0';
	p_FILE = strcat( FILE_NAME, "./ATOLL_FEEDING_STRATEGY_STD_DATA/");
	p_FILE = strcat( FILE_NAME, Name[k] );
	p_FILE = strcat( FILE_NAME, "_"     );
	p_FILE = strcat( FILE_NAME, Feeding_Strategy[l] );
	p_FILE = strcat( FILE_NAME, ".dat"  );
	Writing_Standard_Data_Matrix_to_File(  FILE_NAME, 
					       Presence_Data[k][l],  
					       Species_Name,
					       Time_Vector,
					       ROWS[k][l], COLUMNS[k][l] );
	
	/*     E N D : Writing_Atoll_Feeding_Strategy_Data for checking purposes */
#endif
	/* BEGIN: Freeing up memory ----------------------------------------- */
	for( i=0; i<ROWS[k][l]; i++ ) {
	  free(Species_Name[i]);
	  free(Guild_Name[i]  );
	  free(Island_Name[i] );
	}
	free(Species_Name);  free(Guild_Name); free(Island_Name);
	/*   END: ----------------------------------------------------------- */
      }
    }
    
    free (Time_Vector);
    free (FILE_NAME);
  }

void Reading_Atoll_Matrix_Data( char ** Name, 
				int Sp, 
				double *** Atoll_Presence )
{
  int k, i;
  int n_Columns;
  char ** Species_Name; 
  char ** Guild_Name; 
  char ** Island_Name;
  char * FILE_NAME = (char *)calloc(100, sizeof(char) );
  char * p_FILE;   

  for( k = 0; k<3; k++ ) {
    if (k==2) { n_Columns = 4; }
    else      { n_Columns = 6; }
    Atoll_Presence[k] = (double **)calloc( Sp, sizeof(double *) );
    for( i=0; i<Sp; i++ ) {
      Atoll_Presence[k][i] = (double *)calloc(n_Columns, sizeof(double) );
    }
  }
  
  for( k = 0; k<3; k++ ) {
    
    if (k==2) { n_Columns = 4; }
    else      { n_Columns = 6; }
    Species_Name = (char **)calloc(Sp, sizeof(char *) );
    Guild_Name   = (char **)calloc(Sp, sizeof(char *) );
    Island_Name  = (char **)calloc(Sp, sizeof(char *) );
    
    for( i=0; i<Sp; i++ ) {
      
      Species_Name[i]  = (char *)calloc(50, sizeof(char) );
      Guild_Name[i]    = (char *)calloc(50, sizeof(char) );
      Island_Name[i]   = (char *)calloc(50, sizeof(char) );
    }
    
    FILE_NAME[0]='\0';
    p_FILE = strcat( FILE_NAME, "../../DATA_ILLES_LACADIVES/");
    p_FILE = strcat( FILE_NAME, Name[k] );
    p_FILE = strcat( FILE_NAME, ".dat"  );
    
    Reading_Matrix_from_File(FILE_NAME, Atoll_Presence[k],
			     Species_Name, Guild_Name, Island_Name,
			     Sp, n_Columns + 3);

    /* BEGIN: Freeing up memory ----------------------------------------- */
    for( i=0; i<Sp; i++ ) {
      free(Species_Name[i]);
      free(Guild_Name[i]  );
      free(Island_Name[i] );
    }
    free(Species_Name);  free(Guild_Name); free(Island_Name);
    /*   END: ----------------------------------------------------------- */
  }
  free (FILE_NAME);
}
