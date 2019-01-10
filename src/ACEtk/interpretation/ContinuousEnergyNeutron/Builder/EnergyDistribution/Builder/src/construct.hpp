EnergyDistribution construct(){
  auto makePairs = 
    []( double d, LAWS& law ){ return std::make_pair( d, std::move( law ) ); };

  auto pairs = ranges::view::zip_with( makePairs, probabilities_, laws_ )
      | ranges::to_vector;

  try{
    
    if( !boundaries_ != !schemes_ ){
      Log::error( "Tabulated boundaries and schemes must either be both "
                "specified or neither specified" );
      throw std::exception();
    }
    else if( ( not boundaries_ ) and ( not schemes_ ) ){
      return {
        lawTab{ std::nullopt,
                std::move( energies_ ),
                std::move( pairs ) } 
      };
    }
    return {
      lawTab{ std::make_pair( boundaries_.value(), schemes_.value() ),
              std::move( energies_ ),
              std::move( pairs ) } 
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating an EnergyDistribution" );
    Log::info( "Some component has not been defined" );
    throw;
  }

}
