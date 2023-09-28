class DiscreteData{
  const Table& table;
  const int order;
  const int start;
  
protected:
  #include "ACEtk/interpretation/MP1/src/fetch.hpp"
  #include "ACEtk/interpretation/MP1/src/findStartOfBlock.hpp"
  
public:
  DiscreteData( const Table& table, const int order )
    : table( table ),
      order( order ),
      start( findStartOfBlock( this->table,
			       this->order ) )
  {}

  #include "ACEtk/interpretation/MP1/src/totalCrossSection.hpp"

  auto deflectionCosines( ) const {
    return this->mu( );
  }
  
  auto cumulativeDistributions( ) const {
    return this->cdf( );
  }

};
