call egcc.bat
windres resource.rc -O coff -o resource.o
gcc test.cc win32hlp.cc ..\stdshit.cc %CCFLAGS2% resource.o -lcomdlg32
