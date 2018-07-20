template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
struct Sorted : Range {
  static constexpr bool isSorted = true;

#include "ACEtk/details/verify/Sorted/src/ctor.hpp"
#include "ACEtk/details/verify/Sorted/src/assignment.hpp"

};
