 rm cnn_ex.exe
 g++ -Wall -I ./ac/ -c ../src/cnn_ex.cpp -o ./cnn_ex.o
 g++ -Wall -I ./ac/ -c ../src/cnn_ex_tb.cpp -o ./cnn_ex_tb.o
 g++ cnn_ex.o cnn_ex_tb.o -o cnn_ex.exe
 rm -rf cnn_ex.o cnn_ex_tb.o
 ./cnn_ex.exe
#firefox file:///home/sdagar/DAGER/windows/Catapult_working/ML/ccs/index.html&
