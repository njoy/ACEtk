static std::vector< double > generateXSS( std::vector< Data >&& blocks ) {

  const auto n = blocks.size();
  std::vector< double > energies( n );
  std::vector< double > lengths( n );
  std::vector< double > xss( n );

  std::size_t index = 0;
  for ( const auto& data : blocks ) {

    energies[index] = data.energy();
    lengths[index] = data.L();
    xss[index] = static_cast< double >( xss.size() - n );
    xss.insert( xss.end(), data.begin(), data.end() );
    ++index;
  }

  xss.insert( xss.begin(), lengths.begin(), lengths.end() );
  xss.insert( xss.begin(), energies.begin(), energies.end() );

  return xss;
}
