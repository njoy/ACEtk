static std::vector< double >
generateXSS( std::vector< std::array< unsigned int, 10 > >&& locators ) {

  std::vector< double > xss;
  const auto ntype = locators.size();
  xss.reserve( ntype * 10 );
  for ( const auto& array : locators ) {

    xss.insert( xss.end(), array.begin(), array.end() );
  }
  return xss;
}
