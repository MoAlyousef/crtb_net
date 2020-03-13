# Trouble with cmake? uncommment below and change accordingly

# g++-9.exe -std=c++17 -DWIN32_LEAN_AND_MEAN -c -Iinclude -Iext/rtb/include -o bin/crtb_net.o src/rtb_net.cpp -fPIC
# g++-9.exe -shared bin/crtb_net.o -lws2_32 -lwsock32 -o bin/libcrtb_net.so -pthread
# gcc-9.exe -std=c89 -Iinclude -o bin/server examples/server.c bin/libcrtb_net.so
# gcc-9.exe -std=c89 -Iinclude -o bin/client examples/client.c bin/libcrtb_net.so
# ./bin/client.exe
# ./bin/server.exe

# g++-9 -std=c++17 -c -Iinclude -Iext/rtb/include -o bin/crtb_net.o src/crtb_net.cpp -fPIC
# g++-9 -shared bin/crtb_net.o -o bin/libcrtb_net.so -pthread
# gcc-9 -std=c89 -Iinclude -o bin/server examples/server.c bin/libcrtb_net.so
# gcc-9 -std=c89 -Iinclude -o bin/client examples/client.c bin/libcrtb_net.so
# ./bin/client
# ./bin/server
