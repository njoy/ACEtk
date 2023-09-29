static void verifyLNU( unsigned int LNU ) {

  if ( LNU != 1 ) {

    Log::error( "Expected LNU = XSS(1) = 1 for a polynomial fission multiplicity "
                "representation" );
    Log::info( "XSS(1) value: {}", LNU );
    throw std::exception();
  }
}
