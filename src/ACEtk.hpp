#ifndef ACETK_HPP
#define ACETK_HPP

#include <regex>
#include <istream>
#include <iterator>
#include <functional>
#include <algorithm>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "range/v3/all.hpp"
#pragma GCC diagnostic pop

#include "date.h"
#include "disco.hpp"
#include "dimwits.hpp"
#include "interpolation.hpp"
#include "header-utilities.hpp"
#include "Log.hpp"

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

#include "ACEtk/details.hpp"
#include "ACEtk/Table.hpp"
#include "ACEtk/interpretation.hpp"  

}
}

#endif
