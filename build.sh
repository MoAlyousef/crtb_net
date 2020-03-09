clang++ -std=c++17 -c -I ../rtb/include rtb_server.cpp -fPIC
clang++ -shared rtb_server.o -o librtb_server.so
clang main.c librtb_server.so