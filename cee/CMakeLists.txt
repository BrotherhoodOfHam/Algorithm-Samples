#
#	C samples
#
#	Basic data structures and algorithms
#	Stack/Queue/Sorting etc.
#

set(alg_hdr
    
	inc/common.h
	inc/variant.h
	inc/sorting.h

	inc/vector.h
	inc/stack.h
    inc/queue.h
    inc/tree.h
	inc/heap.h
)

set(alg_src
    
	src/vector.c
	src/insertion_sort.c
	src/merge_sort.c
    src/quick_sort.c

	src/stack.c
    src/queue.c
    src/tree.c
	src/heap.c
)

set(test_src
    test/test.c
    test/test_vector.c
    test/test_stack.c
    test/test_queue.c
    test/test_tree.c
    test/test_heap.c
)

ADD_EXECUTABLE(CAlgorithms ${alg_hdr} ${alg_src} ${test_src})
TARGET_INCLUDE_DIRECTORIES(CAlgorithms PUBLIC inc)
SET_TARGET_PROPERTIES(CAlgorithms PROPERTIES LINKER_LANGUAGE C)
#set_property(TARGET CAlgorithms PROPERTY C_STANDARD 99)

source_group(src FILES ${alg_src})
source_group(inc FILES ${alg_hdr})
source_group(test FILES ${test_src})