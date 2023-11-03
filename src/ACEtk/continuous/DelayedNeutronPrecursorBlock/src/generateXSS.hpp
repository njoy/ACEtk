static std::vector< double >
generateXSS( std::vector< DelayedNeutronPrecursorData >&& groups ) {

  std::vector< double > xss;
  // commmenting this out for now - potential clash with user provided data
  // std::sort( groups.begin(), groups.end(),
  //            [] ( auto&& left, auto&& right )
  //               { return left.number() < right.number(); } );
  for ( const auto& group : groups ) {

    xss.insert( xss.end(), group.begin(), group.end() );
  }
  return xss;
}
