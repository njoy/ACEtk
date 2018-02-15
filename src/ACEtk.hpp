#ifndef ACETK_HPP
#define ACETK_HPP

#include <regex>
#include <istream>
#include <iterator>

#include "date.h"
#include "disco.hpp"
#include "dimwits.hpp"
#include "interpolation.hpp"
#include "header-utilities.hpp"
#include "Log.hpp"
#include "ENDFtk.hpp"

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

template< typename T >
class ScaleBy{
  T scalar;
public:
  ScaleBy( T scalar ) : scalar(scalar) {}

  template<typename Range>
  auto operator()( Range&& range ) const {
    return range 
      | ranges::view::transform( 
          [ scalar_ = this->scalar ](auto&& value){ return value * scalar_; } );
  }
};

template<typename T>
constexpr auto scaleBy(T value){ return ScaleBy<T>{value}; }

#include "ACEtk/Table.hpp"
#include "ACEtk/interpretation.hpp"  

}
}

#endif
