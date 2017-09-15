static auto availableOrders( const Table& table ) {
  return table.data.XSS( 1, 5 );
}

static auto startOfDiscreteBlock( const Table& table ) {
  return table.data.XSS( 6, 5 );
}

static auto findStartOfBlock( const Table& table , const int order ) {

  auto zipOrdersWithStart = ranges::view::zip( availableOrders( table ),
					       startOfDiscreteBlock( table ) );
  auto foundIfThisIsTrue =
    [ order ]( const auto pair ) { return ( std::abs( double( order ) - pair.first ) < 1e-10 ); };
  
  auto pairContainingIndex = ranges::find_if( zipOrdersWithStart,
					      foundIfThisIsTrue );
  
  assert( pairContainingIndex != ranges::end( zipOrdersWithStart ) );

  return (*pairContainingIndex).second;
}
