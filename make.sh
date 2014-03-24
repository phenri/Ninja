W="-Wall -Wextra -pedantic -Wfatal-errors"
O="-DNDEBUG -O3 -msse4.2 -fno-rtti -flto -s"
g++ -static-libstdc++ -std=c++11 -pthread $O $W ./*.cc -o $1

