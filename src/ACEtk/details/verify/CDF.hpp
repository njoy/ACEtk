template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct CDF: public Range {

protected:
  #include "ACEtk/details/verify/CDF/src/check.hpp"

public:
  static constexpr bool isCDF = true;
  static constexpr bool isPositive = true;
  static constexpr bool isSorted = true;

  #include "ACEtk/details/verify/CDF/src/ctor.hpp"
  #include "ACEtk/details/verify/CDF/src/assignment.hpp"
};
