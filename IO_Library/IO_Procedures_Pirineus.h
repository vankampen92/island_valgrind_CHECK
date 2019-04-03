void READ_FILES_ZOOPLANCTON_PIRINEUS ( int No_of_SPECIES,  
				       double *** Presence, int * No_of_SITES, 
				       double ** Time_Vector, int * No_of_SAMPLING_TIMES );
				       
void IO_Procedures_Pirineus( double ** Presence, int * No_of_SPECIES,  
			     double * Time, int No_of_TIMES,    
			     double ** Sp_Time, int * No_of_Sp_Times );

void  zooplancton_Pirineus_File_Name_Creator_15SP(char ** Name); 

void zooplancton_Pirineus_Species_Tag_Creator_15SP( char ** Name );

void Build_in_EV_AREA_Lakes_Pyrenees( double **** EV, int , int , 
				      int * , 
				      int * ); 
