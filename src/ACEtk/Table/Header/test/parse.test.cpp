#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("parsing a 1.0.0 header"){
  std::string retroHeader = 
    " 92235.80c  233.024800  2.5301E-08   12/19/12\n"
    "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";

  State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
  auto header = Table::Header::parse(s);
  CHECK( s.lineNumber == 3 );
  CHECK( header.atomicWeightRatio == Approx(233.024800) );
  CHECK( header.szaid == "               92235.80c" );
  CHECK( header.processDate.year() == date::year(2012) );
  CHECK( header.processDate.month() == date::month(12) );
  CHECK( header.processDate.day() == date::day(19) );
}

SCENARIO("parsing a 2.0.1 header"){
  std::string modernHeader = 
    "     2.0.1            1095242.710nc              ENDFB-VII.1\n"
    "  239.980100   2.5301E-08 2012-12-13    3\n"
    "The next two lines are the first two lines of ’old-style’ ACE.    \n"
    " 95642.80c  239.980100  2.5301E-08   12/13/12                         \n"
    "Am242 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)\n";

  State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
  auto header = Table::Header::parse(s);
  CHECK( s.lineNumber == 6 );
  CHECK( header.atomicWeightRatio == Approx(239.980100) );
  CHECK( header.szaid == "           1095242.710nc" );
  CHECK( header.processDate.year() == date::year(2012) );
  CHECK( header.processDate.month() == date::month(12) );
  CHECK( header.processDate.day() == date::day(13) );
  
}

SCENARIO("invalid 1.0.0 header"){
  SECTION("malformed atomic weight"){
    std::string retroHeader = 
      " 92235.80c  233.0a4800  2.5301E-08   12/19/12\n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";
 
    State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("nonphysical atomic weight ratio"){
    std::string retroHeader = 
      " 92235.80c -233.024800  2.5301E-08   12/19/12\n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";
 
    State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("nonphysical temperature"){
    std::string retroHeader = 
      " 92235.80c  233.024800 -2.5301E-08   12/19/12\n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";
 
    State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("misformatted date"){
    std::string retroHeader = 
      " 92235.80c  233.024800  2.5301E-08     121912\n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";
 
    State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("invalid date"){
    std::string retroHeader = 
      " 92235.80c  233.024800  2.5301E-08   12/99/12\n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9228\n";
 
    State< std::string::iterator > s{ 1, retroHeader.begin(), retroHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
}

SCENARIO("invalid 2.0.1 header"){
  SECTION("malformed atomic weight"){
    std::string modernHeader =
      "     2.0.1              92235.710nc              ENDFB-VII.1\n"
      "  233.a24800   2.5301E-08 2012-12-19    3\n"
      "The next two lines are the first two lines of 'old-style' ACE.        \n"
      " 92235.80c  233.024800  2.5301E-08   12/19/12                         \n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53) \n";
    State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("nonphysical atomic weight ratio"){
    std::string modernHeader =
      "     2.0.1              92235.710nc              ENDFB-VII.1\n"
      " -233.024800   2.5301E-08 2012-12-19    3\n"
      "The next two lines are the first two lines of 'old-style' ACE.        \n"
      " 92235.80c  233.024800  2.5301E-08   12/19/12                         \n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53) \n";
 
    State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("nonphysical temperature"){
    std::string modernHeader = 
      "     2.0.1              92235.710nc              ENDFB-VII.1\n"
      "  233.024800  -2.5301E-08 2012-12-19    3\n"
      "The next two lines are the first two lines of 'old-style' ACE.        \n"
      " 92235.80c  233.024800  2.5301E-08   12/19/12                         \n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53) \n";
 
    State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("misformatted date"){
    std::string modernHeader =
      "     2.0.1              92235.710nc              ENDFB-VII.1\n"
      "  233.024800   2.5301E-08 12-19-2012    3\n"
      "The next two lines are the first two lines of 'old-style' ACE.        \n"
      " 92235.80c  233.024800  2.5301E-08   12/19/12                         \n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53) \n";
 
    State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("invalid date"){
    std::string modernHeader =
      "     2.0.1              92235.710nc              ENDFB-VII.1\n"
      "  233.024800   2.5301E-08 2012-12-99    3\n"
      "The next two lines are the first two lines of 'old-style' ACE.        \n"
      " 92235.80c  233.024800  2.5301E-08   12/19/12                         \n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53) \n";
 
    State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
  SECTION("negative number of comment lines"){
    std::string modernHeader =
      "     2.0.1              92235.710nc              ENDFB-VII.1\n"
      "  233.024800   2.5301E-08 2012-12-11   -3\n"
      "The next two lines are the first two lines of 'old-style' ACE.        \n"
      " 92235.80c  233.024800  2.5301E-08   12/19/12                         \n"
      "U235 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53) \n";
 
    State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
    CHECK_THROWS( Table::Header::parse(s) );
  }
}

SCENARIO("invalid header version"){
  std::string modernHeader =
    "     3.0.1              92235.710nc              ENDFB-VII.1\n";
  State< std::string::iterator > s{ 1, modernHeader.begin(), modernHeader.end() };
  CHECK_THROWS( Table::Header::parse(s) );
}
