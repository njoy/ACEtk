Table construct(){

  try{ 
  equalSize( this->totalXS_.value(), "total cross section" );
  equalSize( this->elasticXS_.value(), "elastic cross section" );
  equalSize( this->captureXS_.value(), "capture cross section" );
  } catch( std::bad_optional_access& ){
    Log::error( "Some component of probabilityTable::Table not created." );
    throw;
  }

  if( this->fissionXS_ ){
    equalSize( this->fissionXS_.value(), "fission cross section" );
  } else{
    this->fissionXS_ = std::make_optional<
      dvP< std::vector< double > > >(
        ranges::view::repeat_n( 0.0, this->CDFs_.value().size() )
          | ranges::to_vector 
      );
  }


  if( this->heating_ ){
    equalSize( this->heating_.value(), "heating" );
  } else{
    this->heating_ = std::make_optional<
      dvP< std::vector< double > > >(
        ranges::view::repeat_n( 0.0, this->CDFs_.value().size() ) 
          | ranges::to_vector
      );
  }

  return Table{
    std::move( CDFs_.value() ),
    std::move( totalXS_.value() ),
    std::move( elasticXS_.value() ),
    std::move( fissionXS_.value() ),
    std::move( captureXS_.value() ),
    std::move( heating_.value() )
  };
}
