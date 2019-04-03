#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <time.h>
#include <assert.h>
#include <limits.h>

typedef struct SP_Matrix_Datainfo
{
  /* * * Model Parameters  * * */
  int No_of_SITES;           // Sites: Number of rows of the presence matrix            
  int No_of_TIMES;           // No of sampling times: Number of columns
  double ** Presence;                           
  double * Time_Vector;
  char * Name;              // Name of the species/guild/Phylum stored in each actual
                            // data structure
}SP_Matrix_Data;

void SP_Matrix_Data_Alloc( int No_of_SITES, int No_of_TIMES, 
			   SP_Matrix_Data * D)
{
  int j;

  // SP_Matrix_Data * D = (SP_Matrix_Data *)calloc( 1, sizeof(SP_Matrix_Data) );

  D->Presence = (double **)calloc(No_of_SITES, sizeof(double *));
  for (j=0; j<No_of_SITES; j++)
      D->Presence[j] = (double *)calloc(No_of_TIMES, sizeof(double ));

  D->Time_Vector = (double *)calloc(No_of_TIMES, sizeof(double));
  
  D->Name = (char *)calloc(50, sizeof(char) );

  // return(D);
}

void SP_Matrix_Data_Free( SP_Matrix_Data * D)
{
  int j;

  for (j=0; j<D->No_of_SITES; j++) free( D->Presence[j] );
  free( D->Presence );
  
  free (D->Time_Vector);

  free(D->Name); 
  
  free (D);
}

void SP_Matrix_Data_Setup(int No_of_SITES, int No_of_COLUMNS,
			  SP_Matrix_Data * D, double ** Presence,
			  double * Time_Vector, char * Sp_Name )
{
  int i,j;
  char * p;
  
  D->No_of_SITES = No_of_SITES;   // Sites: Number of rows of the presence matrix
  D->No_of_TIMES = No_of_COLUMNS;

  for (i=0; i<No_of_SITES; i++){
    for (j=0; j<No_of_COLUMNS; j++) {
      D->Presence[i][j] = Presence[i][j];
    }
  }

  for (j=0; j<No_of_COLUMNS; j++) D->Time_Vector[j] = Time_Vector[j];

  D->Name[0]='\0';
  p = strcat( D->Name, Sp_Name );
  // memcpy( D->Name, Sp_Name, strlen(Sp_Name)+1 );
}

void SP_Matrix_Data_Write( SP_Matrix_Data * D )
{
  
  int j,n;

  printf("Data Matrix: %s\n", D->Name); 
  printf("\n\n");
  printf(" No of Sampling Times = %d\t Times = {", D->No_of_TIMES); 
  for(j = 0; j<D->No_of_TIMES; j++)
    printf(" %g ", D->Time_Vector[j] ); 
  printf("}\n");

  for(j=0; j<D->No_of_SITES; j++) {
    printf("\n{");
    for(n=0; n<D->No_of_TIMES; n++) printf("%g ", D->Presence[j][n]);
    printf("}\n");
  }
  printf("\n\n");

}

int main()
{
  int i,j;
  int No_of_SPECIES = 3; 
  int No_of_SITES = 10;
  int No_of_TIMES = 5;
  
  char * N = (char *)calloc(50, sizeof(char) );
  char ** Names = (char **)calloc(No_of_SPECIES, sizeof(char *) );

  for(i=0; i<No_of_SPECIES; i++){
    Names[i] = (char *)calloc(50, sizeof(char ));
    strcat(Names[i], "Species_");
    sprintf(N, "%d", i);
    strcat(Names[i], N);
  }

  double * Time = (double *)calloc(No_of_TIMES, sizeof(double) );
  double ** Presence = (double **)calloc(No_of_SITES, sizeof(double *) );
  for(i=0; i<No_of_SITES; i++)
    Presence[i] = (double *)calloc(No_of_TIMES, sizeof(double) );

  for(i=0; i<No_of_SITES; i++)
    for(j=0; j<No_of_TIMES; j++){
      Time[j] = (double)j;
      Presence[i][j] = (double)(10 * i + j);
    }
  
  SP_Matrix_Data ** Data = (SP_Matrix_Data **)calloc( No_of_SPECIES, sizeof(SP_Matrix_Data *) );

  for(i=0; i<No_of_SPECIES; i++){
    Data[i] = (SP_Matrix_Data *)calloc( 1, sizeof(SP_Matrix_Data) );
    SP_Matrix_Data_Alloc( No_of_SITES, No_of_TIMES, Data[i]);
    SP_Matrix_Data_Setup( No_of_SITES, No_of_TIMES, Data[i],
			  Presence, Time, Names[i]);
    SP_Matrix_Data_Write( Data[i] );
  }
  
  for( i=0; i<No_of_SPECIES; i++ ) SP_Matrix_Data_Free( Data[i] );
  free (Data);

  for(i=0; i<No_of_SPECIES; i++) free (Names[i]); 
  free(Names); 

  free(N);

  free(Time);
  for(i=0; i<No_of_SITES; i++) free(Presence[i]); 
  free(Presence); 
  
  return(0); 
}
