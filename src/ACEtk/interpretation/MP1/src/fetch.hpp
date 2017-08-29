struct DeflectionCosines{ static constexpr int offset = 1; };
struct CDF{ static constexpr int offset = 2; };

auto fetch( int offset, int order ) const {
  const auto length = this->table.data.NXS( 3 ) * order;
  const auto jxsIndex = this->ACEptr.find( order )->second + offset; 
  const auto start = this->table.data.JXS( jxsIndex );
  return this->table.data.XSS( start, length )
    | ranges::view::chunk( order );
}
  
template< typename Tag, typename... Args >
auto fetch( Args... args ) const {
  return this->fetch( Tag::offset, std::forward<Args>(args)... );
}
