set path=%path%;C:\mingw\bin
g++ -c -Wall -fexceptions -fexpensive-optimizations -O3 -std=c++11 -g main.cpp
g++ -o nwsjs main.o  -s
