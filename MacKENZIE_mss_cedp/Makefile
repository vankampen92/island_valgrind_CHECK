#################################################
PROJECT_DIR=${HOME}/PROJECT_island_valgrind_CHECK/
LIBRARY_DIR=${PROJECT_DIR}Library/
LIBRARY_IO_DIR=${PROJECT_DIR}IO_Library/
INCLUDE_DIR=${PROJECT_DIR}Include/
WKD=${PROJECT_DIR}MacKENZIE_mss_cedp/
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

RSH=NON_R_SHLIB# Optins 'R_SHLIB': R compilation / 'NON_R_SHLIB': C compilation
########################################################################

LDFLAGS+=${EXTRA_LIBRARY_PATH} -lda_AUX  -lda_IO -lm -lgsl -lgslcblas
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -g -Wall -D${CPG} -D${RSH}###############
######## either -g or some optimization opiton, for instance, -O3
########################################################################
########################################################################

TYPE_of_MAIN=LIKELIHOOD_MINIMIZATION_UNEVEN_R_FUNCTION_CHECK############
## D E F I N I T I O N   N A M E   E X E C U T B L E   C O D E #########

EXE=MSS_CEDP############################################################
########################################################################

# Variable to setup library paths for shared objects (*.so)#############
RUNPATH=-Wl,-rpath=${LIBRARY_DIR}:${LIBRARY_IO_DIR}#####################

OBJECTS = main_${TYPE_of_MAIN}.o argumentControl.o

CC=gcc -fPIC -DSHARED_OBJECT##

.SUFIXES:	.o .c

.c.o:
	${CC} $(CXXFLAGS) -c $<

${EXE}:  	$(OBJECTS) AUX_Library_SO IO_Library_SO
		$(CC) $(CXXFLAGS) ${RUNPATH} -o $@ $(OBJECTS) $(LDFLAGS)

# Forcing always a re-build of auxiliary static libraries
AUX_Library:
	cd ${LIBRARY_DIR}; rm *.o; rm libda_AUX.a; make RSH=${RSH}
IO_Library:
	cd ${LIBRARY_IO_DIR}; rm *.o; rm libda_IO.a; make
##################################################################
# Compiling libraries as a shared objects (dynamic libraries):
AUX_Library_SO:
	cd ${LIBRARY_DIR}; rm *.o; rm libda_AUX.so; make RSH=${RSH} da_AUX_SO
IO_Library_SO:
	cd ${LIBRARY_IO_DIR}; rm *.o; rm libda_IO.so; make da_IO_SO
####################################################################
#    B E G I N :  Build shared libraries (.so) to be callable from R:
SHLIB_SO:
	R CMD SHLIB -o R_SHLIB___mle_MacKenzie_NLL_Minimization.so R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization.c R_SHLIB___mle_NLL_Unven_Minimization.c -z defs $(LDFLAGS)
#        E N D :  Example to build an R function from C code:
###################################################################

clean:
	rm -f *.o *~ core
