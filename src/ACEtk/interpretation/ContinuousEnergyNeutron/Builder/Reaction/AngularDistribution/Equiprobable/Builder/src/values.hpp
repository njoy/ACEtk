template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& values( Range&& bins ){
  try{ 
    this->cosineBins_ = details::verify::CosineBins< std::array< double, 33 > >( 
            details::make_array< 33 > (bins ) );
    return *this;
  } catch( details::verify::exceptions::InvalidCosine& c ){
    Log::info( "Trouble encountered constructing cosine bins" );
    throw;
  }
}
