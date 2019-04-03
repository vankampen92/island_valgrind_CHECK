void Writing_Standard_Double_Matrix_to_File( char * File_Name,
                                    double ** Presence_Data,
                                    int N_row, int N_col );

void Writing_MacKenzie_Data_Matrix_to_File(  char * File_Name, 
					     double ** Presence_Data, 
					     char ** Species_Name, int N_row, 
					     double * Time_Vector, int * Transects, 
					     int No_of_TIMES);

void Reading_MacKenzie_Data_Matrix_from_File(  char * File_Name, 
					       double ** Presence_Data, 
					       char ** Species_Name, int * Species, 
					       double * Time_Vector, int * Transects, 
					       int No_of_TIMES );

void Reading_MacKenzie_Generic_Matrix_from_File( char * File_Name, 
						 double ** Presence_Data, 
						 char ** Species_Name, int * Species, 
						 double * Time_Vector, int * Transects, 
						 int * No_of_TIMES );

void Reading_MacKenzie_Generic_Matrix_nFactors_from_File( char * File_Name, int nFactors,
							  double ** Presence_Data, 
							  char ** Species_Name,
							  int * Species, 
							  double * Time_Vector,
							  int * Transects, 
							  int * No_of_TIMES );
