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

  decltype( auto ) getRx = []( auto&& p ) -> decltype( auto )
    { return p.second; };
  decltype( auto ) ppFilter = []( auto&& pair ) ->decltype( auto )
    { return bool( pair.second.photonProduction ); };
  decltype( auto ) getPP = []( auto&& p ) -> decltype( auto )
    { return p.second.photonProduction.value(); };
  decltype( auto ) npRPP = this->neutronProducingReactions_
    | ranges::view::filter( ppFilter );
  decltype( auto ) nonnpRPP = this->nonNeutronProducingReactions_
    | ranges::view::filter( ppFilter );

  decltype( auto ) ppReactions = ranges::view::concat(
    npRPP | ranges::view::transform( getPP ),
    nonnpRPP | ranges::view::transform( getPP )
  );

  // Get all reactions that are neutron producing 
  // (including elastic scattering)
  decltype( auto ) neutronProducingReactions = 
    ranges::view::concat( 
      ranges::view::single( this->elasticScattering_.value() ),
      this->neutronProducingReactions_ | ranges::view::transform( getRx )
    );

  int NTR = this->neutronProducingReactions_.size() + 
            this->nonNeutronProducingReactions_.size();
  tData.NXS()[ 3 ] = NTR;
  int NR = ranges::distance( this->neutronProducingReactions_ );
  tData.NXS()[ 4 ] = NR;
  int NTRP = 
    ranges::distance( this->neutronProducingReactions_ 
                        | ranges::view::filter( ppFilter ) ) + 
    ranges::distance( this->nonNeutronProducingReactions_ 
                        | ranges::view::filter( ppFilter ) );
  tData.NXS()[ 5 ] = NTRP;

  this->NU();
  this->MTR( 2, 
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->LQR( 3,
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->SIG( 5,
             this->neutronProducingReactions_
              | ranges::view::transform( getRx ), 
             this->nonNeutronProducingReactions_
              | ranges::view::transform( getRx ) );
  this->AND( 7, neutronProducingReactions  );
  this->DLW( 9, this->neutronProducingReactions_
                  | ranges::view::transform( getRx ) );
  this->TYR( 4,
             this->neutronProducingReactions_, 
             this->nonNeutronProducingReactions_ );
  this->GPD();
  this->MTR( 12, npRPP, nonnpRPP );
  this->SIG( 13, npRPP | ranges::view::transform( getPP ), 
                 nonnpRPP | ranges::view::transform( getPP ) 
           );
  this->AND( 15, ppReactions );

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
