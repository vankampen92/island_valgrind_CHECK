#################################################
PROJECT_DIR=${HOME}/PROJECT_island_valgrind_CHECK/
LIBRARY_DIR=${PROJECT_DIR}Library/
LIBRARY_IO_DIR=${PROJECT_DIR}IO_Library/
INCLUDE_DIR=${PROJECT_DIR}Include/
WKD=${PROJECT_DIR}MacKENZIE_sss_cedp/
EXTRA_LIBRARY_PATH+=-L/usr/lib/
EXTRA_LIBRARY_PATH+=-L/usr/local/lib/
EXTRA_LIBRARY_PATH+=-L${LIBRARY_DIR}
EXTRA_LIBRARY_PATH+=-L${LIBRARY_IO_DIR}
EXTRA_INCLUDE_PATH+=-I${INCLUDE_DIR}
EXTRA_INCLUDE_PATH+=-I${PROJECT_DIR}
EXTRA_INCLUDE_PATH+=-I${LIBRARY_DIR}
EXTRA_INCLUDE_PATH+=-I${LIBRARY_IO_DIR}
EXTRA_INCLUDE_PATH+=-I${WKD}
#################################################
CPG=NON_CPGPLOT_REPRESENTATION#Possibilities:'CPGPLOT_REPRESENTATION' / 'NON_CPGPLOT_REPRESENTATION'
#################################################
## R_SHLIB is a compilation FLAG for the generation of libraries compatible
## with the generation of the shared objects:
## R_SHLIB___mle_Colonization_Extinction.so and R_SHLIB___GSL_NLLikelihood_Evaluation.so
## When no shared object is needed, the R_SHLIB flag is not required
## and RSH should be defined as NRSHLIB

RSH=R_SHLIB# Only these two options will properly work: 'R_SHLIB' / 'NRSHLIB'
########################################################################

LDFLAGS+=${EXTRA_LIBRARY_PATH} -lda_AUX  -lda_IO -lm -lgsl -lgslcblas
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -g -D${CPG} -D${RSH}###############-Wall
######## either -g or some optimization opiton, for instance, -O3
########################################################################
########################################################################

TYPE_of_MAIN=LIKELIHOOD_MINIMIZATION_R_FUNCTION_CHECK###################
## D E F I N I T I O N   N A M E   E X E C U T B L E   C O D E #########

EXE=SSS_CEDP############################################################
########################################################################

OBJECTS = main_${TYPE_of_MAIN}.o argumentControl.o R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization.o

CC=gcc -fPIC -DSHARED_OBJECT##

.SUFIXES:	.o .c

.c.o:
	${CC} $(CXXFLAGS) -c $<

${EXE}:  	$(OBJECTS) AUX_Library IO_Library 
		$(CC) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Forcing always a re-build of auxiliary libraries
AUX_Library:
	cd ${LIBRARY_DIR}; rm *.o; rm libda_AUX.a; make RSH=${RSH}
IO_Library:
	cd ${LIBRARY_IO_DIR}; rm *.o; rm libda_IO.a; make
##################################################################
####################################################################
#    B E G I N :  Build shared libraries (.so) to be callable from R:
SHLIB_SO:
	R CMD SHLIB -o R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization.so R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization.c -z defs $(LDFLAGS)
#        E N D :  Example to build an R function from C code:
###################################################################

clean:
	rm -f *.o *~ core