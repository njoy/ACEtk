template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& PDF( Range&& pdf ){

  try{
    this->PDF_ = std::move( pdf );
    return *this;
  } catch( details::verify::exceptions::InvalidPDF& e ){
    Log::info( "Trouble constructing PDF values in "
               "tabulated angular distribution" );
    throw;
  }
}
