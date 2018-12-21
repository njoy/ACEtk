template< typename Parent>
struct FormFactors{
  static constexpr int N = Parent::formFactorOffset();        
  std::reference_wrapper<const Table> table;

  FormFactors( const Table& table ) : table(table) {}

  auto scatteringCosines() const {
    const auto length =
      ( this->table.get().data.JXS( 3 + N )
	- this->table.get().data.JXS( 2 + N ) ) / ( 2 + N );
    const auto start =
      this->table.get().data.JXS( 2 + N );
    return this->table.get().data.XSS( start, length );
  }

  template< typename T = Parent,
	    std::enable_if_t<T::hasCumulativeFormFactor(), bool> = true >  
  auto cumulative() const {
    const auto length =
      ( this->table.get().data.JXS( 3 + N )
	- this->table.get().data.JXS( 2 + N ) ) / ( 2 + N );
    const auto start =
      this->table.get().data.JXS( 2 + N ) + length;
    return this->table.get().data.XSS( start, length );
  }

  auto differential() const {
    const auto length =
      ( this->table.get().data.JXS( 3 + N )
	- this->table.get().data.JXS( 2 + N ) ) / ( 2 + N );
    const auto start =
      this->table.get().data.JXS( 2 + N )
      + ( Parent::formFactorOffset() + 1 ) * length;    
    return this->table.get().data.XSS( start, length );
  }

};
