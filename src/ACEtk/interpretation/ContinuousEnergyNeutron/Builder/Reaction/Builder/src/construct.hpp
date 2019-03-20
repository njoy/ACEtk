Reaction construct(){
  try{ 
    return Reaction{ 
      MT_, 
      Q_.value(),
      neutronYield_.value_or( 0 )*
          static_cast< int >( neutronYieldReferenceFrame_.value_or( 
                  NeutronYieldReferenceFrame::LAB ) ),
      std::move( this->crossSection_.value() ),
      std::move( this->angularDistribution_ ),
      std::move( this->energyDistribution_ )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a Reaction object" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
