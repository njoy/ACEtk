void ESZ(){
  // check size of total cross section and energyGrid_
  try{ 
    details::verify::equalSize( this->totalXS_.value(), 
                                this->energyGrid_.value() );

  } catch( std::range_error& r ){
    Log::info( "Total cross section has the wrong length." );
    throw;
  }

  // Check size of heating_ and energyGrid_
  try{ 
    details::verify::equalSize( this->heating_.value(), 
                                this->energyGrid_.value() );

  } catch( std::range_error& r ){
    Log::info( "Heating cross section has the wrong length." );
    throw;
  }

  // Ensure total disappearance cross section is the right size
  try{ 
    details::verify::equalSize( 
      this->totalDisappearanceXS_.value(), this->energyGrid_.value() );

  } catch( std::range_error& r ){
    Log::info( "Total disappearance cross section has the wrong length." );
    throw;
  }

  // Ensure MT2 exists
  if( reactions_.find( 2 ) == reactions_.end() ){
    Log::error( "Elastic scattering cross section must exist "
                "before a table can be created." );
    throw std::exception();
  }
  else{
    try{ 
      details::verify::equalSize( 
        reactions_[ 2 ].crossSection.energyGrid, this->energyGrid_.value() );

    } catch( std::range_error& r ){
      Log::info( "Elastic scattering cross section has the wrong length." );
      throw;
    }
  }

  try{
    this->nxs[ 1 ] = this->SZA_.value();

    this->nxs[ 2 ] = this->energyGrid_.value().size();
    this->jxs[ 0 ] = 1;

    this->xss |= ranges::action::push_back( this->energyGrid_.value() );
    this->xss |= ranges::action::push_back( this->totalXS_.value() );
    this->xss |= ranges::action::push_back( 
        this->totalDisappearanceXS_.value() );
    this->xss |= ranges::action::push_back( 
        this->reactions_[ 2 ].crossSection.values );
    this->xss |= ranges::action::push_back( this->heating_.value() );

  } catch( std::bad_optional_access& b ){
    Log::error( "Some component in the ESZ Block has not been built." );
    throw;
  }
}
