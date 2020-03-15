# Trouble with cmake? uncommment below and change accordingly

# For dynamic linking
# g++.exe -std=c++17 -DWIN32_LEAN_AND_MEAN -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/crtb_net.cpp -fPIC
# g++.exe -shared ../bin/crtb_net.o -lws2_32 -lwsock32 -o ../bin/libcrtb_net.so -pthread
# gcc.exe -std=c89 -I../include -o ../bin/main main.c ../bin/libcrtb_net.so
# ../bin/main.exe

# g++ -std=c++17 -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/crtb_net.cpp -fPIC
# g++ -shared ../bin/crtb_net.o -o ../bin/libcrtb_net.so -pthread
# gcc -std=c89 -I../include -o ../bin/main main.c ../bin/libcrtb_net.so
# ../bin/main

# cl /std:c++17 /EHsc /D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS /D_CRT_SECURE_NO_WARNINGS /DNOMINMAX /DWIN32_LEAN_AND_MEAN /I..\include /I..\.ext\rtb\include /Fo..\bin\crtb_net.obj -c ..\libsrc\crtb_net.cpp
# link.exe /lib /nologo /out:..\bin\libcrtb_net.dll ..\bin\crtb_net.obj
# cl /I..\include main.c /Fo..\bin\main.exe /link ..\bin\libcrtb_net.dll

# For static linking
# g++ -std=c++17 -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/crtb_net.cpp
# ar -crs ../bin/libcrtb_net.a ../bin/crtb_net.o
# gcc -std=c89 -I../include -o ../bin/main main.c ../bin/libcrtb_net.a -lstdc++ -pthread

# clang++ -std=c++17 -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/crtb_net.cpp
# ar -crs ../bin/libcrtb_net.a ../bin/crtb_net.o
# clang -std=c89 -I../include -o ../bin/main main.c ../bin/libcrtb_net.a -lc++

# cl /std:c++17 /EHsc /D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS /D_CRT_SECURE_NO_WARNINGS /DNOMINMAX /DWIN32_LEAN_AND_MEAN /I..\include /I..\.ext\rtb\include /Fo..\bin\crtb_net.obj -c ..\libsrc\crtb_net.cpp
# lib.exe /nologo /out:..\bin\libcrtb_net.lib ..\bin\crtb_net.obj
# cl /I..\include main.c /Fo..\bin\main.exe /link ..\bin\libcrtb_net.lib

# For static linking with OpenSSL
# g++ -std=c++17 -c -I../include -I../.ext/rtb/include -o ../bin/crtb_net.o ../libsrc/crtb_net.cpp
# ar -crs ../bin/libcrtb_net.a ../bin/crtb_net.o
# gcc -std=c89 -I../include -o ../bin/main main.c ../bin/libcrtb_net.a -lstdc++ -lssl -lcrypto -pthread
