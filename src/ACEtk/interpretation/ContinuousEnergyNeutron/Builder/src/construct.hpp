Table construct(){

  this->tableData_ = Table::Data{};
  decltype( auto ) tData = this->tableData_.value();

  if( this->SZA_ ){
    int SZA = this->SZA_.value();

    int A = SZA%int( 1E3 );
    int Z = ( SZA%int( 1E6 ) - A )/int( 1E3 );
    int S = ( SZA%int( 1E7 ) - Z*int( 1E3 ) - A )/int( 1E3 );

    tData.NXS()[ 8  ] = S;
    tData.NXS()[ 9  ] = Z;
    tData.NXS()[ 10 ] = A;
  }

  this->ESZ();

  decltype( auto ) getReaction = []( auto&& pair ) -> decltype( auto )
    { return pair.second; };
  decltype( auto ) getED = []( auto&& R ) -> decltype( auto )
    { return R.energyDistribution; };

  // Get all reactions that are neutron producing 
  // (including elastic scattering)
  decltype( auto ) neutronProducingReactions = 
    ranges::view::concat( 
      ranges::view::single( this->elasticScattering_.value() ),
      this->neutronProducingReactions_ | ranges::view::transform( getReaction )
    );

  int NTR = this->neutronProducingReactions_.size() + 
            this->nonNeutronProducingReactions_.size();
  tData.NXS()[ 3 ] = NTR;
  int NR = ranges::distance( this->neutronProducingReactions_ );
  tData.NXS()[ 4 ] = NR;
  int NTRP = ranges::distance( this->photonProductionReactions_ );
  tData.NXS()[ 5 ] = NTRP;

  this->NU();
  this->MTR( 2, 
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->LQR( 3,
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->TYR( 4,
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->SIG( 5,
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->AND( 7, neutronProducingReactions  );
  this->DLW( 9, this->neutronProducingReactions_
            | ranges::view::transform( getReaction )
            | ranges::view::transform( getED ) );
  // this->GPD(...);
  this->MTRP( 12, this->photonProductionReactions_ );
  this->SIGP( 14, this->photonProductionReactions_ );

  try{
    tData.NXS()[ 0 ] = tData.XSS().size();
    
    return 
      Table{ 
        std::move( this->header_.value() ), 
        std::move( this->tableData_.value() )
      };

  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a Continous Energy Neutron Table" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
