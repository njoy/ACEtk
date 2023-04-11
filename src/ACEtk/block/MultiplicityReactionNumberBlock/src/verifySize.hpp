static void verifySize( Iterator begin, Iterator end, unsigned int nyp ) {

  if ( nyp != 0 ) {

    auto size = std::distance( begin, end );
    if ( size < nyp + 1 ) {

      Log::error( "The size of the XSS subrange should be at least NYP + 1" );
      Log::info( "NYP value: {}", nyp );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }
}
