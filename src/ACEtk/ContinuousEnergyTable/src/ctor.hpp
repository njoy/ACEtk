ContinuousEnergyTable( const ContinuousEnergyTable& ) = default;
ContinuousEnergyTable( ContinuousEnergyTable&& ) = default;

ContinuousEnergyTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}
