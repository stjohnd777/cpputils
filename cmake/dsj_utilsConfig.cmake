add_library(dsj_utils UNKNOWN IMPORTED)

set_target_properties(dsj_utils
        PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/../lib/dsj_utils.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../include" )