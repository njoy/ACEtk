class EL03 {
  const Table& table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  EL03( const Table& table ) : table( table ) {}

  auto atomicNumber() const { return Z( this->table ); }
  
  #include "ACEtk/interpretation/EL03/src/RadiativeStoppingPower.hpp"

  auto radiativeStoppingPower() const {
    return RadiativeStoppingPower{ this->table };
  }

  #include "ACEtk/interpretation/EL03/src/AtomicLevels.hpp"  

  auto atomicLevels() const {
    return AtomicLevels{ this->table };
  }      
  
};
  
