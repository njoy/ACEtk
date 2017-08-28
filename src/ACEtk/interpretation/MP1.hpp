class MP1 {
  const Table& table;
  
  const std::map<int, int>
  numAnglesToAcePtr = { { 1, 2 }, { 2, 5 },
			{ 4, 8 }, { 8, 11 }, 
			{ 16, 14 } };
protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  MP1( const Table& table ) : table( table ) {}

  auto atomicNumber() const { return Z( this->table ); }

  #include "ACEtk/interpretation/MP1/src/TotalCrossSection.hpp"

  auto totalCrossSection( ) const {
    return TotalCrossSection{ this->table, this->numAnglesToAcePtr };
  }

  #include "ACEtk/interpretation/MP1/src/DiscreteScatteringData.hpp"

  auto discreteScatteringData( ) const {
    return DiscreteScatteringData{ this->table, this->numAnglesToAcePtr };
  }
  
};
