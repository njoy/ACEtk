class EPR {
  Table table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  EPR( Table&& table ) : table( std::move(table) ) {}

  int atomicNumber() const {
    return Z( this->table );
  }

  #include "ACEtk/interpretation/EPR/CRTP.hpp"  
  #include "ACEtk/interpretation/EPR/Coherent.hpp"
  
  auto coherent() const {
    return Coherent( this->table );
  }
  
  #include "ACEtk/interpretation/EPR/Incoherent.hpp"
  
  auto incoherent() const {
    return Incoherent( this->table );
  }
  
};
