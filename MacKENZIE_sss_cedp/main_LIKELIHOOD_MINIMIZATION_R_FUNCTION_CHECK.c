/*
    This code reads  MacKenzie Data files, which structure is:

       species      t0 t0 t0 t1 t1 t1 t2 t2 t2 ... ... ... tn tn tn
                    -- -- -- -- -- -- -- -- -- --- --- --- -- -- --
       Sp_0	     0  0  1  0  0  0  0  1  1  ... ... ... 1  1  0
       Sp_1	     1	0  1  0  0  0  0  1  0  ... ... ... 1  1  0
	.            .                                            .
	.	     .                                            .
	.	     .                                            .

   Then, the code evaluates the NLL of the simplest stochastic model underlying MacArthur and
   Wilson IBT (1963) for given model parameter values. Imperfect detectability is taken
   into account (MacKenzie, 2003). Model parameters are colonization, extinction and
   detectability. These parameters can be introduced as command line arguments.

   Compilation:

   ~$  make TYPE_of_MAIN=LIKELIHOOD_MINIMIZATION_R_FUNCTION_CHECK CPG=NON_CPGPLOT RSH=R_SHLIB 

   Execution call:

   ~$ ./SSS_CEDP -pC 0.1 -pE 0.1 -pD 0.5

   Valgrind execution: 

   ~$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt  ./SSS_CEDP -pC 0.1 -pE 0.1 -pD 0.5
*/

#include <MODEL.h>

#include <IO_Procedures_Standard.h>
#include <IO_Procedures_MacKenzie.h>
#include <IO_Procedures_Laccadives.h>

#include "global.h"

#define VERBOSE

/* The main code below acts, effectively, as a wrapper of the following function,
   which does all the work. It is devised as a check for this function.
*/
void R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization(double * , int * , int * ,
                                                       double * , int * ,
                                                       int * ,
                                                       double * , double * ,
                                                       double * , double * ,
                                                       double * , double * ,
                                                       double * , double * ,
                                                       int * ,
                                                       int * ,
                                                       int * , int * ,
                                                       double * ,
                                                       int * ,
                                                       double * ,
                                                       int *, int * );
void ArgumentControl(int argc, char **argv);

int main(int argc, char **argv)
{
  int i,j,k,l,s, m,n;
  char * p;
  int  Verbose;
  int Minimization;

  #include "default.c"

 /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  /* B E G I N: Reserving memory ---------------------- */
  int No_of_DATA_FILES; No_of_DATA_FILES = 3;
  char ** File_Name = (char **)calloc(No_of_DATA_FILES, sizeof(char *) );
  for (i=0; i<No_of_DATA_FILES; i++) File_Name[i] = (char *)calloc(100, sizeof(char) );

  File_Name[0][0]='\0';  p = strcat(File_Name[0], "MacKenzie_Data_Matrix_0.dat");
  File_Name[1][0]='\0';  p = strcat(File_Name[1], "MacKenzie_Data_Matrix_1.dat");
  File_Name[2][0]='\0';  p = strcat(File_Name[2], "MacKenzie_Data_Matrix_2.dat");

  int * No_of_SP = (int *)calloc( No_of_DATA_FILES, sizeof(int) );
  int * No_of_SAMPLING_TIMES = (int *)calloc( No_of_DATA_FILES, sizeof(int) );

  for( i=0; i<No_of_DATA_FILES; i++ ){
    No_of_SAMPLING_TIMES[i] = No_of_TIME_OBS_MAX;
    No_of_SP[i] = No_of_SPECIES_MAX;
  }

  char *** Species_Name = (char ***)calloc(No_of_DATA_FILES, sizeof(char **));
  for( i=0; i<No_of_DATA_FILES; i++ ){
    Species_Name[i] = (char **)calloc(No_of_SPECIES_MAX, sizeof(char *));
    for (j=0; j<No_of_SPECIES_MAX; j++){
      Species_Name[i][j] = (char *)calloc( 100, sizeof( char ) );
    }
  }
  double *** Presence = (double ***)calloc(No_of_DATA_FILES, sizeof(double **));
  for( i=0; i<No_of_DATA_FILES; i++ ){
    Presence[i] = (double **)calloc(No_of_SPECIES_MAX, sizeof(double *));
    for (j=0; j<No_of_SPECIES_MAX; j++){
      Presence[i][j] = (double *)calloc(No_of_SAMPLING_TIMES[i],
					sizeof(double ));
    }
  }
  double ** Time_Vector = (double **)calloc(No_of_DATA_FILES,  sizeof(double *));
  for( i=0; i<No_of_DATA_FILES; i++ ){
    Time_Vector[i] = (double *)calloc(No_of_SAMPLING_TIMES[i],
				      sizeof(double ));
  }
  int ** Transects = (int **)calloc(No_of_DATA_FILES,
                                            sizeof(int *));
  for( i=0; i<No_of_DATA_FILES; i++ ){
    Transects[i] = (int *)calloc(No_of_SAMPLING_TIMES[i],
                                      sizeof(int ));
  }

  double * Colonization = (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * Extinction   = (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * Detectability= (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  double * Phi_Time_0   = (double *)calloc( No_of_DATA_FILES, sizeof(double ));

  double * NLL_Value = (double *)calloc( No_of_DATA_FILES, sizeof(double ));
  /*     E N D: Reserving memory ---------------------- */

  /* B E G I N : Reading File (see IO_Procedures_MacKenzie.c in ./Library) */
  int Species;
  for( i=0; i<No_of_DATA_FILES; i++ ){

    Reading_MacKenzie_Generic_Matrix_from_File( File_Name[i],
                                                Presence[i],
                                                Species_Name[i], &No_of_SP[i],
                                                Time_Vector[i], Transects[i],
                                                &No_of_SAMPLING_TIMES[i] );

    /* Reading_MacKenzie_Generic_Matrix_nFactors_from_File( File_Name[i], 2,               */
    /* 							    Presence[i],                   */
    /* 							    Species_Name[i], &No_of_SP[i], */
    /* 							    Time_Vector[i], Transects[i],  */
    /* 							    &No_of_SAMPLING_TIMES[i] );    */

    printf(" Number of Species (File %d): %d\n", i, No_of_SP[i] );
    printf(" Sampling Times:\t{ ");
    for(j=0; j<No_of_SAMPLING_TIMES[i]; j++)
      printf("%g (%d)  ", Time_Vector[i][j], Transects[i][j]);
    printf(" }\n");
    for(j=0; j<No_of_SP[i]; j++) {
      m = 0;
      printf(" { ");
      for(k=0; k<No_of_SAMPLING_TIMES[i]; k++)
	for(n=0; n<Transects[i][k]; n++) printf("%g ", Presence[i][j][m++]);
      printf(" }\n");
    }
    printf("\n\n");

    // getchar();
  }
  /*     E N D : --------------------------------------------------------*/
  int * Index = (int *)calloc( MODEL_PARAMETERS_MAXIMUM, sizeof(int));
  Index[0] = I0; Index[1] = I1; Index[2] = I2; Index[3] = I3;
  int * Discretization = (int *)calloc( MODEL_PARAMETERS_MAXIMUM, sizeof(int));
  Discretization[0]=d0; Discretization[1]=d1; Discretization[2]=d2; Discretization[3]=d3;

  /* B E G I N : Defining the boundaries of the parameter space through
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
  /* B E G I N : NLLikelihood Minimization -----------------------------------------*/
  Verbose = 1;  Minimization = 1;
  int  No_of_PARAMETERS_MAX = MODEL_PARAMETERS_MAXIMUM;
  FILE * fp = fopen("Colonization_Extinction_Detectability.dat","w");
  for( i=0; i<No_of_DATA_FILES; i++ ){

    /* Seeding the minimization procedure
       with initial parameter values */
    Colonization[i]  = Colonization_Rate;
    Extinction[i]    = Extinction_Rate;
    Detectability[i] = Detectability_Value;
    Phi_Time_0[i]    = Phi_0;

    int N = 0;
    for( j=0; j<No_of_SAMPLING_TIMES[i]; j++ ) 	N+=Transects[i][j];

    double * Data = (double *)calloc( No_of_SP[i] * N, sizeof(double) );
    k = 0;
    for( m=0; m < No_of_SP[i]; m++ )
      for( j=0; j < N; j++ ) Data[k++] = Presence[i][m][j];

    R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization(Data, &No_of_SP[i], &N,
						      Time_Vector[i], Transects[i],
						      &No_of_SAMPLING_TIMES[i],
						      &Colonization[i],  Par_Range[0],
						      &Extinction[i],    Par_Range[1],
						      &Detectability[i], Par_Range[2],
						      &Phi_Time_0[i],    Par_Range[3],
						      &No_of_PARAMETERS,
						      &No_of_PARAMETERS_MAX,
						      Index, Discretization,
						      &TOLERANCE,
						      &MAX_No_of_ITERATIONS,
						      &NLL_Value[i],
						      &Verbose,
						      &Minimization );
    fprintf(fp, " Negative loglikelihood (File %d): ", i);
    fprintf(fp, " NLL( Data | C=%g, E=%g, D=%g, P_0=%g ) = %g\n",
	    Colonization[i], Extinction[i], Detectability_Value, Phi_Time_0[i],
	    NLL_Value[i] );

    free(Data);
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
  free(NLL_Value); free(Colonization); free(Extinction); free(Detectability); free(Phi_Time_0);
  free(Index); free(Discretization);
  for(i=0; i<MODEL_PARAMETERS_MAXIMUM; i++) free(Par_Range[i]);
  free(Par_Range);
  free(MAX_P); free(min_P);

  for( i=0; i<No_of_DATA_FILES; i++ ){
    for (j=0; j<No_of_SPECIES_MAX; j++) free( Presence[i][j] );
    free( Presence[i] );
  }
  free(Presence);
  for( i=0; i<No_of_DATA_FILES; i++ ){
    for (j=0; j<No_of_SPECIES_MAX; j++) free( Species_Name[i][j] );
    free( Species_Name[i] );
  }
  free(Species_Name);
  for( i=0; i<No_of_DATA_FILES; i++ ) {free (Time_Vector[i]); free (Transects[i]);}
  free(Time_Vector); free(Transects);
  free(No_of_SP); free(No_of_SAMPLING_TIMES);
  for (i=0; i<No_of_DATA_FILES; i++) free(File_Name[i]);
  free(File_Name);

  #include <include.Parameter_Model.default.free.c>
  /*   END: ---------------------------------------- */

  printf("\nEnd of progam\n");
  return(0);
}
