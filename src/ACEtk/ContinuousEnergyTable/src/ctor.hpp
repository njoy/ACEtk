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
