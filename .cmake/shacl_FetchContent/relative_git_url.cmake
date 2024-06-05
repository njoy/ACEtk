include_guard(GLOBAL)

# Gets the URL of the git remote with name origin
function(get_git_remote_url return_url)   
  execute_process( COMMAND "${GIT_EXECUTABLE}" config --get remote.origin.url 
                           WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                           OUTPUT_STRIP_TRAILING_WHITESPACE
                           RESULT_VARIABLE rc
                           OUTPUT_VARIABLE output
                           ERROR_VARIABLE error )

  if( rc ) 
    string(CONCAT error_output 
          "FetchContent GIT_REPOSITORY listed with relative URL.\n"
          "Error encountered while obtaining parent repository for ${PROJECT_NAME} URL for remote named origin \n"
          "${output}"
          "${error}"
    )
    message(FATAL_ERROR "${error_output}")
  endif()

  set(${return_url} ${output} PARENT_SCOPE) 

endfunction()

# If the dependency contains relative paths (i.e. ../../proj/repo) then update
# the url relative to the current project's url
function(get_dependency_url input_url return_url)   

  if(${input_url} MATCHES "^[.][.][/]")

    cmake_path(APPEND PROJECT_SOURCE_DIR .git OUTPUT_VARIABLE git_path)
    if(EXISTS ${git_path})
      get_git_remote_url(remote_url)
      set(remote_url_prefix "${remote_url}")
      while(${input_url} MATCHES "^[.][.][/]")
        string(FIND "${remote_url_prefix}" "/" truncate_point REVERSE)
        string(SUBSTRING "${remote_url_prefix}" 0 ${truncate_point} remote_url_prefix)
        string(SUBSTRING "${input_url}" 3 -1 input_url)
      endwhile()
      set(retval "${remote_url_prefix}/${input_url}")
    else()
      message(STATUS "shacl-FetchContent_Declare - relative url ${input_url} provided but ${PROJECT_NAME} isn't a git repository.")
      set(retval "${input_url}")
    endif()
  else()
    set(retval "${input_url}")
  endif()

  set(${return_url} ${retval} PARENT_SCOPE)

endfunction()
