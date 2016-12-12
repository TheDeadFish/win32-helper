combine.exe

call egcc.bat
gcc %CCFLAGS2% bin\win32hlp.cc -c
copy /Y bin\win32hlp.h %PROGRAMS%\local\include
ar -rcs  %PROGRAMS%\local\lib32\libexshit.a win32hlp.o
