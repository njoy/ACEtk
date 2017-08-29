class MP1 {
  const Table& table;
  
  const std::map<int, int>
  ACEptr = { { 1, 2 }, { 2, 5 },
	     { 4, 8 }, { 8, 11 }, 
	     { 16, 14 } };
protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
  #include "ACEtk/interpretation/MP1/src/fetch.hpp"
  
public:
  MP1( const Table& table ) : table( table ) {}

  auto atomicNumber() const { return Z( this->table ); }

  #include "ACEtk/interpretation/MP1/src/energyGrid.hpp"  
  #include "ACEtk/interpretation/MP1/src/totalCrossSection.hpp"

  auto deflectionCosine( int order ){
    return this->fetch< DeflectionCosines >( order );
  }

  auto cummulativeDistribution( int order ){
    return this->fetch< CDF >( order );
  }  
  
};
