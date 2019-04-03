void IO_Filtering_Out_Missing_Values_Structure ( int No_of_SPECIES,  
						 double *** Presence, int * No_of_SITES, 
						 int **** Structure, 
						 double ** Time_Vector, 
						 int * No_of_TIMES, 
						 double *** Sp_Time, 
						 int ** No_of_Sp_Times, 
						 double MISSING_VALUE_FLAG ); 

void IO_Filtering_Out_Structure( double ** Presence, int * No_of_SPECIES,  
				 int *** Structure,
				 double * Time, int No_of_TIMES,    
				 double ** Sp_Time, int * No_of_Sp_Times, 
				 double MISSING_VALUE_FLAG );


void IO_Filtering_Out_Missing_Values ( int No_of_SPECIES,  
				       double *** Presence, int * No_of_SITES, 
				       double ** Time_Vector, int * No_of_TIMES, 
				       double *** Sp_Time, int ** No_of_Sp_Times , 
				       double MISSING_VALUE_FLAG );

void IO_Filtering_Out_Matrix( double ** Presence, int * No_of_SPECIES,  
			      double * Time, int No_of_TIMES,    
			      double ** Sp_Time, int * No_of_Sp_Times, 
			      double MISSING_VALUE_FLAG );

void Reading_Standard_Data_Matrix_from_File( char * File_Name,  
					     double ** Presence__Data, 
					     char ** Species_Name,
					     int * Species, 
					     int No_of_Times, 
					     double * Time_Vector );

void Writing_Standard_Data_Matrix(double ** Presence__Data, 
				  char ** Species_Name,
				  double * Time_Vector,
				  int N_row, int N_column);


void Writing_Standard_Data_Matrix_to_File(  char * File_Name, 
					    double ** Presence__Data, 
					    char ** Species_Name,
					    double * Time_Vector,
					    int N_row, int N_column);

void Writing_Species_Distribution_over_Replicates_to_File (char * XYZ_File_NAME, 
						   double ** Variable, 
						   int REPLICATES, 
						   double * Time_Vector, 
						   int I_Time,
						   int No_of_SPECIES);
