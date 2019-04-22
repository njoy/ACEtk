template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cdf( Range&& cdf ){
 this->cdf_  = std::make_optional< 
   dvC< std::vector< double > > >( 
       std::move( cdf ) | ranges::to_vector 
   );
  return *this;
}

