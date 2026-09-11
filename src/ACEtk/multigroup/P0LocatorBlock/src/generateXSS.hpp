static std::vector< double >
generateXSS( std::vector< unsigned int >&& locators ) {

  std::vector< double > xss;
  const auto nsec = locators.size() - 1;
  xss.reserve( nsec + 1 );
  xss.insert( xss.end(), locators.begin(), locators.end() );
  return xss;
}
