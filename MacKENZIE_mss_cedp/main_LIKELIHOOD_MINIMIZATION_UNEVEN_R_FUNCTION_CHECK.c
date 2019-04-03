/*
    This code reads  MacKenzie Data files, which structure is:

       species      t0 t0 t0 t1 t1 t1 t2 t2 t2 ... ... ... tn tn tn
                    -- -- -- -- -- -- -- -- -- --- --- --- -- -- --
       Sp_0	     0  0  1  0  0  0  0  1  1  ... ... ... 1  1  0
       Sp_1	     1	0  1  0  0  0  0  1  0  ... ... ... 1  1  0                   .

   Then, the code evaluates the NLL of the simplest stochastic model underlying MacArthur and
   Wilson IBT (1963) for given model parameter values. Imperfect detectability is taken
   into account (MacKenzie, 2003). Model parameters are colonization, extinction and
   detectability, and probability of iniitial presence. These parameters can be introduced as command line arguments.

   Compilation:

   $  make CPG=NON_CPGPLOT RSH=R_SHLIB

   Compilation (CPGPLOT):

   Execution call:

   $ ./MSS_CEDP -pC 0.1 -pE 0.1 -pD 0.5

   Valgrind execution: 

   $ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt  ./MSS_CEDP -pC 0.1 -pE 0.1 -pD 0.5
*/
#include <MODEL.h>

#include <IO_Procedures_Standard.h>
#include <IO_Procedures_MacKenzie.h>
#include <IO_Procedures_Laccadives.h>

#include "global.h"

#define VERBOSE

/* ATOLLS and GUILDS could NOT be defined at the same time. Please comment out
 * consistently!!!
 */
#define ATOLLS
// #define GUILDS

/* The main code below acts, effectively, as a wrapper of the following function,
   which does all the work
*/
void R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization ( int * pNo_of_SPECIES,
						       char ** Species_Tag,
						       double * R_Presence,
						       int * No_of_SITES,
						       double * R_Time_Vector,
						       int * No_of_TIMES,
						       double * MISSING_VALUE_FLAG,
						       double * Colonization_Rate,
						       double * C_Range,
						       double * Extinction_Rate,
						       double * E_Range,
						       double * Detectability,
						       double * D_Range,
						       double * Phi_Time_0,
						       double * P_Range,
						       int * No_of_PARAMETERS,
						       int * No_of_PARAMETERS_MAX,
						       int * Index,
						       int * Discretization,
						       double * Tolerance,
						       int * No_of_ITERATIONS,
						       int * Verbose,
						       int * Minimization,
						       double * R_Results );

void ArgumentControl(int argc, char **argv);

int main(int argc, char **argv)
{
  int i,j,k,l,s, m,n;
  char * p;

  #include "default.c"

 /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  /* B E G I N: Reserving memory ---------------------- */
#if defined ATOLLS
  int No_of_DATA_FILES; No_of_DATA_FILES = 3;  // 3 ATOLLS
#endif
#if defined GUILDS
  int No_of_DATA_FILES; No_of_DATA_FILES = 7;  // 7 GUILDS
#endif
  char ** File_Name = (char **)calloc(No_of_DATA_FILES, sizeof(char *) );
  for (i=0; i<No_of_DATA_FILES; i++) File_Name[i] = (char *)calloc(100, sizeof(char) );

  File_Name[0][0]='\0';  p = strcat(File_Name[0], "MacKenzie_Data_Matrix_0.dat");
  File_Name[1][0]='\0';  p = strcat(File_Name[1], "MacKenzie_Data_Matrix_1.dat");
  File_Name[2][0]='\0';  p = strcat(File_Name[2], "MacKenzie_Data_Matrix_2.dat");
  // File_Name[3][0]='\0';  p = strcat(File_Name[3], "MacKenzie_Data_Matrix_3.dat");
  // File_Name[4][0]='\0';  p = strcat(File_Name[4], "MacKenzie_Data_Matrix_4.dat");

  double *** Presence = (double ***)calloc(No_of_DATA_FILES, sizeof(double **));
  int * No_of_SAMPLING_TIMES = (int *)calloc(No_of_DATA_FILES, sizeof(int) );
  int * TOTAL_No_of_TRANSECTS = (int *)calloc(No_of_DATA_FILES, sizeof(int) );
  int * No_of_SITES = (int *)calloc(No_of_DATA_FILES, sizeof(int) );
  double ** Time_Vector = (double **)calloc(No_of_DATA_FILES, sizeof(double *));
  double ** Time_Vector_Long = (double **)calloc(No_of_DATA_FILES, sizeof(double *));
  int    ** Transects   = (int **)calloc(No_of_DATA_FILES, sizeof(int *));
  for( i=0; i<No_of_DATA_FILES; i++ ){
    No_of_SAMPLING_TIMES[i] = No_of_TIME_OBS_MAX;
    No_of_SITES[i]          = No_of_SPECIES_MAX;
    Time_Vector[i] = (double *)calloc(No_of_SAMPLING_TIMES[i], sizeof(double));
    Time_Vector_Long[i] = (double *)calloc(No_of_SAMPLING_TIMES[i], sizeof(double));
    Transects[i]   = (int    *)calloc(No_of_SAMPLING_TIMES[i], sizeof(   int));

    Presence[i] = (double **)calloc(No_of_SITES[i], sizeof(double *));
    for (j=0; j<No_of_SITES[i]; j++)
      Presence[i][j] = (double *)calloc(No_of_SAMPLING_TIMES[i], sizeof(double ));
  }

  char *** Species_Name = (char ***)calloc(No_of_DATA_FILES, sizeof(char **));
  for( i=0; i<No_of_DATA_FILES; i++ ){
    Species_Name[i] = (char **)calloc(No_of_SPECIES_MAX, sizeof(char *));
    for (j=0; j<No_of_SPECIES_MAX; j++){
      Species_Name[i][j] = (char *)calloc( 100, sizeof( char ) );
    }
  }

  double * Colonization = (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * Extinction   = (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * Detectability= (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * Phi_Time_0   = (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * NLL_Value = (double *)calloc( No_of_DATA_FILES, sizeof(double ));

	char ** Species_Tag = (char **)calloc( No_of_DATA_FILES, sizeof(char *) );
  for (i=0; i<No_of_DATA_FILES; i++)
    Species_Tag[i] = (char *)calloc(100, sizeof(char) );
#if defined ATOLLS
  p = strcat (Species_Tag[0], "Agatti");
  p = strcat (Species_Tag[1], "Kadmath");
  p = strcat (Species_Tag[2], "Kavratti"); // Three Atolls
#endif
#if defined GUILDS
  p = strcat (Species_Tag[0], "ALG");
  p = strcat (Species_Tag[1], "COL");
  p = strcat (Species_Tag[2], "MAC");
  p = strcat (Species_Tag[3], "MIC");
  p = strcat (Species_Tag[4], "OMN");
  p = strcat (Species_Tag[5], "PIC");
  p = strcat (Species_Tag[6], "ZOO");      // Seven Guilds
#endif
  /*     E N D: Reserving memory ---------------------- */

  /* B E G I N : Reading File (see IO_Procedures_MacKenzie.c in ./Library) */
  int Species;
  for( i=0; i<No_of_DATA_FILES; i++ ){

    Reading_MacKenzie_Generic_Matrix_nFactors_from_File( File_Name[i], 2,
							 Presence[i],
							 Species_Name[i], &No_of_SITES[i],
							 Time_Vector[i], Transects[i],
							 &No_of_SAMPLING_TIMES[i] );

    // Building Long Vector (with repetitions according the the no of transects)
    n=0;
    for(j=0; j<No_of_SAMPLING_TIMES[i]; j++)
      for(k=0; k<Transects[i][j]; k++)
			Time_Vector_Long[i][n++] = Time_Vector[i][j];
		TOTAL_No_of_TRANSECTS[i] = n;

    printf(" Number of Species (File %d): %d\n", i, No_of_SITES[i] );
    printf(" Sampling Times:\t{ ");
    for(j=0; j<No_of_SAMPLING_TIMES[i]; j++)
      printf("%g (%d)  ", Time_Vector[i][j], Transects[i][j]);
    printf(" }\n");
    for(j=0; j<No_of_SITES[i]; j++) {
      m = 0;
      printf(" { ");
      for(k=0; k<No_of_SAMPLING_TIMES[i]; k++)
			for(n=0; n<Transects[i][k]; n++) printf("%g ", Presence[i][j][m++]);
      printf(" }\n");
    }
    printf("\n\n");

    // getchar();
  }

  /* B E G I N : -------------------------------------------------------
     1. Transforming C arrys into R friendly arrays */
  int No, NT;
  No  = 0;
  NT  = 0;
  for(i=0; i<No_of_DATA_FILES; i++) {
    No += No_of_SITES[i] * TOTAL_No_of_TRANSECTS[i];
    NT += TOTAL_No_of_TRANSECTS[i];
  }
  double * R_Presence    = (double *)calloc( No, sizeof(double) );
  double * R_Time_Vector = (double *)calloc( NT, sizeof(double) );

  n=0;
  for(i=0; i<No_of_DATA_FILES; i++)
    for(j=0; j<TOTAL_No_of_TRANSECTS[i]; j++)
      R_Time_Vector[n++] = Time_Vector_Long[i][j];
  n=0;
  for(i=0; i<No_of_DATA_FILES; i++)
    for(j=0; j<No_of_SITES[i]; j++)
      for(k=0; k<TOTAL_No_of_TRANSECTS[i]; k++)
	R_Presence[n++] = Presence[i][j][k];

  double * Results = (double *)calloc( No_of_DATA_FILES * 5, sizeof(double) );
  /*     E N D : -------------------------------------------------------
   */
  /* B E G I N : -------------------------------------------------------
     2. Transforming input arguments defining model parameters and
     parameter space into R friendly pointers
  */
  int * Index = (int *)calloc( MODEL_PARAMETERS_MAXIMUM, sizeof(int));
  Index[0] = I0; Index[1] = I1; Index[2] = I2; Index[3] = I3;
  int * Discretization = (int *)calloc( MODEL_PARAMETERS_MAXIMUM, sizeof(int));
  Discretization[0]=d0; Discretization[1]=d1; Discretization[2]=d2; Discretization[3]=d3;

  /* Defining the boundaries of the parameter space through
	   min and MAX model parameter ranges. The parameter
		 search will be conducted within these boundaries.
		 Notice that these boundaries are controlled through
		 command line arguments. The command line argument list
		 should be carefully written.
  -----------------------------------------------------------------*/
  double ** Par_Range = (double **)calloc( MODEL_PARAMETERS_MAXIMUM, sizeof(double *) );
  for(i=0; i<MODEL_PARAMETERS_MAXIMUM; i++)
    Par_Range[i] = (double *)calloc( 2, sizeof(double) );
  Parameter_Model * MAX_P = (Parameter_Model *)calloc(1, sizeof(Parameter_Model) );
  Parameter_Model * min_P = (Parameter_Model *)calloc(1, sizeof(Parameter_Model) );
  Vector_Entry_into_Parameter_Model ( MAX_P0, Index[0], MAX_P );
  Vector_Entry_into_Parameter_Model ( MAX_P1, Index[1], MAX_P );
  Vector_Entry_into_Parameter_Model ( MAX_P2, Index[2], MAX_P );
  Vector_Entry_into_Parameter_Model ( MAX_P3, Index[3], MAX_P );
  Vector_Entry_into_Parameter_Model ( min_P0, Index[0], min_P );
  Vector_Entry_into_Parameter_Model ( min_P1, Index[1], min_P );
  Vector_Entry_into_Parameter_Model ( min_P2, Index[2], min_P );
  Vector_Entry_into_Parameter_Model ( min_P3, Index[3], min_P );

  printf(" Parameter Space Boundaries:\tDimension: %d\n", MODEL_PARAMETERS_MAXIMUM);
  for(i=0; i<MODEL_PARAMETERS_MAXIMUM; i++) {
    Par_Range[i][1] = Parameter_Model_into_Vector_Entry (i, MAX_P);
    Par_Range[i][0] = Parameter_Model_into_Vector_Entry (i, min_P);
    printf(" ---> Parameter Key %d: [%s_0 = %g, %s_1 = %g]\n",
	    i, Symbol[i], Par_Range[i][0], Symbol[i], Par_Range[i][1]);
  }
  /*    E N D : ---------------------------------------------------*/
  // getchar();

  int Verbose, Minimization;
#if defined VERBOSE
  Verbose = 1;
#else
  Verbose = 0;
#endif
  Minimization = 1;
  /* B E G I N : NLLikelihood Minimization -----------------------------------------*/
  int  No_of_PARAMETERS_MAX = MODEL_PARAMETERS_MAXIMUM;
  double MISSING_VALUE_FLAG = 0.1;
  R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization(&No_of_DATA_FILES,
		                                              Species_Tag,
																									R_Presence, No_of_SITES,
																									R_Time_Vector, TOTAL_No_of_TRANSECTS,
																									&MISSING_VALUE_FLAG,
																									&Colonization_Rate, Par_Range[0],
																									&Extinction_Rate, Par_Range[1],
																									&Detectability_Value, Par_Range[2],
																									&Phi_0, Par_Range[3],
																									&No_of_PARAMETERS,
																									&No_of_PARAMETERS_MAX,
																									Index, Discretization,
																									&TOLERANCE,
																									&MAX_No_of_ITERATIONS,
																									&Verbose,
																									&Minimization,
																									Results );

  FILE * fp = fopen("Colonization_Extinction_Detectability.dat","w");
  n=0;
  for(i=0; i<No_of_DATA_FILES; i++) {
    for(j=0; j<5; j++) {
      fprintf(fp, "%g\t", Results[n] );
      if(j%5 == 0) Colonization[i] = Results[n];
      if(j%5 == 1) Extinction[i] = Results[n];
      if(j%5 == 2) Detectability[i] = Results[n];
      if(j%5 == 3) Phi_Time_0[i] = Results[n];
      if(j%5 == 4) NLL_Value[i] = Results[n];
      n++;
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  /*     E N D : -------------------------------------------------------------------*/
  printf(" \n");
  printf(" Results (summary):\n");
  for( i=0; i<No_of_DATA_FILES; i++ ){
    printf(" Negative loglikelihood (File %d): ", i);
    printf(" NLL( Data | C=%g, E=%g, D=%g, P_0=%g ) = %g\n",
	   Colonization[i], Extinction[i], Detectability[i], Phi_Time_0[i],
	   NLL_Value[i] );
  }

  /* BEGIN: Freeing up memory ---------------------- */
  free(NLL_Value);
  free(Colonization); free(Extinction); free(Detectability); free(Phi_Time_0);
  free(Index); free(Discretization);
  for(i=0; i<MODEL_PARAMETERS_MAXIMUM; i++) free(Par_Range[i]);
  free(Par_Range);
  free(MAX_P); free(min_P);
  free(Results);

  for( i=0; i<No_of_DATA_FILES; i++ ){
    for (j=0; j<No_of_SPECIES_MAX; j++) free( Presence[i][j] );
    free( Presence[i] );
  }
  free(Presence);

  for( i=0; i<No_of_DATA_FILES; i++ ){
    free(Time_Vector[i]);
    free(Time_Vector_Long[i]);
    free(Transects[i]);

  }
  free( Time_Vector); free(Time_Vector_Long); free(Transects);
  free( No_of_SAMPLING_TIMES ); free(TOTAL_No_of_TRANSECTS);
  free( No_of_SITES );

  for( i=0; i<No_of_DATA_FILES; i++ ){
    for (j=0; j<No_of_SPECIES_MAX; j++) free( Species_Name[i][j] );
    free( Species_Name[i] );
  }
  free(Species_Name);

  for (i=0; i<No_of_DATA_FILES; i++) free(Species_Tag[i]);
  free(Species_Tag);

  for (i=0; i<No_of_DATA_FILES; i++) free(File_Name[i]);
  free(File_Name);

  free(R_Presence); free(R_Time_Vector);

  #include <include.Parameter_Model.default.free.c>
  /*   END: ---------------------------------------- */

  printf("\nEnd of progam\n");
  return(0);
}
