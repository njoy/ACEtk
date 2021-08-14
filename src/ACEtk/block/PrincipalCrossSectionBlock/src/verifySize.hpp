static void verifySize( Iterator begin, Iterator end, unsigned int nes ) {

  auto size = std::distance( begin, end );
  if ( size < 5 * nes ) {

    Log::error( "The size of the XSS subrange should be at least 5 * NES" );
    Log::info( "NES value: {}", nes );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
