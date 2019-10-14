namespace details{

#include "ACEtk/details/verify.hpp"
#include "ACEtk/details/src/make_array.hpp"
#include "ACEtk/details/hasACEify.hpp"  
#include "ACEtk/details/ACEify.hpp"  

/*
 This is intended for testing purposes.
 */
template< typename Range1, typename Range2 >
void printRanges( std::string name, Range1&& reference, Range2&& test ){
  njoy::Log::info( "{}", name );
  njoy::Log::info( "\treference: {}", reference | ranges::view::all );
  njoy::Log::info( "\ttest     : {}", test | ranges::view::all );
}


template< typename Range1, typename Range2 >
void checkEqualRange( Range1&& reference, Range2&& test ){
  for ( decltype( auto ) pair : ranges::view::zip( reference, test ) ) {
    CHECK( std::get< 0 >( pair ) == Approx( std::get< 1 >( pair ) ) );
    
  }
}
} 
