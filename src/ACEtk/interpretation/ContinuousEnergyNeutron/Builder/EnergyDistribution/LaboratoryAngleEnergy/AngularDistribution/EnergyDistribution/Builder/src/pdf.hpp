template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){
  this->cosineGrid_ = std::make_optional< dvCB< std::vector< double > > >( 
    std::move( pdf | ranges::to_vector ) );
  return *this;
}
