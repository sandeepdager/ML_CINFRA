rm ./j2s.exe
g++ j2s.cpp -o j2s.exe
./j2s.exe |sed '/>/!d'>w.h
cp ./w.h ../src/w.h
