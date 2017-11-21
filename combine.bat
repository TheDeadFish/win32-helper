combine.exe

call egcc.bat
gcc %CCFLAGS2% bin\win32hlp.cc -c -g -o obj\win32hlp.o
gcc %CCFLAGS2% src\drop.cc -c -g -o obj\drop.o
gcc %CCFLAGS2% src\openfile.cc -c -g -o obj\openfile.o -fpermissive
gcc %CCFLAGS2% src\selfiles.cc -c -g -o obj\selfiles.o
copy /Y bin\win32hlp.h %PROGRAMS%\local\include
ar -rcs  %PROGRAMS%\local\lib32\libwin32hlp.a *.o
