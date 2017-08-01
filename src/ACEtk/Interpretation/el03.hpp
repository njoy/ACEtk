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
    const auto lengthOfRadStoppingPower = table.data.NXS( Tag::radStoppingPowerLength );
    return table.data.XSS( table.data.JXS( Tag::radStoppingPowerBegin ) + lengthOfRadStoppingPower,
			   lengthOfRadStoppingPower );
  }    
  
};
  
