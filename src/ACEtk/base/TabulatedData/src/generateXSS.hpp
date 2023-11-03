static std::vector< double >
generateXSS( const std::string& name,
             std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< double >&& x,
             std::vector< double >&& y ) {

  // reserve size in the vector
  std::vector< double > xss;
  const auto nr = boundaries.size();
  const auto ne = x.size();
  xss.reserve( 2 + 2 * nr + 2 * ne );

  // insert the interpolation data
  const block::InterpolationData interpolation( std::string( name ),
                                                std::move( boundaries ),
                                                std::move( interpolants ) );
  xss.insert( xss.end(), interpolation.begin(), interpolation.end() );

  // insert the tabulated data
  const ColumnData table( std::string( name ), std::move( x ), std::move( y ) );
  xss.insert( xss.end(), table.begin(), table.end() );

  return xss;
}
