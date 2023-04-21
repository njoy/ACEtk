static std::vector< double > generateXSS( std::vector< Data >&& xs ) {

  std::size_t nr = xs.size();
  std::vector< double > xss( nr );
  std::size_t index = 0;
  for ( const auto& data : xs ) {

    xss[index] = xss.size() - nr + 1;
    xss.insert( xss.end(), data.begin(), data.end() );
    ++index;
  }

  return xss;
}
