class EPRData {
  Table table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  EPRData( Table&& table ) : table( std::move(table) ) {}

  int atomicNumber() const {
    return Z( this->table );
  }

  #include "ACEtk/interpretation/EPRData/CRTP.hpp"  
  #include "ACEtk/interpretation/EPRData/Coherent.hpp"
  
  auto coherent() const {
    return Coherent( this->table );
  }
  
  #include "ACEtk/interpretation/EPRData/Incoherent.hpp"
  
  auto incoherent() const {
    return Incoherent( this->table );
  }
  
};
