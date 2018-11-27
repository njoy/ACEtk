UnresolvedResonanceRange( int INTT, int ILF, int IOA, int IFF,
                          Slice energies, Slice ptables ):
  interpolationParameter_( INTT ),
  inelasticCompetition_( ILF ),
  otherAbsorption_( IOA ),
  factors_( IFF ),
  incidentEnergies_( energies ),
  probabilityTables_( makeProbabilityTables( ptables ) )
{
  if( ( interpolationParameter_ != 2 ) and ( interpolationParameter_ != 5 ) ) {
    njoy::Log::error( 
        "Invalid unresolved resonance range interpolation parameter: {}", 
        interpolationParameter_ );
    njoy::Log::info( "Valid values are 2 or 5" );
    throw std::range_error( 
        "Invalid unresolved resonance range interpolation parameter" );
  }
  
  if( ( factors_ != 0 ) and ( factors_ != 1 ) ){
     njoy::Log::error(
        "Invalid uresolved resonance range factors parameters: {}",
        factors_ );
     njoy::Log::info( "valid values are 0 or 1" );
     throw std::range_error(
        "Invalid uresolved resonance range factors flag" );
  }

  try{
    details::verify::isPositive( incidentEnergies_ );
  } catch( details::verify::exceptions::NotPositive& e ){
    njoy::Log::info( "Incident energy values must be positive" );
    throw;
  }
}

template< typename Range,
          utility::Require< true, utility::is_range, Range > = true,
          utility::Require< true, std::is_lvalue_reference, Range > = true
          >
UnresolvedResonanceRange( int INTT, int ILF, int IOA, int IFF,
                          Range&& energies, Range&& ptables ):
  UnresolvedResonanceRange( INTT, ILF, IOA, IFF,
                            Table::slice( energies ),
                            Table::slice( ptables ) )
{ }
