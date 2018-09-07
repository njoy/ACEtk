template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct Sorted : Range {
protected:
#include "ACEtk/details/verify/Sorted/src/check.hpp"

public:
  static constexpr bool isSorted = true;

#include "ACEtk/details/verify/Sorted/src/ctor.hpp"
#include "ACEtk/details/verify/Sorted/src/assignment.hpp"

};
