cd ./MacKENZIE_sss_cedp
rm *.txt
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt  ./SSS_CEDP -pC 0.1 -pE 0.1 -pD 0.5 > output.txt &
cd ../
cd ./MacKENZIE_mss_cedp
rm *.txt
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt  ./MSS_CEDP -pC 0.1 -pE 0.1 -pD 0.5 > output.txt &
cd ../
cd ./MODEL_SELECION_upgma
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_7GUILDS-out.txt ./upgma_model_selection_MacKenzie_7GUILDS -Nr 7 -Nc 28 -pC 1.0 -pE 1.0 -sP 4 -sT 1.0E-08 -m0 0.0 -M0 10.0 -m1 0.0 -M1 10.0 > output_7GUILDS.txt &
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_3ATOLLS-out.txt ./upgma_model_selection_MacKenzie_3ATOLLS -Nr 3 -Nc 28 -pC 1.0 -pE 1.0 -sP 4 -sT 1.0E-08 -m0 0.0 -M0 10.0 -m1 0.0 -M1 10.0 > output_3ATOLLS.txt &
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_COLEXT-out.txt ./upgma_model_selection_COLEXT -Nr 15 -Nc 17 -pC 1.0 -pE 1.0 -sP 2 -sT 1.0E-08 -m0 0.0 -M0 10.0 -m1 0.0 -M1 10.0 > output_COLEXT.txt &
cd ..
