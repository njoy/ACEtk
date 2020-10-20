void check(){
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
  if( not elasticScattering_ ){
    Log::error( "Elastic scattering cross section must exist "
                "before a table can be created." );
    throw std::exception();
  }
  else{
    try{ 
      details::verify::equalSize( 
        elasticScattering_.value().crossSection.energyGrid, 
        this->energyGrid_.value() );
    } catch( std::range_error& r ){
      Log::info( "Elastic scattering cross section has the wrong length." );
      throw;
    }
  }
}
