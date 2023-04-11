static std::vector< double > generateXSS( std::vector< unsigned int >&& mts ) {

  std::vector< double > xss;
  auto ntr = mts.size();
  xss.reserve( ntr );
  xss.insert( xss.end(), mts.begin(), mts.end() );
  return xss;
}
