class Data {
private:
  std::vector< double > xss;
  std::array< int64_t, 32 > jxs;
  std::array< int64_t, 16 > nxs;
  std::pair< std::array< int32_t, 16 >,
             std::array< double, 16 > > izaw;

  /* helper typedef */
  template< int index >
  using Index = std::integral_constant< int, index >;

  #include "ACEtk/Table/Data/src/name.hpp"
  #include "ACEtk/Table/Data/src/verifyIndex.hpp"
  #include "ACEtk/Table/Data/src/fetch.hpp"

protected:
  #include "ACEtk/Table/Data/Parse.hpp"

public:
  #include "ACEtk/Table/Data/src/ctor.hpp"

#define CONST_OVERLOAD( method )                        \
  auto method( std::size_t index ) const {              \
    return const_cast<Data&>(*this).method(index);      \
  }

  #include "ACEtk/Table/Data/src/IZ.hpp"
  #include "ACEtk/Table/Data/src/AW.hpp"
  #include "ACEtk/Table/Data/src/NXS.hpp"
  #include "ACEtk/Table/Data/src/JXS.hpp"
  #include "ACEtk/Table/Data/src/XSS.hpp"

#undef CONST_OVERLOAD

  #include "ACEtk/Table/Data/src/print.hpp"
};
