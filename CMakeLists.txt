################################################################################################

cmake_minimum_required (VERSION 3.0.0)
set(CMAKE_C_FLAGS "-std=c11")

project (Algorithms C)

################################################################################################

set(alg_hdr
    
	inc/common.h
	inc/variant.h
	inc/sorting.h

	inc/vector.h
	inc/stack.h
    inc/queue.h
    inc/graph.h
    inc/tree.h
)

set(alg_src
    
	src/vector.c
	src/insertion_sort.c
	src/merge_sort.c

	src/stack.c
    src/queue.c
    src/graph.c
    src/tree.c
)

ADD_LIBRARY(Algorithms STATIC ${alg_hdr} ${alg_src})
TARGET_INCLUDE_DIRECTORIES(Algorithms PUBLIC inc)

################################################################################################

set(test_src
    test/test.c
    test/test_vector.c
    test/test_stack.c
    test/test_queue.c
    test/test_tree.c
    test/test_graph.c
)

ADD_EXECUTABLE(Test ${test_src})
TARGET_LINK_LIBRARIES(Test PUBLIC Algorithms)

################################################################################################

#set_property(TARGET Test Algorithms PROPERTY C_STANDARD 99)
