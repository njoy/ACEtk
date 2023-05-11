static void
insertXSS( std::vector< double >& xss, const EvaporationSpectrum& distribution ) {

  xss.insert( xss.end(), distribution.begin(), distribution.end() );
}
