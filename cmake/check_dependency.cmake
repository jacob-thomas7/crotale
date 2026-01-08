function(check_dependency name)
    string(TOLOWER ${name} NAME_LOWER)    
    string(TOUPPER ${name} NAME_UPPER)    

    if(NOT DEFINED CROTALE_${NAME_UPPER}_SOURCE_DIR)
        message(FATAL_ERROR
            "Unable to find a source directory for CROTALE_${NAME_UPPER}.\n"
            "Please make sure it is included in the CMake configuration.\n"
            "The source can be found at https://github.com/jacob-thomas7/crotale-${NAME_LOWER}"
        )
    endif()

    if(NOT TARGET crotale::${NAME_LOWER})
        message(FATAL_ERROR
            "Unable to find a target building crotale::${NAME_LOWER}."
            "Please make sure CROTALE_${NAME_UPPER}_STATIC or CROTALE_${NAME_UPPER}_SHARED are set."
        )
    endif()
endfunction()