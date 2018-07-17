template< typename T, utility::Require< true, utility::is_range, T > = true >
struct Sorted : T {

#include "ACEtk/details/verify/Sorted/src/ctor.hpp"

};
