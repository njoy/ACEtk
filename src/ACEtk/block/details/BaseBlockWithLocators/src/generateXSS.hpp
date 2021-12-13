static std::vector< double > generateXSS( std::vector< Data >&& xs ) {

  std::size_t ntr = xs.size();
  std::vector< double > xss( ntr );
  std::size_t index = 0;
  for ( const auto& data : xs ) {

    xss[index] = xss.size() - ntr + 1;
    xss.insert( xss.end(), data.begin(), data.end() );
    ++index;
  }

  return xss;
}
