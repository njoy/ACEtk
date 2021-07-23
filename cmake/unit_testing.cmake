#######################################################################
# Setup
#######################################################################

message( STATUS "Adding ACEtk unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/ACEtk/Table/Data/Parse/test )
add_subdirectory( src/ACEtk/Table/Data/test )
add_subdirectory( src/ACEtk/Table/Header/test )
add_subdirectory( src/ACEtk/Table/test )
add_subdirectory( src/ACEtk/ContinuousEnergyTable/test )
add_subdirectory( src/ACEtk/details/verify/CDF/test )
add_subdirectory( src/ACEtk/details/verify/Positive/test )
add_subdirectory( src/ACEtk/details/verify/Sorted/test )
add_subdirectory( src/ACEtk/details/verify/StrictlyPositive/test )
add_subdirectory( src/ACEtk/details/verify/test )
add_subdirectory( src/ACEtk/interpretation/DEDX1/test )
add_subdirectory( src/ACEtk/interpretation/EL03/test )
add_subdirectory( src/ACEtk/interpretation/EPR/test )
add_subdirectory( src/ACEtk/interpretation/MP1/test )
