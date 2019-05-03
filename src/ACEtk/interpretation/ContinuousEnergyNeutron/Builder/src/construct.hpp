Table construct(){

  this->tableData_ = Table::Data{};
  decltype( auto ) tableData = this->tableData_.value();

  this->ESZ();

  decltype( auto ) getReaction = []( auto&& pair ) -> decltype( auto )
    { return pair.second; };
  decltype( auto ) getED = []( auto&& R ) -> decltype( auto )
    { return R.energyDistribution; };

  // Get all reactions that are neutron producing (including elastic scattering)
  decltype( auto ) neutronProducingReactions = 
    ranges::view::concat( 
      ranges::view::single( this->elasticScattering_.value() ),
      this->neutronProducingReactions_ | ranges::view::transform( getReaction )
    );

  int NTR = this->neutronProducingReactions_.size() + 
            this->nonNeutronProducingReactions_.size();
  tableData.NXS()[ 3 ] = NTR;
  int NR = ranges::distance( this->neutronProducingReactions_ );
  tableData.NXS()[ 4 ] = NR;

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
  this->DLW( 9, neutronProducingReactions 
            | ranges::view::transform( getED ) );

  try{
    tableData.NXS()[ 0 ] = tableData.XSS().size();
    
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
