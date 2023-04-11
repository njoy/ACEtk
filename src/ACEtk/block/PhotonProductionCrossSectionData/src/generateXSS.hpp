static std::vector< double > generateXSS(
    std::size_t index,
    std::vector< double >&& values ) {

  std::vector< double > xss = { 13,
                                static_cast< double >( index ),
                                static_cast< double >( values.size() ) };
  xss.reserve( 3 + values.size() );
  xss.insert( xss.end(), values.begin(), values.end() );

  return xss;
}
