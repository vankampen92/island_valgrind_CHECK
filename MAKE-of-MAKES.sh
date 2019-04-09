cd MacKENZIE_sss_cedp/
make clean
make TYPE_of_MAIN=LIKELIHOOD_MINIMIZATION_R_FUNCTION_CHECK
make clean
cd ..
cd MacKENZIE_mss_cedp/
make clean
make TYPE_of_MAIN=LIKELIHOOD_MINIMIZATION_UNEVEN_R_FUNCTION_CHECK
make clean
cd ..
cd MODEL_SELECION_upgma/
make clean
sh define-sym-links.sh
make TYPE_of_MAIN=COLEXT
make clean
make TYPE_of_MAIN=MacKenzie_3ATOLLS
make clean
make TYPE_of_MAIN=MacKenzie_7GUILDS
make clean
cd ..


