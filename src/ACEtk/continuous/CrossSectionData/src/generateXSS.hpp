static std::vector< double > generateXSS(
    std::size_t index,
    std::vector< double >&& values ) {

  std::vector< double > xss = { static_cast< double >( index ),
                                static_cast< double >( values.size() ) };
  xss.reserve( 2 + values.size() );
  xss.insert( xss.end(), values.begin(), values.end() );

  return xss;
}
