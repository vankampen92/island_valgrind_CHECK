No_of_SPECIES     = 100;
No_of_COLUMNS     = 100;
No_of_TRANSECTS   = 1;
REPLICATES        = 1000;
Colonization_Rate = 1.0;
Extinction_Rate   = 1.0;
Detectability_Value = 0.5;
Phi_0               = 0.5; // Probability of presence at time 0.
RATES             = 1; // If RATES = 0, then model parametres are regarded as transition
                       // probabilities rather than true rates. 
Symbol = (char **)calloc(MODEL_PARAMETERS_MAXIMUM, sizeof(char * ) );
char * p_Symbol;
Symbol[0] = (char *)calloc( 10, sizeof(char ) ); p_Symbol = strcat(Symbol[0], "C");
Symbol[1] = (char *)calloc( 10, sizeof(char ) ); p_Symbol = strcat(Symbol[1], "E");
Symbol[2] = (char *)calloc( 10, sizeof(char ) ); p_Symbol = strcat(Symbol[2], "D");
Symbol[3] = (char *)calloc( 10, sizeof(char ) ); p_Symbol = strcat(Symbol[3], "P");
