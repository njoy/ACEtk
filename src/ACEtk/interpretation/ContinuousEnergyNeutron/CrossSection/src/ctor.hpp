CrossSection( Slice energies, Slice values ) :
  energyGrid_( energies ),
  values_( values )
{ 
  try{
    details::verify::equalSize(energyGrid_, values_);
  } catch( std::range_error& e ){
    njoy::Log::info( "Energy grid and cross section must have the same size" );
    throw e;
  }
}

template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
CrossSection( Range& energies, Range& values ):
  CrossSection( Slice{energies.begin(), energies.end() },
                Slice{values.begin(), values.end() } )
{ }
