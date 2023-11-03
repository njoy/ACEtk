static std::vector< double > generateXSS( std::vector< unsigned int >&& mts ) {

  const auto nyp = mts.size();
  std::vector< double > xss{ static_cast< double >( nyp ) };
  xss.reserve( nyp + 1 );
  xss.insert( xss.end(), mts.begin(), mts.end() );
  return xss;
}
