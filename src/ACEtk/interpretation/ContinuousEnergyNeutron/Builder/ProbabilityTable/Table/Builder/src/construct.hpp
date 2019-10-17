Table construct(){

  try{ 
    if( not this->fissionXS_ ){
      this->fissionXS_ = details::verify::positive(
          ranges::view::repeat_n( 0.0, this->CDFs_.value().size() )
            | ranges::to_vector 
        );
    }


    if( not this->heating_ ){
      this->heating_ = details::verify::positive(
          ranges::view::repeat_n( 0.0, this->CDFs_.value().size() ) 
            | ranges::to_vector
        );
    }

    details::verify::equalSize(
      this->heating_.value(),
      this->fissionXS_.value(),
      this->totalXS_.value(),
      this->elasticXS_.value(),
      this->captureXS_.value()
    );
    return Table{
      std::move( CDFs_.value() ),
      std::move( totalXS_.value() ),
      std::move( elasticXS_.value() ),
      std::move( fissionXS_.value() ),
      std::move( captureXS_.value() ),
      std::move( heating_.value() )
    };
  } catch( std::range_error& e){
    Log::info( "totalXS, elasticXS, captureXS, fissionXS, CDFs, and heating"
               " must all be the same size." );
    throw;
  } catch( std::bad_optional_access& ){
    Log::error( "Some component of probabilityTable::Table not created." );
    throw;
  }

}
