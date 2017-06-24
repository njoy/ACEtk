#define CATCH_CONFIG_MAIN
#include <chrono>

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("parsing a ACE file"){
  auto timeStart = std::chrono::steady_clock::now();
  auto contents = njoy::utility::slurpFileToMemory("92238.710nc");
  auto parsingStart = std::chrono::steady_clock::now();
  State< std::string::iterator > s{ 1, contents.begin(), contents.end() };
  auto table = Table( s );
  auto parsingEnd = std::chrono::steady_clock::now();
 
  std::cout << "IO took "
            << std::chrono::duration_cast<std::chrono::microseconds>(parsingStart - timeStart).count()
            << "us.\n";
  std::cout << "parsing took "
            << std::chrono::duration_cast<std::chrono::microseconds>(parsingEnd - parsingStart).count()
            << "us.\n";
  std::cout << "IO and parsing took "
            << std::chrono::duration_cast<std::chrono::microseconds>(parsingEnd - timeStart).count()
            << "us.\n";
}
