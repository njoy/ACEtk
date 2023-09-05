static std::vector< double > generateXSS( std::vector< Data >&& blocks ) {

  const auto n = blocks.size();
  std::vector< double > xss( n );
  std::size_t index = 0;
  for ( const auto& data : blocks ) {

    xss[index] = static_cast< double >( xss.size() - n + 1 );
    xss.insert( xss.end(), data.begin(), data.end() );
    ++index;
  }

  return xss;
}
