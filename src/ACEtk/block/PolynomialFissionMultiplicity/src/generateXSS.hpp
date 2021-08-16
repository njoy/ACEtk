static std::vector< double > generateXSS(
    std::vector< double >&& coefficients ) {

  std::vector< double > xss = { 1, static_cast< double >( coefficients.size() ) };
  xss.reserve( 2 + coefficients.size() );
  xss.insert( xss.end(), coefficients.begin(), coefficients.end() );

  return xss;
}
