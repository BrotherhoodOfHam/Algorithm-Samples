################################################################################################
#
#    Algorithm Sample Project
#    
#    Contains a set of sample implementations of various algorithms and data structures.
#
################################################################################################

cmake_minimum_required (VERSION 3.0.0)

project (Algorithms)

add_subdirectory(cee)
add_subdirectory(cpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(
	CAlgorithms 
	Algorithms
	PROPERTIES FOLDER "Samples"
)

################################################################################################
