class DEDX1{

  njoy::ACEtk::Table table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  static auto energySpacing( const Table& table ) { return table.data.XSS( 1 ); }
  static auto densitySpacing( const Table& table ) { return table.data.XSS( 2 ); }
  static auto temperatureSpacing( const Table& table ) { return table.data.XSS( 3 ); }    

   #include "ACEtk/interpretation/DEDX1/CRTP.hpp" 
  
public:
  DEDX1( Table&& table) : table(std::move(table)){}

  auto atomicNumber() const { return Z( this->table ); }
  auto energySpacing() const { return energySpacing( this->table ); }
  auto densitySpacing() const { return densitySpacing( this->table ); }
  auto temperatureSpacing() const { return temperatureSpacing( this->table ); }

  #include "ACEtk/interpretation/DEDX1/StandardWithoutCutoff.hpp"
  
  auto standardWithoutCutoff() const {
    return StandardWithoutCutoff{this->table};
  }

};
