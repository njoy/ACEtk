Reaction::NeutronProducing constructNeutronProducing(){
  if( this->energyDistribution_.empty() ){
    if( this->MT_ != 2 ){
      Log::error( "An EnergyDistribution must be specified for neutron "
                   "producing reactions." );
      throw std::exception();
    }
  }

  try{ 
    return Reaction::NeutronProducing{ 
      MT_, 
      Q_.value(),
      neutronYield_.value_or( 0 )*
          static_cast< int >( neutronYieldReferenceFrame_.value_or( 
                  NeutronYieldReferenceFrame::LAB ) ),
      std::move( this->crossSection_.value() ),
      std::move( this->angularDistribution_ ),
      std::move( this->energyDistribution_ ),
      std::move( this->photonProduction_ )
    };
  } catch( std::bad_optional_access& ){
    Log::error( "Trouble when creating a Reaction::NeutronProducing object." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}
