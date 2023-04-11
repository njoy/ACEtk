static void verifySize( Iterator begin, Iterator end, unsigned int nes ) {

  auto size = std::distance( begin, end );
  if ( size < nes ) {

    Log::error( "The size of the XSS subrange should be at least NES" );
    Log::info( "NES value: {}", nes );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
