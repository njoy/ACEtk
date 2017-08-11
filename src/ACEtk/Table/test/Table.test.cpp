#define CATCH_CONFIG_MAIN
#include <chrono>
#include <fstream>

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("parsing a ACE file from State"){
  auto timeStart = std::chrono::steady_clock::now();
  auto contents = njoy::utility::slurpFileToMemory("92238.710nc");
  auto parsingStart = std::chrono::steady_clock::now();
  State< std::string::iterator > s{ 1, contents.begin(), contents.end() };
  auto table = Table( s );
  auto parsingEnd = std::chrono::steady_clock::now();

  std::cout << "-----------------------------------" << std::endl;
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

SCENARIO("parsing a ACE file from a string"){
  auto timeStart = std::chrono::steady_clock::now();
  auto table = Table( njoy::utility::slurpFileToMemory("92238.710nc") );
  auto parsingEnd = std::chrono::steady_clock::now();

  std::cout << "-----------------------------------" << std::endl;
  std::cout << "IO and parsing took "
            << std::chrono::duration_cast<std::chrono::microseconds>(parsingEnd - timeStart).count()
            << "us.\n";
}

SCENARIO("parsing a ACE file from a ifstream"){
  auto timeStart = std::chrono::steady_clock::now();
  auto table = Table( std::ifstream("92238.710nc") );
  auto parsingEnd = std::chrono::steady_clock::now();

  std::cout << "-----------------------------------" << std::endl;
  std::cout << "IO and parsing took "
            << std::chrono::duration_cast<std::chrono::microseconds>(parsingEnd - timeStart).count()
            << "us.\n";
}
