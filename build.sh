cmake -B bin
cmake --build bin

# or uncommment below and change accordingly

# g++ -std=c++17 -DWIN32_LEAN_AND_MEAN -c -Iinclude -o bin/crtb_net.o src/rtb_net.cpp -fPIC
# g++ -shared bin/crtb_net.o -lws2_32 -lwsock32 -o bin/libcrtb_net.so
# gcc -o bin/server example.c bin/libcrtb_net.so
# ./server.exe

# clang++ -std=c++17 -c -Iinclude -o bin/crtb_net.o src/crtb_net.cpp -fPIC
# clang++ -shared bin/crtb_net.o -o bin/libcrtb_net.so
# clang -o bin/server example.c bin/libcrtb_net.so
# ./server
