static std::vector< std::vector< double > > generateArrays(
    std::vector< unsigned int > primary,
    std::vector< unsigned int > secondary,
    std::vector< double > energies,
    std::vector< double > probabilities ) {

  const auto nt = primary.size();

  if ( ( secondary.size() != nt ) || ( energies.size() != nt ) ||
       ( probabilities.size() != nt ) ) {

    Log::error( "The sizes of the transition data arrays are not consistent" );
    Log::info( "primary.size(): {}", nt );
    Log::info( "secondary.size(): {}", secondary.size() );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "probabilities.size(): {}", probabilities.size() );
    throw std::exception();
  }

  std::vector< std::vector< double > > arrays;

  for ( unsigned int index = 0; index < nt; ++index ) {

    std::vector< double > data( 4 );
    data[0] = static_cast< double >( primary[index] );
    data[1] = static_cast< double >( secondary[index] );
    data[2] = energies[index];
    data[3] = probabilities[index];
    arrays.emplace_back( std::move( data ) );
  }

  return arrays;
}
