static
Reaction makeReaction( const Table& ACETable, int ){
  auto energies = EnergyGrid( ACETable ).energies();
}

Reaction makeReaction( int MT ) const {
  return makeReaction( this->table, MT );
}
