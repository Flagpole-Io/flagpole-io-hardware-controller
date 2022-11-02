if (HIREDIS_INCLUDE_DIRS AND HIREDIS_LIBRARIES)
    set(HIREDIS_FIND_QUIETLY TRUE)
else ()
    find_path(HIREDIS_INCLUDE_DIR NAMES hiredis/hiredis.h HINTS ${HIREDIS_ROOT_DIR} PATH_SUFFIXES include)
    find_library(HIREDIS_LIBRARY NAMES hiredis HINTS ${HIREDIS_ROOT_DIR} PATH_SUFFIXES ${CMAKE_INSTALL_LIBDIR})

    set(HIREDIS_INCLUDE_DIRS ${HIREDIS_INCLUDE_DIR})
    set(HIREDIS_LIBRARIES ${HIREDIS_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(hiredis DEFAULT_MSG HIREDIS_LIBRARY HIREDIS_INCLUDE_DIR)

    mark_as_advanced(HIREDIS_LIBRARY HIREDIS_INCLUDE_DIR)
endif ()