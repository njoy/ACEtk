Tabulated construct(){

  try{
    details::verify::equalSize(
      this->cosineGrid_.value(),
      this->PDF_.value(),
      this->CDF_.value()
    );
    return Tabulated{
      std::move( interpolationFlag_.value() ),
          std::move( cosineGrid_.value() ),
          std::move( PDF_.value() ),
          std::move( CDF_.value() )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a "
                "Reaction::AngularDistribution::Tabulated object" );
    Log::info( "Some component has not been defined" );
    throw;
  } catch( std::range_error& e ){
    Log::error( "Trouble when creating a "
                "Reaction::AngularDistribution::Tabulated object" );
    Log::info( "cosine grid, pdf, and cdf, must all be the same size." );
    throw;
  }
}
