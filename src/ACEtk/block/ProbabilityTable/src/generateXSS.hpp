static std::vector< double >
generateXSS( std::vector< double >&& probabilities,
             std::vector< double >&& total,
             std::vector< double >&& elastic,
             std::vector< double >&& fission,
             std::vector< double >&& capture,
             std::vector< double >&& heating ) {

  std::vector< double > xss;
  std::size_t bins = probabilities.size();
  xss.reserve( 6 * probabilities.size() );

  if ( ( total.size() != bins ) || ( elastic.size() != bins ) ||
       ( fission.size() != bins ) || ( capture.size() != bins ) ||
       ( heating.size() != bins ) ) {

    Log::error( "The size of data in the probability table are not the same" );
    Log::info( "Expected size = {}", bins );
    Log::info( "Found probabilities ize = {}", probabilities.size() );
    Log::info( "Found total ize = {}", total.size() );
    Log::info( "Found elastic ize = {}", elastic.size() );
    Log::info( "Found fission ize = {}", fission.size() );
    Log::info( "Found capture ize = {}", capture.size() );
    Log::info( "Found heating ize = {}", heating.size() );
    throw std::exception();
  }
  xss.insert( xss.end(), probabilities.begin(), probabilities.end() );
  xss.insert( xss.end(), total.begin(), total.end() );
  xss.insert( xss.end(), elastic.begin(), elastic.end() );
  xss.insert( xss.end(), fission.begin(), fission.end() );
  xss.insert( xss.end(), capture.begin(), capture.end() );
  xss.insert( xss.end(), heating.begin(), heating.end() );

  return xss;
}
