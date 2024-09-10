
# Test with relative path provided with FIND_PACKAGE_ARGS
shacl_FetchContent_Declare( Catch2
    GIT_REPOSITORY  ../../catchorg/catch2
    GIT_TAG         master 
    FIND_PACKAGE_ARGS 2.0
)

# First-in wins - these values are ignored
shacl_FetchContent_Declare( Catch2
    GIT_REPOSITORY  nonsense 
    GIT_TAG         morenonsense
)

# Test with relative path
# shacl-trait also depends on Catch2
shacl_FetchContent_Declare( shacl-trait
    GIT_REPOSITORY  ../trait
    GIT_TAG         master
    GIT_SUBMODULES  ".gitmodules"
    GIT_SHALLOW     TRUE
)

shacl_FetchContent_MakeAvailable(shacl-trait Catch2)
