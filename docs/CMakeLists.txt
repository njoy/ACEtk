find_package( sphinx )

if ( SPHINX_EXECUTABLE )
    set( SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set( SPHINX_BUILD  ${PROJECT_BINARY_DIR}/python/sphinx )
    file( MAKE_DIRECTORY ${SPHINX_BUILD} )

    add_custom_target( sphinx
        COMMAND
        ${SPHINX_EXECUTABLE} -b html
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${SPHINX_BUILD}
        COMMENT "generating sphinx documentation in HTML"
    )
else()
    # cannot make documentation
    message( STATUS "Cannot build sphinx documentation because sphinx was not found" )
endif()
