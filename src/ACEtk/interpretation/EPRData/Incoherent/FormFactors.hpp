struct FormFactors{

  std::reference_wrapper<const Table> table;

  FormFactors( const Table& table ) : table(table) {}

  auto independentVariable() const {
    const auto length =
      ( this->table.get().data.JXS( 3 )
      - this->table.get().data.JXS( 2 ) ) / 2;
    const auto start =
      this->table.get().data.JXS( 2 );
    return this->table.get().data.XSS( start, length );
  }
  
  auto differential() const {
    const auto length =
      ( this->table.get().data.JXS( 3 )
      - this->table.get().data.JXS( 2 ) ) / 2;
    const auto start =
      this->table.get().data.JXS( 2 ) + length;    
    return this->table.get().data.XSS( start, length );
  }

};
