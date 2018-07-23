class EPRData {
  const Table& table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  EPRData( const Table& table ) : table( table ) {}

  #include "ACEtk/interpretation/EPRData/ESZG.hpp"
  
  auto eszg() const {
    return ESZG( this->table );
  }
  
};
