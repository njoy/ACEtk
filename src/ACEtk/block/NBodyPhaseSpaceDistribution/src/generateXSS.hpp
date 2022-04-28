static std::vector< double > generateXSS( unsigned int npsx, double ap,
                                          unsigned int interpolation,
                                          std::vector< double >&& values,
                                          std::vector< double >&& pdf,
                                          std::vector< double >&& cdf ) {

  std::vector< double > xss = { static_cast< double >( npsx ),
                                ap,
                                static_cast< double >( interpolation ) };
  xss.reserve( 5 + 3 * values.size() );
  details::ColumnData columns( "NBodyPhaseSpaceDistribution",
                               std::move( values ),
                               std::move( pdf ),
                               std::move( cdf ) );
  xss.insert( xss.end(), columns.begin(), columns.end() );

  return xss;
}
