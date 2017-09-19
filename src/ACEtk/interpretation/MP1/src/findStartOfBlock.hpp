static auto availableOrders( const Table& table ) {
  auto start = table.data.JXS( 1 );
  auto length = table.data.NXS( 5 );
  return table.data.XSS( start, length );
}

static auto startOfDiscreteBlock( const Table& table ) {
  auto start = table.data.JXS( 1 ) + table.data.NXS( 5 );
  auto length = table.data.NXS( 5 );
  return table.data.XSS( start, length ); 
}

static auto findStartOfBlock( const Table& table , const int order ) {

  auto lrnd = []( const auto x ){ return std::lround( x ); };
  auto orders = availableOrders( table )
    | ranges::view::transform( lrnd );

  auto starts = startOfDiscreteBlock( table )
    | ranges::view::transform( lrnd );
  
  auto zipOrdersWithStart = ranges::view::zip( orders, starts );
  
  auto foundIfThisIsTrue =
    [ order ]( const auto pair ) { return ( order == pair.first ); };
  
  auto pairContainingIndex = ranges::find_if( zipOrdersWithStart,
					      foundIfThisIsTrue );
  
  assert( pairContainingIndex != ranges::end( zipOrdersWithStart ) );

  return (*pairContainingIndex).second;
}
