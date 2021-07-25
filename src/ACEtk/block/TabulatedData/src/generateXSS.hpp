static std::vector< double >
generateXSS( std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< double >&& x,
             std::vector< double >&& y ) {

  std::vector< double > xss = { static_cast< double >( boundaries.size() ),
                                static_cast< double >( x.size() ) };
  auto nb = boundaries.size();
  auto ne = x.size();
  xss.reserve( 2 + 2 * nb + 2 *  ne );

  if ( interpolants.size() != nb ) {

    Log::error( "The size of the boundaries and interpolant subranges are not "
                "consistent" );
    Log::info( "NB value: {}", nb );
    Log::info( "boundaries.size(): {}", nb );
    Log::info( "interpolants.size(): {}", interpolants.size() );
    throw std::exception();
  }

  if ( y.size() != ne ) {

    Log::error( "The size of the x and y subranges are not consistent" );
    Log::info( "NE value: {}", ne );
    Log::info( "x.size(): {}", ne );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  xss.insert( xss.end() - 1, boundaries.begin(), boundaries.end() );
  xss.insert( xss.end() - 1, interpolants.begin(), interpolants.end() );
  xss.insert( xss.end(), x.begin(), x.end() );
  xss.insert( xss.end(), y.begin(), y.end() );

  return xss;
}
