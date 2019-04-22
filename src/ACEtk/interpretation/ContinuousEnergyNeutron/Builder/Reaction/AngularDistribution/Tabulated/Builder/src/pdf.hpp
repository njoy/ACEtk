template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){

  try{
    this->PDF_  = std::make_optional< 
      dvP< std::vector< double > > >( 
        std::move( pdf ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::InvalidPDF& e ){
    Log::info( "Trouble constructing PDF values in "
               "tabulated angular distribution" );
    throw;
  }
}
