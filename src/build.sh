# Trouble with cmake? uncommment below and change accordingly

# g++-9.exe -std=c++17 -DWIN32_LEAN_AND_MEAN -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/rtb_net.cpp -fPIC
# g++-9.exe -shared ../bin/crtb_net.o -lws2_32 -lwsock32 -o ../bin/libcrtb_net.so -pthread
# gcc-9.exe -std=c89 -I../include -o ../bin/main main.c -L../bin -lcrtb_net
# ../bin/main.exe

# g++-9 -std=c++17 -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/crtb_net.cpp -fPIC
# g++-9 -shared ../bin/crtb_net.o -o ../bin/libcrtb_net.so -pthread
# gcc-9 -std=c89 -I../include -o ../bin/main main.c -L../bin -lcrtb_net
# ../bin/main
