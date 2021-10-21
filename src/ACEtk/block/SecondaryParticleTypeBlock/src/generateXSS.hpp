static std::vector< double > generateXSS( std::vector< unsigned int >&& types ) {

  std::vector< double > xss;
  auto ntype = mts.size();
  xss.reserve( ntype );
  xss.insert( xss.begin(), types.begin(), types.end() );
  return xss;
}
