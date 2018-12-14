template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct Normal: public Range {

protected:
  #include "ACEtk/details/verify/Normal/src/check.hpp"

public:
  static constexpr bool isNormal = true;

  #include "ACEtk/details/verify/Normal/src/ctor.hpp"
  #include "ACEtk/details/verify/Normal/src/assignment.hpp"
};

