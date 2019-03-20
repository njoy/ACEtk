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
    auto grid = this->energyGrid_.value();
    auto total = this->totalXS_.value();
    auto disap = this->totalDisappearanceXS_.value();
    auto elast = this->reactions_[ 2 ].crossSection.values;
    auto heat  = this->heating_.value();

    this->nxs[ 2 ] = grid.size();
    this->jxs[ 0 ] = 1;

    this->xss.insert( xss.end(), grid.begin(), grid.end() );
    this->xss.insert( xss.end(), total.begin(), total.end() );
    this->xss.insert( xss.end(), disap.begin(), disap.end() );
    this->xss.insert( xss.end(), elast.begin(), elast.end() );
    this->xss.insert( xss.end(), heat.begin(), heat.end() );

  } catch( std::bad_optional_access& b ){
    Log::error( "Some component in the ESZ Block has not been built." );
    throw;
  }
}
