template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosines( Range&& cosines ){
  this->cosines_ = std::make_optional< dvCB< std::vector< double > > >( 
    std::move( cosines ) | ranges::to_vector );
  return *this;
}
