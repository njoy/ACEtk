template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){

  try{
    this->PDF_ = std::move( details::verify::pdf( pdf ) );
    return *this;
  } catch( details::verify::exceptions::InvalidPDF& e ){
    Log::info( "Trouble constructing PDF values in "
               "tabulated angular distribution" );
    throw;
  }
}
