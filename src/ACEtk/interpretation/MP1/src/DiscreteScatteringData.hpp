struct DeflectionCosines{ static constexpr int offset = 1; };
struct CDF{ static constexpr int offset = 2; };

class DiscreteScatteringData{
  const Table& table;
  const std::map<int, int>& ACEptr;

  auto fetch( int offset, int order ) const {
    const auto length = this->table.data.NXS( 3 ) * order;
    const auto jxsIndex = this->ACEptr.find( order )->second + offset; 
    const auto start = this->table.data.JXS( jxsIndex );
    auto getEveryNth = [i=0, j=0, N=order] ( auto ) mutable
      { j = i; i = i + 1; return ( j % N  == 0 ); };
    return this->table.data.XSS( start, length )
      | ranges::view::sliding( order )
      | ranges::view::filter( getEveryNth );
  }
  
  template< typename Tag, typename... Args >
  auto fetch( Args... args ) const {
    return this->fetch( Tag::offset, std::forward<Args>(args)... );
  }
  
public:
  DiscreteScatteringData( const Table& table,
  		     const std::map<int, int>& ACEptr )
    : table( table ), ACEptr( ACEptr ) {}

  
 #include "ACEtk/interpretation/MP1/src/energyGrid.hpp"
  
  auto values( int order ) const {
    return ranges::view::zip( this->energyGrid(),
			      this->fetch< DeflectionCosines >( order ),
			      this->fetch< CDF >( order ) );
  }
  
};
