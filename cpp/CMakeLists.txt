#
#	CPP Samples
#
#

set(alg_hdr
	inc/graphs/Digraph.h
	inc/graphs/Traversal.h
	inc/graphs/Algorithms.h
)

set(alg_src
	src/Main.cpp
)

add_executable(Algorithms ${alg_hdr} ${alg_src})
TARGET_INCLUDE_DIRECTORIES(Algorithms PUBLIC inc)
SET_TARGET_PROPERTIES(Algorithms PROPERTIES LINKER_LANGUAGE CXX)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${alg_src})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${alg_hdr})
