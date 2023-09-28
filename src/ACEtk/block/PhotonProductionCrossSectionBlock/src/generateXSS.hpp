static std::vector< double > generateXSS( std::vector< PhotonProductionData >&& xs, bool ) {

  const auto ntr = xs.size();
  std::vector< double > xss( ntr );
  std::size_t index = 0;
  for ( const auto& data : xs ) {

    xss[index] = xss.size() - ntr + 1;
    std::visit( [&xss] ( const auto& value )
                       { xss.insert( xss.end(), value.begin(), value.end() ); },
                 data );
    ++index;
  }

  return xss;
}
