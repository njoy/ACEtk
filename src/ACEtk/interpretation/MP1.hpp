class MP1 {
  const Table& table;
  
protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }

public:
  MP1( const Table& table ) : table( table ) {}
			      
  auto atomicNumber() const { return Z( this->table ); }
    
  #include "ACEtk/interpretation/MP1/src/energyGrid.hpp"  				         
  #include "ACEtk/interpretation/MP1/src/DiscreteData.hpp"

  auto discreteData( const int order ) const {
    return DiscreteData{ this->table, order };
  }

};
