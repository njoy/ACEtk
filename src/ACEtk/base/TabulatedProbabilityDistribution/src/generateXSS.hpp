static std::vector< double > generateXSS(
    int interpolation,
    std::vector< double >&& values,
    std::vector< double >&& pdf,
    std::vector< double >&& cdf,
    std::vector< std::vector< double > >&& data ) {

  std::vector< double > xss = { static_cast< double >( interpolation ) };
  xss.reserve( 2 + 3 * values.size() );
  data.insert( data.begin(), std::move( cdf ) );
  data.insert( data.begin(), std::move( pdf ) );
  data.insert( data.begin(), std::move( values ) );
  ColumnData columns( "TabulatedProbabilityDistribution", std::move( data ) );
  xss.insert( xss.end(), columns.begin(), columns.end() );

  return xss;
}
