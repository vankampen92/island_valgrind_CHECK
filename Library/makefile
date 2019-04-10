# =======================
#     LIBRARY make
# =======================

# Gnu C make cpgplot_GRID UTILS (libda_cpgplot_GRID.a)
# LIB_DIR              = ${HOME}/C_pro/
PROJECT_DIR          = ${HOME}/PROJECT_island_valgrind_CHECK/
INCLUDE_R_DIR=/usr/share/R/include/
EXTRA_INCLUDE_PATH   = -I${PROJECT_DIR}Include/ -I${PROJECT_DIR}Library/ -I${INCLUDE_R_DIR}
## R_SHLIB is a compilation FLAG for the generation of libraries compatible
## with the generation of a shared object. When no shared object is needed,
## the R_SHLIB flag is not required and RSH should be defined as NON_R_SHLIB
RSH = R_SHLIB # Options 'R_SHLIB' / 'NON_R_SHLIB'

CFLAGS=-g -Wall -DHAVE_INLINE -D${RSH} ${EXTRA_INCLUDE_PATH}
###CFLAGS= -Wall -O21

COMPILER=gcc -fPIC -DSHARED_OBJECT

OBJECTS=Checking_for_Parameter_Correctness.o Counting_Replicates_per_Time.o Counting_Type_of_Transitions.o Create_Binary_Combination.o EUCLIDIAN_DISTANCE_MATRIX.o GSL_MacKenzie_NLLikelihood_Function.o GSL_MacKenzie_NLL_Uneven_Function.o GSL_Minimization_Simplex.o GSL_NLL_Function_Uneven.o GSL_NLLikelihood_Function.o IO_AKAIKE_Model_Selection.o IO_Missing_Values.o MacKenzie_NLLikelihood_Function.o mle_Col_Ext_Uneven_Matrix_R_SHLIB.o mle_MacKenzie_Uneven_Matrix_R_SHLIB.o MODEL_SELECTION_UPGMA_MacKENZIE_R_SHLIB.o MODEL_SELECTION_UPGMA_R_SHLIB.o Parameter_Model.o Parameter_Space_R_SHLIB.o Probability_Rates.o Rates_into_Probabilities.o SP_Matrix_Data.o Time_Control.o Transition_Matrix.o upgma_clustering.o UPGMA_CLUSTERING_PARTITION.o R_SHLIB___mle_NLL_Uneven_Minimization.o R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization.o R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization.o MODEL_SELECTION_UPGMA_R_FUNCTION.o MODEL_SELECTION_UPGMA_MacKENZIE_R_FUNCTION.o # Parameter_Index_Checking_Order.o

.SUFIXES: .o .c

.c.o:
	${COMPILER} $(CFLAGS) -c $<

da_AUX: ${OBJECTS}
	ar -q libda_AUX.a ${OBJECTS}

da_AUX_SO: ${OBJECTS}
	gcc -shared -o libda_AUX.so ${OBJECTS}

clean:
	rm -f *.o *~
