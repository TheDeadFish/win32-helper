project(stdshit)
cmake_minimum_required(VERSION 3.16)
set(CD ${CMAKE_CURRENT_SOURCE_DIR})
file(MAKE_DIRECTORY ${CD}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CD}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CD}/bin)

# build combine
add_link_options(-s)
add_executable(combine combine.cc)
target_link_libraries(combine -lstdshit)

# build stdshit.h
file(GLOB_RECURSE combine_dep src/*.h src/*.cc)
add_custom_command(
	OUTPUT ${CD}/bin/win32hlp.h ${CD}/bin/win32hlp.cc
	COMMAND ${CD}/bin/combine.exe
	DEPENDS combine ${combine_dep}
)

# build win32hlp library
add_library(win32hlp STATIC bin/win32hlp.cc 
	src/drop.cc src/openfile.cc src/selfiles.cc
	src/drawItem.cc
	src/txtEdtDlg.cc
)
