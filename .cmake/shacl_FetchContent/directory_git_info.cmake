include_guard(GLOBAL)
function(get_git_info_for_directory source_dir return_url return_hash return_branch)   

  # Get remote url of origin
  execute_process( COMMAND "${GIT_EXECUTABLE}" config --get remote.origin.url 
                           WORKING_DIRECTORY "${source_dir}"
                           OUTPUT_STRIP_TRAILING_WHITESPACE
                           RESULT_VARIABLE rc
                           OUTPUT_VARIABLE output
                           ERROR_VARIABLE error )

  if( rc ) 
    string(CONCAT error_output 
          "Error encountered while obtaining repository url for fetched content in ${source_dir} \n"
          "${output}"
          "${error}"
    )
    message(FATAL_ERROR "${error_output}")
  endif()

  set(${return_url} ${output} PARENT_SCOPE) 

  # Get hash of current branch
  execute_process( COMMAND  "${GIT_EXECUTABLE}" rev-parse HEAD
                           WORKING_DIRECTORY "${source_dir}"
                           OUTPUT_STRIP_TRAILING_WHITESPACE
                           RESULT_VARIABLE rc
                           OUTPUT_VARIABLE output
                           ERROR_VARIABLE error )

  if( rc ) 
    string(CONCAT error_output 
          "Error encountered while obtaining repository url for fetched content in ${source_dir} \n"
          "${output}"
          "${error}"
    )
    message(FATAL_ERROR "${error_output}")
  endif()

  set(${return_hash} ${output} PARENT_SCOPE) 

  # Get current tag or HEAD if not on a branch or tag
  execute_process( COMMAND  "${GIT_EXECUTABLE}" rev-parse --abbrev-ref HEAD
                           WORKING_DIRECTORY "${source_dir}"
                           OUTPUT_STRIP_TRAILING_WHITESPACE
                           RESULT_VARIABLE rc
                           OUTPUT_VARIABLE output
                           ERROR_VARIABLE error )

  set(${return_branch} ${output} PARENT_SCOPE) 

endfunction()

