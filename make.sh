W="-Wall -Wextra -pedantic"
O="-O3 -msse4.2 -fno-rtti -s"
g++ -static-libstdc++ -std=c++11 -pthread $O $W ./*.cc -o $1

