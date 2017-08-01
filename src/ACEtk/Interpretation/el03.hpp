template< >
class Interpretation< El03 >{

  const Table& table;

public:
  Interpretation( const Table& table ) : table( table ) {}

  template< typename Tag >
  auto dependentVariable( const Tag ) const {
    const auto startOfDependent = table.data.JXS( Tag::dependentVariableBegin );
    const auto lengthOfDependent = table.data.NXS( Tag::dependentVariableLength );          
    return table.data.XSS( startOfDependent, lengthOfDependent );
  }

  template< typename Tag >
  auto independentVariable( const Tag ) const {
    const auto lengthOfData = table.data.NXS( Tag::dependentVariableLength );    
    const auto startOfData = table.data.JXS( Tag::dependentVariableBegin ) + lengthOfData;
    return table.data.XSS( startOfData, lengthOfData );
  }    
  
};
  
