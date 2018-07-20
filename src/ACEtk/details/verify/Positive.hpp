template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct Positive : Range{
protected:
#include "ACEtk/details/verify/Positive/src/check.hpp"

public:
  static constexpr bool isPositive = true;

#include "ACEtk/details/verify/Positive/src/ctor.hpp"
};

