template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct Positive : public Range{
protected:
#include "ACEtk/details/verify/Positive/src/check.hpp"

public:
  static constexpr bool isPositive = true;

#include "ACEtk/details/verify/Positive/src/ctor.hpp"
#include "ACEtk/details/verify/Positive/src/assignment.hpp"
};
