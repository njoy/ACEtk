struct DeflectionCosines{ static constexpr int offset = 1; };
struct CDF{ static constexpr int offset = 2; };


class DiscreteScatteringData{
  const Table& table;
  const std::map<int, int>& ACEptr;

  auto fetch( int offset, int numberOfDiscretePoints ) const {
    const auto length = this->table.data.NXS( 3 ) * numberOfDiscretePoints;
    const auto startIndex = 
      this->ACEptr.find( numberOfDiscretePoints )->second + offset; 
    const auto start = this->table.data.JXS( startIndex );
    return this->table.data.XSS( start, length );   
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
  
  auto values( size_t numberOfAngles ) const {
    return ranges::view::zip( this->fetch< DeflectionCosines >( numberOfAngles ),
			      this->fetch< CDF >( numberOfAngles ) );
  }
  
};
