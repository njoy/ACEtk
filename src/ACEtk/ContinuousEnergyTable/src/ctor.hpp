ContinuousEnergyTable( const ContinuousEnergyTable& ) = default;
ContinuousEnergyTable( ContinuousEnergyTable&& ) = default;

ContinuousEnergyTable( const Table& table ): Table( table ) {}

ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {}
