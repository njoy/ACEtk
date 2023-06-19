static std::vector< double >
generateXSS( double energy, std::vector< double >&& cosines ) {

  std::vector< double > xss = { energy };
  xss.insert( xss.end(), cosines.begin(), cosines.end() );
  return xss;
}
