template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct CosineBins: public Range {

protected:
  #include "ACEtk/details/verify/CosineBins/src/check.hpp"

public:
  static constexpr bool isCosineBins = true;

  #include "ACEtk/details/verify/CosineBins/src/ctor.hpp"
  #include "ACEtk/details/verify/CosineBins/src/assignment.hpp"
};
