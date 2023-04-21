static std::vector< double >
generateXSS( std::vector< DelayedNeutronPrecursorData >&& groups ) {

  std::vector< double > xss;
  for ( const auto& group : groups ) {

    xss.insert( xss.end(), group.begin(), group.end() );
  }
  return xss;
}
