#include "catch.hpp"
#include "ACEtk/Table.hpp"

#include <sstream>

using namespace njoy::ACEtk;

SCENARIO("print a 1.0.0 header"){
  std::string retroHeader =
    " 92235.80c  233.024800  2.5301E-08   12/19/12\n"
    "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";

  State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
  auto header = Table::Header::parse(s);

  std::ostringstream oss;
  header.print<1,0,0>( oss );
  REQUIRE( retroHeader == oss.str() );
}

SCENARIO("2.0.1 header"){
  std::string modernHeader =
    "     2.0.1            1095242.710nc              ENDFB-VII.1\n"
    "  239.980100   2.5301E-08 2012-12-13    3\n"
    "The next two lines are the first two lines of ’old-style’ ACE.    \n"
    " 95642.80c  239.980100  2.5301E-08   12/13/12                         \n"
    "Am242 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)\n";

  State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
  auto header = Table::Header::parse(s);

  std::ostringstream oss;
  header.print<2,0,1>( oss );
  REQUIRE( modernHeader == oss.str() );
}
