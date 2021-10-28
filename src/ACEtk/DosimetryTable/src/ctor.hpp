DosimetryTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

DosimetryTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

DosimetryTable( const DosimetryTable& cetable ) :
  Table( cetable ) {

  this->generateBlocks();
}

DosimetryTable( DosimetryTable&& cetable ) :
  Table( std::move( cetable ) ) {

  this->generateBlocks();
}

DosimetryTable& operator=( const DosimetryTable& base ) {

  new (this) DosimetryTable( base );
  return *this;
}

DosimetryTable& operator=( DosimetryTable&& base ) {

  new (this) DosimetryTable( std::move( base ) );
  return *this;
}
