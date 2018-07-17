template< typename T, utility::Require< true, utility::is_range, T > = true >
struct Positive : T {

#include "ACEtk/details/verify/Positive/src/ctor.hpp"

};
