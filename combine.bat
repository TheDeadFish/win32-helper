combine.exe

call egcc.bat
gcc %CCFLAGS2% bin\win32hlp.cc -c -g -fpermissive
gcc %CCFLAGS2% src\drop.cc -c -g -o win32hlp-drop.o

copy /Y bin\win32hlp.h %PROGRAMS%\local\include
ar -rcs  %PROGRAMS%\local\lib32\libexshit.a *.o
