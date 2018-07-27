template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct StrictlyPositive : Range {
protected:
#include "ACEtk/details/verify/StrictlyPositive/src/check.hpp"

public:
  static constexpr bool isPositive = true;
  static constexpr bool isStrictlyPositive = true;

#include "ACEtk/details/verify/StrictlyPositive/src/ctor.hpp"
#include "ACEtk/details/verify/StrictlyPositive/src/assignment.hpp"

};
