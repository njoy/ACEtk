template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosineGrid( Range&& grid ){
  try{
    this->cosineGrid_ = details::verify::CosineBins< std::vector< double > >( 
        std::forward< Range >( grid ) );
    return *this;
  } catch( details::verify::exceptions::InvalidCosine& c ){
    Log::info( "Trouble encountered constructing cosine grid" );
    throw;
  }
}
