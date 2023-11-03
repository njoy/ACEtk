static std::vector< double >
generateXSS( ParameterData&& a, ParameterData&& b, double energy ) {

  std::vector< double > xss;
  xss.insert( xss.end(), a.begin(), a.end() );
  xss.insert( xss.end(), b.begin(), b.end() );
  xss.push_back( energy );

  return xss;
}
