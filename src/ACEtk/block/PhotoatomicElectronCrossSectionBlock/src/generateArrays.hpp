static std::vector< std::vector< double > > generateArrays(
    std::vector< double > energies,
    std::vector< double > elastic,
    std::vector< double > bremsstrahlung,
    std::vector< double > excitation,
    std::vector< std::vector< double > > electroionisation ) {

  const auto ne = energies.size();
  const auto nssh = electroionisation.size();

  if ( electroionisation.size() == 0 ) {

    Log::error( "Expected at least 1 electroionisation cross section, found 0" );
    throw std::exception();
  }
  bool size = false;
  for ( const auto& values : electroionisation ) {

    if ( values.size() != ne ) {

      size = true;
    }
  }
  if ( ( elastic.size() != ne ) || ( bremsstrahlung.size() != ne ) ||
       ( excitation.size() != ne ) || size ) {

    Log::error( "The sizes of the principal cross sections are not consistent" );
    Log::info( "energies.size(): {}", ne );
    Log::info( "elastic.size(): {}", elastic.size() );
    Log::info( "bremsstrahlung.size(): {}", bremsstrahlung.size() );
    Log::info( "excitation.size(): {}", excitation.size() );
    unsigned int index = 0;
    for ( const auto& values : electroionisation ) {

      Log::info( "electroionisation.size() for subshell {}: {}", index, bremsstrahlung.size() );
      ++index;
    }
    throw std::exception();
  }

  std::vector< std::vector< double > > arrays;

  std::vector< double > total = elastic;
  std::vector< double > totalionisation = electroionisation.front();

  arrays.push_back( std::move( energies ) );
  arrays.push_back( std::move( elastic ) );
  arrays.push_back( std::move( bremsstrahlung ) );
  std::transform( arrays.back().cbegin(), arrays.back().cend(),
                  total.cbegin(), total.begin(), std::plus<>{} );
  arrays.push_back( std::move( excitation ) );
  std::transform( arrays.back().cbegin(), arrays.back().cend(),
                  total.cbegin(), total.begin(), std::plus<>{} );
  for ( unsigned int i = 0; i < nssh; ++i ) {

    arrays.push_back( std::move( electroionisation[i] ) );
    if ( i != 0 ) {

      std::transform( arrays.back().cbegin(), arrays.back().cend(),
                      totalionisation.cbegin(), totalionisation.begin(),
                      std::plus<>{} );
    }
  }
  std::transform( totalionisation.cbegin(), totalionisation.cend(),
                  total.cbegin(), total.begin(), std::plus<>{} );

  arrays.insert( std::next( arrays.begin(), 4 ), totalionisation );
  arrays.insert( std::next( arrays.begin() ), total );

  return arrays;
}
