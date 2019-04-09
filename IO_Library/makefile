# =======================
#     LIBRARY make
# =======================

# Gnu C make cpgplot_GRID UTILS (libda_cpgplot_GRID.a)
PROJECT_DIR          = ${HOME}/PROJECT_island_valgrind_CHECK/
LIB_DIR              = ${PROJECT_DIR}IO_Library/
EXTRA_INCLUDE_PATH   = -I${LIB_DIR} -I${PROJECT_DIR}Include/ -I${PROJECT_DIR}Library/
## R_SHLIB is a compilation FLAG for the generation of libraries compatible
## with the generation of a shared object. When no shared object is needed,
## the R_SHLIB flag is not required and RSH should be defined as NON_R_SHLIB

CFLAGS=-g -Wall -DHAVE_INLINE ${EXTRA_INCLUDE_PATH}
###CFLAGS= -Wall -O21

COMPILER=gcc -fPIC -DSHARED_OBJECT

OBJECTS=IO_Procedures_Laccadives.o IO_Procedures_MacKenzie.o IO_Procedures_Standard.o IO_Procedures_Pirineus.o

.SUFIXES:       .o .c

.c.o:
	${COMPILER} $(CFLAGS) -c $<

da_IO: ${OBJECTS}
	ar -q libda_IO.a ${OBJECTS}

da_IO_SO: ${OBJECTS}
	gcc -shared -o libda_IO.so ${OBJECTS}

clean:
	rm -f *.o *~
