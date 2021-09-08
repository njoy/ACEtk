static std::vector< double >
generateXSS( std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< double >&& x,
             std::vector< double >&& y ) {

  std::vector< double > xss = { 2 };
  InterpolationData interpolation( "NU::TABLE", std::move( boundaries ),
                                   std::move( interpolants ) );
  ColumnData data( "NU::TABLE", std::move( x ), std::move( y ) );
  xss.insert( xss.end(), interpolation.begin(), interpolation.end() );
  xss.insert( xss.end(), data.begin(), data.end() );
  return xss;
}
