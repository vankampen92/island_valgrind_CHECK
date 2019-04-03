#include <HEADERS.h>
#include "IO_Procedures_Standard.h"
#include "IO_Procedures_Pirineus.h"

#define No_of_MATRIX_ROWS_MAX 10000

void READ_FILES_ZOOPLANCTON_PIRINEUS ( int No_of_SPECIES,  
				       double *** Presence, int * No_of_SITES, 
				       double ** Time_Vector, 
				       int * No_of_SAMPLING_TIMES )
{
  /*  A list of 'No_of_SPECIES' zooplanction species in the Pyrenees are read from 
      files. Data for each species are read from a different file and stored in 
      Presence matrices: Presence[i] is the matrix of i-th species. All files start
      with the same row:
      Species	1973 1974 1975 1976 1977 1987 1998 2000	2005 2006 2007 2008 2009 2010 2011 2012	2013
      ... 
      ... 
      and have the same number of columns. The total number of rows can change from 
      file to file. 

      Input arguments:
      . No_of_SPECIES, No of different files to be read
      . No_of_SAMPLING_TIMES[i], No of sampling times species i.

      Output arguments:
      . No_of_SITES[i], No of Rows species i
      . Time_Vector[i][], values of the sampling times of species i 
      . Presence[i][][], matrix Presence-Absence-Missed values of species i 
       
  */
  int i,j;
      assert( No_of_SPECIES == 15 ); 

      char ** Island_Name = (char **)calloc(No_of_SPECIES, sizeof(char *) );
      for (i=0; i<No_of_SPECIES; i++) Island_Name[i] = (char *)calloc(100, sizeof(char) );
      zooplancton_Pirineus_File_Name_Creator_15SP( Island_Name ) ;
      
      char *** Species_Name = (char ***)calloc(No_of_SPECIES, sizeof(char **));
      for( i=0; i<No_of_SPECIES; i++ ){
	Species_Name[i] = (char **)calloc(No_of_MATRIX_ROWS_MAX, sizeof(char *));
	for (j=0; j<No_of_MATRIX_ROWS_MAX; j++){
	  Species_Name[i][j] = (char *)calloc( 100, sizeof( char ) );
	}
      }
      
      /* B E G I N : Reading File (see IO_Procedures_Standard.c in ./Library) */
      int Species; 
      for( i=0; i<No_of_SPECIES; i++ ){
	
	Reading_Standard_Data_Matrix_from_File( Island_Name[i], 
						Presence[i], 
						Species_Name[i],
						&Species, 
						No_of_SAMPLING_TIMES[i], 
						Time_Vector[i] );
	assert( No_of_MATRIX_ROWS_MAX > Species );
	No_of_SITES[i] = Species;
	//printf(" Number of Sites (File %d): %d\n", i, No_of_SITES[i] );
	//printf(" Number of Sampling Times (File %d): %d\n", i, No_of_SAMPLING_TIMES[i] );
	//getchar();
      }
      /*     E N D :                                                          */
      for( i=0; i<No_of_SPECIES; i++ ){
	for (j=0; j<No_of_MATRIX_ROWS_MAX; j++) free( Species_Name[i][j] );
	free( Species_Name[i] );
      }
      free(Species_Name);
      
      for (i=0; i<No_of_SPECIES; i++) free(Island_Name[i]);
      free(Island_Name); 
}

void  zooplancton_Pirineus_File_Name_Creator_15SP(char ** Name)
  { 
  char * p;    
  // cyclopoidea (2): 
  Name[0][0]='\0';  p = strcat(Name[0], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/C.abyssorum-temps.csv");
  Name[1][0]='\0';  p = strcat(Name[1], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/A.vernalis-temps.csv");
  // calanoidea (4):
  Name[2][0]='\0';  p = strcat(Name[2], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/D.castaneti-temps.csv");
  Name[3][0]='\0';  p = strcat(Name[3], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/D.cyaneus-temps.csv");
  Name[4][0]='\0';  p = strcat(Name[4], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/E.vulgaris-temps.csv");
  Name[5][0]='\0';  p = strcat(Name[5], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/M.laciniatus-temps.csv");
  // branchiopoda (8):
  Name[6][0]='\0';  p = strcat(Name[6], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/D.longispina-temps.csv");
  Name[7][0]='\0';  p = strcat(Name[7], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/D.obtusa-temps.csv");
  Name[8][0]='\0';  p = strcat(Name[8], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/D.pulicaria-temps.csv");
  Name[9][0]='\0';  p = strcat(Name[9], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/C.quadrangula-temps.csv");
  Name[10][0]='\0';  p = strcat(Name[10], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/H.gibberum-temps.csv");
  Name[11][0]='\0';  p = strcat(Name[11], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/S.mucronata-temps.csv");
  Name[12][0]='\0';  p = strcat(Name[12], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/S.vetulus-temps.csv");
  Name[13][0]='\0';  p = strcat(Name[13], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/C.diaphanus-temps.csv");
  // amphipoda:
  Name[14][0]='\0';  p = strcat(Name[14], "/home/dalonso/PROJECT_ISLAND_BIOGEOGRAPHY/DATA_ZOOPLANCTON_PIRINEUS/G.lacustris-temps.csv");
  }  

void IO_Procedures_Pirineus( double ** Presence, int * No_of_SPECIES,
			     double * Time, int No_of_TIMES,
			     double ** Sp_Time, int * No_of_Sp_Times )
{
  /* This function calculates true time vectors and their true length.
     from a matrix Presence, which has a flag value (value 0.1) to mark
     those times that are missing. 
     
     This function is not generic, this is, it applies only to Pirineus
     data because, in those, the missing value flag is always 0.1. See 
     IO_Missing_Values.c to find the corresponding function which 
     incorporates a generic flag. 

     The output is a Sp_Time array that gives the specific time vector
     (Sp_Time) and its actual length (No_of_Sp_Times) for row of the
     initial matrix once missing values have been discounted.

     The function also counts the number of actual rows of the initial
     Presence matrix.

     Input arguments:
     . Presence[][]: presence/absence values (including missing values)
     . (* No_of_SPECIES) total number of rows in the input Presence
     matrix.
     . Time[]: sampling times corresponding to each column of the initial
     Presence matrix
     . No_of_TIMES: total number of columns of the input Presence matrix.
     
     Output arguments:
     . Sp_Time[i][j]: j-th sampling time associated to the i-th row
     once missing values in Presence has been excluded.
     . No_of_Sp_Times[i]; number of sampling times associated to the
     i-th row once missing values in Presence has been excluded.
     . (* No_of_SPECIES) total number of effective rows in the input
     Presence matrix for which there is, at least, two times with
     non-missing sampling times.
     . Presence[][] the output is the same as the initial matrix once
     deffective rows (those with only one sampled time) and missing values
     have been filtered out.
  */

  int i,j;
  int m,n;
  int S;
  int JUMPS;

  S = (* No_of_SPECIES);
  m = 0;
  for( i=0; i<S; i++) {
    
    JUMPS = 0;
    for( j=0; j<No_of_TIMES; j++ ) if( Presence[i][j] != 0.1 ) JUMPS++;
    
    n = 0;
    if( JUMPS > 1 ) {
      for( j=0; j<No_of_TIMES; j++ ) {
	if( Presence[i][j] != 0.1 ) {
	  Presence[m][n] = Presence[i][j];
	  Sp_Time[m][n]  = Time[j];
	  
	  assert(Presence[m][n] == 0.0 || Presence[m][n] == 1.0 );
	  
	  n++;
	}
      }
      No_of_Sp_Times[m] = n;
      if (n > 0) m++;
    }
  }
  
  (* No_of_SPECIES) = m;
}

void zooplancton_Pirineus_Species_Tag_Creator_15SP( char ** Name )
{ 
    char * p;
    // Cyclopoidea
    Name[0][0] = '\0'; p = strcat( Name[0], "Cab"); 
    Name[1][0] = '\0'; p = strcat( Name[1], "Ave");
    // Calanoidea 
    Name[2][0] = '\0'; p = strcat( Name[2], "Dca");
    Name[3][0] = '\0'; p = strcat( Name[3], "Dcy");
    Name[4][0] = '\0'; p = strcat( Name[4], "Evu");
    Name[5][0] = '\0'; p = strcat( Name[5], "Mla");
    // Branquiopoidea
    Name[6][0] = '\0'; p = strcat( Name[6], "Dlo");
    Name[7][0] = '\0'; p = strcat( Name[7], "Dob");
    Name[8][0] = '\0'; p = strcat( Name[8], "Dpu");
    Name[9][0] = '\0'; p = strcat( Name[9], "Cqu");
    Name[10][0] = '\0'; p = strcat( Name[10], "Hgi");
    Name[11][0] = '\0'; p = strcat( Name[11], "Smu");
    Name[12][0] = '\0'; p = strcat( Name[12], "Sve"); 
    Name[13][0] = '\0'; p = strcat( Name[13], "Cdi"); 
    // Amphipoidea
    Name[14][0] = '\0'; p = strcat( Name[14], "Gla"); 
}

void Build_in_EV_AREA_Lakes_Pyrenees( double **** EV, int No_of_SPECIES, 
				      int No_of_ENV_VAR, 
				      int * No_of_SITES, 
				      int * No_of_SAMPLING_TIMES )
{
  int i,j,k,l; 
  double x;
 
  assert( No_of_ENV_VAR == 1);

  // 404 is the overall number of lakes.
  //  17 is the overall number of sampling times. 
  double ** Area = (double **)calloc(404, sizeof(double *) );
  for(i=0; i<404; i++)
    Area[i] = (double *)calloc(17, sizeof(double) );

  // printf(" Environmental Variable Matrix (Lake Area):\n");
  FILE * fp = fopen("EV_AREA_LAKES.dat", "r");
  for(i=0; i<405; i++) {
    if(i == 0) 
      for(j=0; j<17; j++) fscanf(fp, "%lf\t", &x);
    else {  
      for(j=0; j<17; j++) {
	fscanf(fp, "%lf\t", &x);
	Area[i-1][j] = x;
	// printf("%g\t", Area[i-1][j]); 
      }
      fscanf(fp, "\n");
      // printf("\n");
    }
  }
  // getchar();

  for( i=0; i<No_of_SPECIES; i++ ) 
    for( j=0; j<No_of_ENV_VAR; j++)       
      for( k=0; k<No_of_SITES[i]; k++)
	for( l=0; l<No_of_SAMPLING_TIMES[i]; l++)
	  EV[i][j][k][l] = Area[k][l]; 
  
  for(i=0; i<404; i++) free(Area[i]); 
  free(Area); 
}

