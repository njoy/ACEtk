#ifndef ACETK_HPP
#define ACETK_HPP

#include <regex>
#include <istream>
#include <iterator>
#include <functional>
#include <map>

#ifdef USING_CPP17
  #include <optional>
#else 
  #include <experimental/optional>
  namespace std {
    using namespace std::experimental;
  }
#endif

#include "date.h"
#include "disco.hpp"
#include "dimwits.hpp"
#include "interpolation.hpp"
#include "header-utilities.hpp"
#include "Log.hpp"
#include "range/v3/all.hpp"
#include "hopscotch_map.h"

namespace njoy {
namespace ACEtk {

using namespace date;
using namespace disco;
using namespace dimwits;

template< typename Iterator >
struct State{
  long lineNumber = 1;
  Iterator position;
  const Iterator end;
};

#include "ACEtk/Table.hpp"
#include "ACEtk/details.hpp"
#include "ACEtk/interpretation.hpp"  

}
}

#endif
