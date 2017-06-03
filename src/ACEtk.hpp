#ifndef ACETK_HPP
#define ACETK_HPP

#include "date.h"
#include "disco.hpp"
#include "dimwits.hpp"
#inlcude "header-utilities.hpp"
#inlcude "Log.hpp"

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

}
}

#endif
