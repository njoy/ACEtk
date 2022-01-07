static std::vector< double > generateXSS( std::vector< unsigned int >&& types ) {

  std::vector< double > xss;
  auto ntype = types.size();
  xss.reserve( ntype );
  xss.insert( xss.end(), types.begin(), types.end() );
  return xss;
}
