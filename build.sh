cmake -B bin
cmake --build bin

# or uncommment below and change accordingly

# g++ -std=c++17 -DWIN32_LEAN_AND_MEAN -c -I ../rtb/include rtb_server.cpp -fPIC
# g++ -shared rtb_server.o -lws2_32 -lwsock32 -o librtb_server.so
# gcc -o server example.c librtb_server.so
# ./server.exe

# clang++ -std=c++17 -c -I ../rtb/include rtb_server.cpp -fPIC
# clang++ -shared rtb_server.o -o librtb_server.so
# clang -o server example.c librtb_server.so
# ./server
