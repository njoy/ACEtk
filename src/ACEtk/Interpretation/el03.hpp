template< >
class Interpretation< El03 >{

  const Table& table;

public:
  Interpretation( const Table& table ) : table( table ) {}

  template< typename Tag >
  auto energyGrid( const Tag ) const {
    return table.data.XSS( table.data.JXS( Tag::energyGridBegin ),
			   table.data.NXS( Tag::energyGridLength ) );
  }

  template< typename Tag >
  auto evaluations( const Tag ) const {
    const auto lengthOfEvaluation = table.data.NXS( Tag::length );
    return table.data.XSS( table.data.JXS( Tag::begin ) + Tag::offset * lengthOfEvaluation,
			   lengthOfEvaluation );
  }    
  
};
  
