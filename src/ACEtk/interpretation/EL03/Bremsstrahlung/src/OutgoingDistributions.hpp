class OutgoingDistributions{
  const Table& table;

public:
  OutgoingDistributions( const Table& table ) : table( table ) {}
  
  auto photonElectronRatiosForEnergy() const {
    const auto length = this->table.data().NXS( 9 );
    const auto start  = this->table.data().JXS( 9 );
    return this->table.data().XSS( start, length );
  }

  auto photonElectronRatiosForAngle() const {
    const auto length = this->table.data().NXS( 10 );
    const auto start  = this->table.data().JXS( 10 );
    return this->table.data().XSS( start, length );
  }  
};



  


