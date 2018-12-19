Tabulated construct(){
  equalSize( this->PDF_, "PDF" );
  equalSize( this->CDF_, "CDF");

  try{
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
  }
}
