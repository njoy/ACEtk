static std::vector< double >
generateXSS( double energy, double pdf, double cdf,
             std::vector< double >&& cosines ) {

  std::vector< double > xss = { energy, pdf, cdf };
  xss.insert( xss.end(), cosines.begin(), cosines.end() );
  return xss;
}
