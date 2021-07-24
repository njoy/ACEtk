static std::vector< double >
generateXSS( std::vector< double >&& energies,
             std::vector< double >&& total,
             std::vector< double >&& disappearance,
             std::vector< double >&& elastic,
             std::vector< double >&& heating ) {

  std::vector< double > xss( std::move( energies ) );
  auto nes = xss.size();
  xss.reserve( 5 * nes );

  if ( ( total.size() != nes ) || ( disappearance.size() != nes ) ||
       ( elastic.size() != nes ) || ( heating.size() != nes ) ) {

    Log::error( "The size of the ESZ subranges are not consistent" );
    Log::info( "NES value: {}", nes );
    Log::info( "energies.size(): {}", nes );
    Log::info( "total.size(): {}", total.size() );
    Log::info( "disappearance.size(): {}", disappearance.size() );
    Log::info( "elastic.size(): {}", elastic.size() );
    Log::info( "heating.size(): {}", heating.size() );
    throw std::exception();
  }

  xss.insert( xss.end(), total.begin(), total.end() );
  xss.insert( xss.end(), disappearance.begin(), disappearance.end() );
  xss.insert( xss.end(), elastic.begin(), elastic.end() );
  xss.insert( xss.end(), heating.begin(), heating.end() );

  return xss;
}
