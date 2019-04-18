Reaction::NonNeutronProducing constructNonNeutronProducing(){
  try{ 
    return Reaction::NonNeutronProducing{ 
      MT_, 
      Q_.value(),
      neutronYield_.value_or( 0 )*
          static_cast< int >( neutronYieldReferenceFrame_.value_or( 
                  NeutronYieldReferenceFrame::LAB ) ),
      std::move( this->crossSection_.value() )
    };
  } catch( std::bad_optional_access& ){
    Log::error( 
      "Trouble when creating a Reaction::NonNeutronProducing object." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}
