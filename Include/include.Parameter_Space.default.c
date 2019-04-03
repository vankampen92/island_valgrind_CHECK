 No_of_PARAMETERS = MODEL_PARAMETERS_MAXIMUM; /* No of parameters defining the actual dimension of 
			                         the subparameter space */

 I0 = 0;            /* P->Colonization_Rate = Colonization_Rate; */ 
 d0 = 100;              // No of dicrete values 
 MAX_P0 = 2.0;          // Maximum value of the subparameter range
 min_P0 = 0.0;          // Minimum value of the subparameter range 
 Acc_P0 = 0.1;

 I1 = 1;            /* P->Exticntion_Rate   = Extinction_Rate;   */       
 d1 = 100; 
 MAX_P1 = 2.0;
 min_P1 = 0.0;
 Acc_P1 = 0.1;
 
 I2 = 2;            /* P->Detectability_Value = Detectability_Value */ 
 d2 = 100;              // No of dicrete values 
 MAX_P2 = 0.99;         // Maximum value of the subparameter range
 min_P2 = 0.01;         // Minimum value of the subparameter range 
 Acc_P2 = 0.01;

 I3 = 3;            /* P->Phi_0   = Phi_0;   */       
 d3 = 100; 
 MAX_P3 = 0.99;
 min_P3 = 0.01;
 Acc_P3 = 0.01;

 TOLERANCE = 1.0E-3;
 MAX_No_of_ITERATIONS = 100; 



