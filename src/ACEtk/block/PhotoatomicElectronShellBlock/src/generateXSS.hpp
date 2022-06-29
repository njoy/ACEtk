static std::vector< double > generateXSS( std::vector< unsigned int >&& electrons,
                                          std::vector< double >&& energies,
                                          std::vector< double >&& probabilities ) {

  std::vector< double > xss;
  xss.reserve( 3 * electrons.size() - 2 );
  xss.insert( xss.end(), electrons.begin(), electrons.end() );
  xss.insert( xss.end(), energies.begin(), energies.end() );
  xss.insert( xss.end(), probabilities.begin(), probabilities.end() );

  return xss;
}
