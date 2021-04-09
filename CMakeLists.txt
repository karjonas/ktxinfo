cmake_minimum_required(VERSION 3.15)

project(ktxinfo
	DESCRIPTION "Show information about a ktx file."
)

find_package(Ktx REQUIRED)
find_package(Threads REQUIRED)

add_executable(ktxinfo main.c)
target_link_libraries(ktxinfo KTX::ktx)

