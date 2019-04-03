void Reading_Matrix_East_West_from_File(char * File_Name,  double ** Presence__Data, 
					char ** Species_Name,
					char ** Guild_Name, 
					int N_row, int N_column);

void Writing_Matrix_East_West(double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      int N_row, int N_column);

void Reading_Matrix_from_File_Header_True(char * File_Name,  double ** Presence__Data,
                                          double * Time, 
                                          char ** Species_Name,
                                          char ** Guild_Name,
                                          char ** Island_Name,
                                          int N_row, int N_column); 


void Reading_Matrix_from_File(char * File_Name,  double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      char ** Island_Name,
			      int N_row, int N_column);

void Writing_Matrix(double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      char ** Island_Name,
			      int N_row, int N_column);

void Writing_Matrix_to_File(  char * File_Name, 
			      double ** Presence__Data, 
			      char ** Species_Name,
			      char ** Guild_Name, 
			      char ** Island_Name,
			      int N_row, int N_column);

void Writing_Single_Matrix_East_West_to_File(  char * File_Name, 
					       double ** Presence__Data, 
					       char ** Species_Name,
					       char * Island_Name,
					       char * Site, 
					       char * Guild_Name, 
					       int N_row, int N_column);

void Writing_Single_Matrix_East_West(  double ** Presence__Data, 
				       char ** Species_Name,
				       char * Island_Name,
				       char * Site, 
				       char * Guild_Name, 
				       int N_row, int N_column);

void Reading_Single_Matrix_East_West_from_File(  char * File_Name, 
						 double ** Presence__Data, 
						 char ** Species_Name,
						 char * Island_Name,
						 char * Site, 
						 char * Guild_Name, 
						 int N_row, int N_column );

void Laccadive_File_Name_Creator (char ** Name, 
				  char ** Feeding_Strategy );

void Reading_Total_Matrix_Data ( char * FILE_NAME, int Sp, int Nc, 
				 double ** Total_Presence );

void Reading_Atoll_Feeding_Strategy_Data (double **** Presence_Data, 
					  int ** ROWS, int ** COLUMNS, 
					  char ** Name, char ** Feeding_Strategy );
