################################################################################################

cmake_minimum_required (VERSION 3.0.0)

project (Algorithms C)

################################################################################################

set(alg_hdr
	inc/common.h
	inc/variant.h

	inc/vector.h
	inc/sorting.h
)

set(alg_src
	src/vector.c
	src/insertion_sort.c
	src/merge_sort.c
)

ADD_LIBRARY(Algorithms STATIC ${alg_hdr} ${alg_src})
TARGET_INCLUDE_DIRECTORIES(Algorithms PUBLIC inc)

################################################################################################

set(test_src
    test/test.c
)

ADD_EXECUTABLE(Test ${test_src})
TARGET_LINK_LIBRARIES(Test PUBLIC Algorithms)

################################################################################################
