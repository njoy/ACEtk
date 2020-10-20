template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
struct PDF: public Range {

protected:
  #include "ACEtk/details/verify/PDF/src/check.hpp"

public:
  static constexpr bool isPDF = true;
  static constexpr bool isPositive = true;
  static constexpr bool isSorted = true;

  #include "ACEtk/details/verify/PDF/src/ctor.hpp"
  #include "ACEtk/details/verify/PDF/src/assignment.hpp"
};
