static std::vector< double > generateXSS(
    std::size_t index,
    std::vector< double >&& production,
    std::vector< double >&& heating ) {

  const auto size = production.size();
  if ( heating.size() != size ) {

    Log::error( "The number of heating values is not equal to the number of "
                "production values" );
    Log::info( "Expected size = {}", size );
    Log::info( "Found production size = {}", production.size() );
    Log::info( "Found heating size = {}", heating.size() );
    throw std::exception();
  }

  std::vector< double > xss = { static_cast< double >( index ),
                                static_cast< double >( size ) };
  xss.reserve( 2 + 2 * size );
  xss.insert( xss.end(), production.begin(), production.end() );
  xss.insert( xss.end(), heating.begin(), heating.end() );

  return xss;
}
