class OccupationNumber {
  const Table& table;

public:
  OccupationNumber( const Table& table ) : table( table ){}
    
  auto values() const {
    const auto length = this->table.data.NXS( 11 );
    const auto start  = this->table.data.JXS( 11 );
    return this->table.data.XSS( start, length );
  }
};
