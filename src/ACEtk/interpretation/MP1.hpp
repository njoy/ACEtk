class EL03 {
  const Table& table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  EL03( const Table& table ) : table( table ) {}

  auto atomicNumber() const { return Z( this->table ); }

  #include "ACEtk/interpretation/MP1/src/TotalCrossSection.hpp"

  auto totalCrossSection( ) const {
    return TotalCrossSection{ this->table };
  }

  
  /*

  #include "ACEtk/interpretation/MP1/DiscreteScatteringAngles.hpp"

  auto discreteScatteringAngles( int N ) const {
    return DiscreteScatteringAngles{ this->table };
  }
  
  #include "ACEtk/interpretation/MP1/CummulativeDistributionFunction.hpp"

  auto cumulativeDistributionFunction( int N ) const {
    return TotalCrossSection{ this->table };
  } 
   
  */
};
  
