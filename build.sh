cmake -B bin
cmake --build bin

# or uncommment below and change accordingly

# g++ -std=c++17 -DWIN32_LEAN_AND_MEAN -c -I ../rtb/include rtb_server.cpp -fPIC
# g++ -shared rtb_server.o -lws2_32 -lwsock32 -o librtb_server.so
# gcc main.c librtb_server.so


# clang++ -std=c++17 -c -I ../rtb/include rtb_server.cpp -fPIC
# clang++ -shared rtb_server.o -o librtb_server.so
# clang main.c librtb_server.so
