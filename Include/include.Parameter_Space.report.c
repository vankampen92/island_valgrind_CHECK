 printf(" Parameter Space Default Values:\n");

 printf(" -sP %d\t No of parameters defining the actual dimension of the subparameter space within which the search will be performed: %d\n", No_of_PARAMETERS, No_of_PARAMETERS);
 
 printf("-I0 0: Parameter Key (%s) 0: Colonization Rate\n", Symbol[0]); 
 printf(" [Parameter: 0]: -m0 %g -M0 %g -A0 %g -d0 %d\t [ min_Value[0] = %g, MAX_Value[0] = %g ]\t Accuracy[0] = %g, No of Points (along this axis) = %d\n",  
	min_P0, MAX_P0, Acc_P0, d0, min_P0, MAX_P0, Acc_P0, d0);
 printf("-I1 1: Parameter Key (%s) 1: Extinction Rate\n", Symbol[1]); 
 printf(" [Parameter: 1]: -m1 %g -M1 %g -A1 %g -d1 %d\t [ min_Value[1] = %g, MAX_Value[1] = %g ]\t Accuracy[1] = %g, No of Points (along this axis) = %d\n",  
	min_P1, MAX_P1, Acc_P1, d1, min_P1, MAX_P1, Acc_P1, d1);
 printf("-I2 2: Parameter Key (%s) 2: Detection Probability\n", Symbol[2]); 
 printf(" [Parameter: 2]: -m2 %g -M2 %g -A2 %g -d2 %d\t [ min_Value[2] = %g, MAX_Value[2] = %g ]\t Accuracy[2] = %g, No of Points (along this axis) = %d\n",  
	min_P2, MAX_P2, Acc_P2, d2, min_P2, MAX_P2, Acc_P2, d2);
 printf("-I3 3: Parameter Key (%s) 3: Probability of Presence at time 0\n", Symbol[3]); 
 printf(" [Parameter: 3]: -m3 %g -M3 %g -A3 %g -d3 %d\t [ min_Value[3] = %g, MAX_Value[3] = %g ]\t Accuracy[3] = %g, No of Points (along this axis) = %d\n",  
	min_P3, MAX_P3, Acc_P3, d3, min_P3, MAX_P3, Acc_P3, d3);
  
 printf(" -sT %g\t TOLERANCE (minimization algorithm): %g\n", TOLERANCE, TOLERANCE);
 printf(" -sN %d\t Max No of Iterations (minimization algorithm): %d\n", MAX_No_of_ITERATIONS, 
       MAX_No_of_ITERATIONS );

 
 
 
