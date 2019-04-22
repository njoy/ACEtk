template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){
  this->pdf_  = std::make_optional< 
    dvP< std::vector< double > > >( 
      std::move( pdf ) | ranges::to_vector );
  return *this;
}
