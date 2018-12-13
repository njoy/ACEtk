template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
class CDF: Range {

protected:
  #include "ACEtk/details/verify/CDF/src/check.hpp"

public:
  static constexprt bool isCDF = true;

  #include "ACEtk/details/verify/CDF/src/ctor.hpp"
};
