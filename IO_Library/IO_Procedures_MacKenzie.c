#include <HEADERS.h>
#include "IO_Procedures_MacKenzie.h"

#define No_of_TIME_OBS_MAX 100000 // Maximum number of temporal observations 
                                  // (total temporal columns in the data matrix)
                                  // (check accordance with definition in MODEL.h)

void Writing_Standard_Double_Matrix_to_File( char * File_Name,
                                    double ** Presence_Data,
                                    int N_row, int N_col )
{ 
  /* Input parameters: 
     . N_row: Number of Species
     . N_col: Number of Columns 
     . Presence__Data[][]: Data

     Output: a file containing a data matrix:

               0  0  1  0  0  0  0  1  1  ... ... ... 1  1  0 
               1  0  1  0  0  0  0  1  0   .. ... ... 1  1  0 
                     .
                     .
                     .
  */
  int i,j;

  FILE * FP = fopen(File_Name, "w");
  for(i=0; i < N_row; i++){
    for(j=0; j < N_col; j++) {
        if( j == (N_col-1)  )
          fprintf(FP, "%g\n", Presence_Data[i][j]);
        else
          fprintf(FP, "%g\t", Presence_Data[i][j]);
    }
  }

  fclose(FP);
}

void Writing_MacKenzie_Data_Matrix_to_File(  char * File_Name, 
					     double ** Presence_Data, 
					     char ** Species_Name, int N_row, 
					     double * Time_Vector, int * Transects, 
					     int No_of_TIMES)
{
  /* Input parameters: 
     . N_row: Number of Species
     . No_of_TIMES: Number of Sampling Times
     . Presence__Data[][]: Data
     . Species__Name[][]: Species Names
     . Time_Vector[]: a double array containing sampling times
     . Transects[] an integer array containing number of transects per sampling time.

     Output: a file containing a data matrix:

       species      t0 t0 t0 t1 t1 t1 t2 t2 t2 ... ... ... tn tn tn
                    -- -- -- -- -- -- -- -- -- --- --- --- -- -- --
       Sp_0	     0  0  1  0  0  0  0  1  1  ... ... ... 1  1  0 
       Sp_1	     1	0  1  0  0  0  0  1  0   .. ... ... 1  1  0 
	             .
		     .
		     .

  */
  int i,j,k,n;
  
  FILE * FP = fopen(File_Name, "w");
  fprintf(FP, "%s\t", "Species_Name");
  for(j=0; j < No_of_TIMES; j++) {
    for(i=0; i < Transects[j]; i++) {
      if( j == (No_of_TIMES-1) && i == (Transects[j]-1) )
	fprintf(FP, "%g\n", Time_Vector[j]);
      else
	fprintf(FP, "%g\t", Time_Vector[j]);
    }
  }
  
  for(i=0; i < N_row; i++){
    fprintf(FP, "%s\t", Species_Name[i] );
    n = 0;
    for(j=0; j < No_of_TIMES; j++) {
      for(k=0; k < Transects[j]; k++) {
	if( j == (No_of_TIMES-1) && k == (Transects[j]-1) )
	  fprintf(FP, "%g\n", Presence_Data[i][n++]);
	else
	  fprintf(FP, "%g\t", Presence_Data[i][n++]);
      } 
    }	   
  }
  fclose(FP);
}

void Reading_MacKenzie_Data_Matrix_from_File(  char * File_Name, 
					       double ** Presence_Data, 
					       char ** Species_Name, int * Species, 
					       double * Time_Vector, int * Transects, 
					       int No_of_TIMES )
{
  /* Input parameters: 
     . * Species: Pointer to the Number of Species (also given as an output) 
     . No_of_TIMES: Number of Sampling Times
     . Presence__Data[][]: Data
     . Species__Name[][]: Species Names
     . Time_Vector[]: a double array containing sampling times
     . Transects[] an integer array containing number of transects per sampling time.

     Output
     . * Species: number of species read from file 
     . Reading the matrix into Presence_Data[][]:

       species      t0 t0 t0 t1 t1 t1 t2 t2 t2 ... ... ... tn tn tn
                    -- -- -- -- -- -- -- -- -- --- --- --- -- -- --
       Sp_0	     0  0  1  0  0  0  0  1  1  ... ... ... 1  1  0 
       Sp_1	     1	0  1  0  0  0  0  1  0  ... ... ... 1  1  0 
	.            .                                            .
	.	     .                                            .
	.	     .                                            . 
  */
  int i,j,n, N;
  double y; 
  char * Name_Dummy = (char *)calloc( 50, sizeof(char) );

  FILE * fp; 
  printf("\n [Entering function Reading_MacKenzie_Data_Matrix_from_File(...)]\n");
  printf(" Reading File %s...\n", File_Name); 
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    error(0,0,"Program aborted");
  }
  N = 0;
  for(j=0; j < No_of_TIMES; j++) N += Transects[j]; 
    
  fscanf(fp, "%s\t", Name_Dummy );
  n=0;
  for(j=0; j < No_of_TIMES; j++) {
    for(i=0; i < Transects[j]; i++) {
       if( n == (N - 1) ) fscanf(fp, "%lf\n", &y);
       else               fscanf(fp, "%lf\t", &y);
       n++;
    }
    Time_Vector[j] = y; 
  }

  n=0;
  while ( fscanf(fp, "%s\t", Name_Dummy ) != EOF ){
    strcpy(Species_Name[n], Name_Dummy); 

    for(j=0; j < N; j++) {
      if( j == (N - 1) ) fscanf(fp, "%lf\n", &y);
      else               fscanf(fp, "%lf\t", &y);

      assert( n < (*Species) );
      Presence_Data[n][j] = y;
    }
    n++;
  }
  (*Species) = n;
  
  fclose(fp);  
  
  printf(" A %d species File (%s) has been read successfully\n", (*Species), File_Name); 
  printf(" [Exiting function Reading_MacKenzie_Data_Matrix_from_File(...)]\n\n");

  free(Name_Dummy);  
}

void Reading_MacKenzie_Generic_Matrix_from_File(  char * File_Name, 
						  double ** Presence_Data, 
						  char ** Species_Name, int * Species, 
						  double * Time_Vector, int * Transects, 
						  int * No_of_TIMES )
{
  /* This function works the same as before, but it is better because, while reading 
     the file, it counts the number of species, the number of sampling times, and the 
     number of transects per sampling time. Unlike the function above, this function here
     does not need to know this information to correctly read the file. 

     Input parameters: 
     . * Species: Pointer to Number of Species (also given as an output) 
     . * No_of_TIMES: Number of Sampling Times

     Output
     . * Species: number of species read from file 
     . * No_of_TIMES: number of sampling times.
     . Species__Name[][]: Species Names
     . Time_Vector[]: a double array containing sampling times
     . Transects[] an integer array containing number of transects per sampling time.
     . Reading the matrix into Presence_Data[][]. 

     Note: Presence_Data, Species_Name, Transects, and Time_Vector should have been 
     correctly dimensionalized in the parent code that calls this function. 

       species      t0 t0 t0 t1 t1 t1 t2 t2 t2 ... ... ... tn tn tn
                    -- -- -- -- -- -- -- -- -- --- --- --- -- -- --
       Sp_0	     0  0  1  0  0  0  0  1  1  ... ... ... 1  1  0 
       Sp_1	     1	0  1  0  0  0  0  1  0  ... ... ... 1  1  0 
	.            .                                            .
	.	     .                                            .
	.	     .                                            . 
  */
  int j,n, m,nt, N;
  double y; 
  char * Name_Dummy = (char *)calloc( 50, sizeof(char) );
  int N_MAX = No_of_TIME_OBS_MAX; // Maximum number of temporal observations 
                                  // (total temporal columns in the data matrix)
                                  // (see MODEL.h)
  double * Vector = (double *)calloc( N_MAX, sizeof(double) );

  FILE * fp; 
  printf("\n [Entering function Reading_MacKenzie_Generic_Matrix_from_File(...)]\n");
  printf(" Reading File %s...\n", File_Name); 
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    error(0,0,"Program aborted");
  } 
  /* B E G I N : ---------------------------------------------------------------------
   *             Reading the first row (times and transects)
   */
  fscanf(fp, "%s\t", Name_Dummy );
  int End_of_Line   = '\n';  
  int Tab_Separator = '\t';
  printf("End of Line: %d\t Tab Separator: %d\n", End_of_Line, Tab_Separator);
  
  int ch = Tab_Separator;
  n=0;
  while( ch != End_of_Line  ) {
         fscanf(fp, "%lf", &y);
         ch  = getc( fp );
	 // printf("Vector[%d] = %g\tch: %d\n", n, y, ch);
         if (n < N_MAX) { Vector[n++] = y; }
 	 else { printf("Too many time columns reading file %s\n", File_Name);  exit(0);} 
	 // getchar();
  }
  N  = n; //  Actual number of temporal observations 
          // (total number of time columns in the data matrix)  

  nt = 0;
  m  = 0;
  n  = 0;
  y=Vector[0];
  while (n < N) {
   if( Vector[n] == y ){
     Time_Vector[m] = y;
     nt++;
     n++;
   }
   else {
     y = Vector[n];
     Transects[m++] = nt;
     nt = 0;
   }
  }
  Transects[m] = nt;
  (* No_of_TIMES) = 1 + m;
  /*     E N D : ---------------------------------------------------------------------
   *             Reading the first row (times and transects)
   */
  /* B E G I N : ---------------------------------------------------------------------
   *             Reading Presence/Absence values on a per row basis
   */
  n=0;
  while ( fscanf(fp, "%s\t", Name_Dummy ) != EOF ){
    strcpy(Species_Name[n], Name_Dummy); 

    for(j=0; j < N; j++) {
      if( j == (N - 1) ) fscanf(fp, "%lf\n", &y);
      else               fscanf(fp, "%lf\t", &y);

      assert( n < (*Species) );
      Presence_Data[n][j] = y;
    }
    n++;
  }
  (*Species) = n;
  /*     E N D : ---------------------------------------------------------------------
   *             Reading Presence/Absence values on a per row basis
   */
  fclose(fp);  
  
  printf(" A %d species File (%s)\n", (*Species), File_Name); 
  printf(" with %d sampling times (No_of_TIMES) has been read successfully\n", 
	 (*No_of_TIMES) );
  printf(" [Exiting function Reading_MacKenzie_Generic_Matrix_from_File(...)]\n\n");

  free(Name_Dummy); free(Vector);
}

void Reading_MacKenzie_Generic_Matrix_nFactors_from_File(  char * File_Name,
							   int nFactors,
							   double ** Presence_Data, 
							   char ** Species_Name,
							   int * Species, 
							   double * Time_Vector,
							   int * Transects, 
							   int * No_of_TIMES )
{
  /* This function works the same as before, but it is even better because, while reading 
     the file, it discounts a number of 'nFactors' factor columns, and still counts the 
     number of species (rows), the number of sampling times, and the number of transects 
     per sampling time. Unlike the function above, this function here
     does not need to know this information to correctly read the file, but the number, 
     'nFactors', of factor columns should be given as an input argument 

     Input parameters: 
     . * Species: Pointer to Number of Species (also given as an output) 
     . * No_of_TIMES: Number of Sampling Times
     . nFactors: number of factor columns (non-numeric, but qualitative variables)

     Output
     . * Species: number of species read from file 
     . * No_of_TIMES: number of sampling times.
     . Species__Name[][]: Species Names
     . Time_Vector[]: a double array containing sampling times
     . Transects[] an integer array containing number of transects per sampling time.
     . Reading the matrix into Presence_Data[][]. 

     Note: Presence_Data, Species_Name, Transects, and Time_Vector should have been 
     correctly dimensionalized in the parent code that calls this function. 
       
     Species Name  F1 ... Fn t0 t0 t0 t1 t1 t1 t2 t2 t2 ... ... ... tn tn tn
                   -- ... -- -- -- -- -- -- -- -- -- -- --- --- --- -- -- --
       Sp_0        A  ... a  1  0  0  0  0  1  1  1  0  ... ... ... 1  1  0 
       Sp_1        B  ... a  1  0  0  0  0  1  0  0  1  ... ... ... 1  1  0 
        .          .                                                .  .  . 
        .          .                                                .  .  . 
        .          .                                                .  .  . 

  */
  int i,j,n, m,nt, N;
  double y; 
  char * Name_Dummy = (char *)calloc( 50, sizeof(char) );
  int N_MAX = No_of_TIME_OBS_MAX; // Maximum number of temporal observations 
                                  // (total temporal columns in the data matrix)
                                  // (see MODEL.h)
  double * Vector = (double *)calloc( N_MAX, sizeof(double) );

  FILE * fp; 
  printf("\n [Entering function Reading_MacKenzie_Generic_Matrix_nFactors_from_File(...)]\n");
  printf(" Reading File %s...\n", File_Name); 
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    error(0,0,"Program aborted");
  } 
  /* B E G I N : ---------------------------------------------------------------------
   *             Reading the first row (times and transects)
   */
  for(i=0; i<= nFactors; i++) fscanf(fp, "%s\t", Name_Dummy );
  
  int End_of_Line   = '\n';  
  int Tab_Separator = '\t';
  printf("End of Line: %d\t Tab Separator: %d\n", End_of_Line, Tab_Separator);
  
  int ch = Tab_Separator;
  n=0;
  while( ch != End_of_Line  ) {
         fscanf(fp, "%lf", &y);
         ch  = getc( fp );
	 // printf("Vector[%d] = %g\tch: %d\n", n, y, ch);
         if (n < N_MAX) { Vector[n++] = y; }
 	 else { printf("Too many time columns reading file %s\n", File_Name);  exit(0);} 
	 // getchar();
  }
  N  = n; //  Actual number of temporal observations 
          // (total number of time columns in the data matrix)  

  nt = 0;
  m  = 0;
  n  = 0;
  y=Vector[0];
  while (n < N) {
   if( Vector[n] == y ){
     Time_Vector[m] = y;
     nt++;
     n++;
   }
   else {
     y = Vector[n];
     Transects[m++] = nt;
     nt = 0;
   }
  }
  Transects[m] = nt;
  (* No_of_TIMES) = 1 + m;
  /*     E N D : ---------------------------------------------------------------------
   *             Reading the first row (times and transects)
   */
  /* B E G I N : ---------------------------------------------------------------------
   *             Reading Presence/Absence values on a per row basis
   */
  n=0;
  int End_of_File = 0; 
  while ( End_of_File != EOF ){

    End_of_File = fscanf(fp, "%s\t", Name_Dummy );

    if( End_of_File != EOF ) {
    
      strcpy(Species_Name[n], Name_Dummy);

      // printf("Species: %s(%d-th):\t", Species_Name[n], n); 
      
      for(i=0; i< nFactors; i++) End_of_File = fscanf(fp, "%s\t", Name_Dummy ); 
      
      for(j=0; j < N; j++) {
	if( j == (N - 1) ) fscanf(fp, "%lf\n", &y);
	else               fscanf(fp, "%lf\t", &y);
	
	assert( n < (*Species) );
	
	Presence_Data[n][j] = y;
	
	// printf("Time = %g\t%g;", Vector[j], y); 
	
      }
      // printf("\n"); // getchar();

      n++;
    }
  }
  (*Species) = n;
  /*     E N D : ---------------------------------------------------------------------
   *             Reading Presence/Absence values on a per row basis
   */
  fclose(fp);  
  
  printf(" A %d species File (%s)\n", (*Species), File_Name); 
  printf(" with %d sampling times (No_of_TIMES) has been read successfully\n", 
	 (*No_of_TIMES) );
  printf(" [Exiting function Reading_MacKenzie_Generic_Matrix_from_File(...)]\n\n");

  free(Name_Dummy); free(Vector);
}
