              case 'N':
              if(argv[argcount][2]=='r')
                sscanf(argv[argcount+1],"%d", &No_of_SPECIES);
 	      else if(argv[argcount][2]=='c')
 	        sscanf(argv[argcount+1],"%d", &No_of_COLUMNS);
              else if(argv[argcount][2]=='R')
 	        sscanf(argv[argcount+1],"%d", &REPLICATES);
              else if(argv[argcount][2]=='T')
 	        sscanf(argv[argcount+1],"%d", &No_of_TRANSECTS);
              else {
		printf("**invalid command line argument: %s%c\n",
		       "-N", argv[argcount][2]);
		exit(0);
	      }
 	      skip++;
 	      break;

              case 'p':
              if(argv[argcount][2]=='C')
                sscanf(argv[argcount+1],"%lf", &Colonization_Rate);
 	      else if(argv[argcount][2]=='E')
 	        sscanf(argv[argcount+1],"%lf", &Extinction_Rate);
              else if(argv[argcount][2]=='D')
 	        sscanf(argv[argcount+1],"%lf", &Detectability_Value);
              else if(argv[argcount][2]=='R')
 	        sscanf(argv[argcount+1],"%d", &RATES);
              else if(argv[argcount][2]=='F')
 	        sscanf(argv[argcount+1],"%lf", &Phi_0);
              else {
		printf("**invalid command line argument: %s%c\n",
		       "-p", argv[argcount][2]);
		exit(0);
	      }
 	      skip++;
 	      break;

              
