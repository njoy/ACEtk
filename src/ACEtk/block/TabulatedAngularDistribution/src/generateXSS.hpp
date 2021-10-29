static std::vector< double > generateXSS(
    int interpolation,
    std::vector< double >&& cosines,
    std::vector< double >&& pdf,
    std::vector< double >&& cdf ) {

  std::vector< double > xss = { static_cast< double >( interpolation ) };
  xss.reserve( 2 + 3 * cosines.size() );
  ColumnData data( "AND::TabulatedAngularDistribution",
                   std::move( cosines ), std::move( pdf ), std::move( cdf ) );
  xss.insert( xss.end(), data.begin(), data.end() );

  return xss;
}
