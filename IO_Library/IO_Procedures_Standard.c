#include <HEADERS.h>
#include "IO_Procedures_Standard.h"

void Reading_Standard_Data_Matrix_from_File( char * File_Name,
					     double ** Presence__Data,
					     char ** Species_Name,
					     int * Species,
					     int No_of_Times,
					     double * Time_Vector )
{
  int n;
  int j;
  double y;
  char * Name_Dummy = (char *)calloc( 50, sizeof(char) );

  FILE * fp;
  printf("\n [Entering function Reading_Matrix_from_File(...)]\n");
  printf(" Reading File %s...\n", File_Name);
  if((fp=fopen(File_Name,"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    IO_ERROR(0,0,"Program aborted");
  }

  fscanf(fp, "%s\t", Name_Dummy );
  for(j=0; j < No_of_Times; j++) {
    if( j == (No_of_Times - 1) ) fscanf(fp, "%lf\n", &y);
    else                         fscanf(fp, "%lf\t", &y);
    Time_Vector[j] = y;
  }

  n=0;
  while ( fscanf(fp, "%s\t", Name_Dummy) != EOF ){
    strcpy(Species_Name[n], Name_Dummy);

    for(j=0; j < No_of_Times; j++) {
      if( j == (No_of_Times - 1) ) fscanf(fp, "%lf\n", &y);
      else                         fscanf(fp, "%lf\t", &y);
      Presence__Data[n][j] = y;
    }
    n++;
  }
  fclose(fp);
  (*Species) = n;

  printf(" File %s has been read successfully\n", File_Name);
  printf(" [Exiting function Reading_Matrix_from_File(...)]\n\n");

  free(Name_Dummy);
  // printf("Press any key to continue...\n"); getchar();
}

void Writing_Standard_Data_Matrix(double ** Presence__Data,
				  char ** Species_Name,
				  double * Time_Vector,
				  int N_row, int N_column)
{
  /* Input parameters:
     . N_row: Number of Species
     . N_column: Number of Sampling Times
     . Presence__Data[][]: Data
     . Species__Name[][]: Species Names
     . Time_Vector[]: a double array containing sampling times
  */
  int i,j;

  fprintf(stdout, "%s\t", "Species Name");
  for(j=0; j < N_column; j++) {
    fprintf(stdout, "%g\t", Time_Vector[j]);
  }
  fprintf(stdout, "\n");
  for(i=0; i < N_row; i++){
    fprintf(stdout, "%s\t", Species_Name[i] );

    for(j=0; j < N_column; j++) {
        fprintf(stdout, "%g\t", Presence__Data[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

void Writing_Standard_Data_Matrix_to_File(  char * File_Name,
					    double ** Presence__Data,
					    char ** Species_Name,
					    double * Time_Vector,
					    int N_row, int N_column)
{
  /* Input parameters:
     . N_row: Number of Species
     . N_column: Number of Sampling Times
     . Presence__Data[][]: Data
     . Species__Name[][]: Species Names
     . Time_Vector[]: a double array containing sampling times
  */
  int i,j;

  FILE * FP = fopen(File_Name, "w");
  fprintf(FP, "%s\t", "Species_Name");
  for(j=0; j < N_column; j++) {
    fprintf(FP, "%g\t", Time_Vector[j]);
  }
  fprintf(FP, "\n");
  for(i=0; i < N_row; i++){
    fprintf(FP, "%s\t", Species_Name[i] );

    for(j=0; j < N_column; j++) {
        fprintf(FP, "%g\t", Presence__Data[i][j]);
    }
    fprintf(FP, "\n");

  }
  fclose(FP);
}
    
