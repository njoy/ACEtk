ContinuousEnergyTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

ContinuousEnergyTable( const ContinuousEnergyTable& cetable ) :
  Table( cetable ) {

  this->generateBlocks();
}

ContinuousEnergyTable( ContinuousEnergyTable&& cetable ) :
  Table( std::move( cetable ) ) {

  this->generateBlocks();
}

ContinuousEnergyTable& operator=( const ContinuousEnergyTable& base ) {

  new (this) ContinuousEnergyTable( base );
  return *this;
}

ContinuousEnergyTable& operator=( ContinuousEnergyTable&& base ) {

  new (this) ContinuousEnergyTable( std::move( base ) );
  return *this;
}
