class DEDX1{

  Table table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  static int energySpacing( const Table& table ) { return table.data.XSS( 1 ); }
  static int densitySpacing( const Table& table ) { return table.data.XSS( 2 ); }
  static int temperatureSpacing( const Table& table ) { return table.data.XSS( 3 ); }    
  
public:
  DEDX1( Table&& table) : table(table){}

  auto atomicNumber() const { return Z( this->table ); }
  auto energySpacing() const { return energySpacing( this->table ); }
  auto densitySpacing() const { return densitySpacing( this->table ); }
  auto temperatureSpacing() const { return temperatureSpacing( this->table ); }      

};
