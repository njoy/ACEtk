void verifyType() {

  char type = this->ZAID().back();
  if ( ( type != 'e' ) ) {


    Log::error( "The ZAID given in the ACE table ({}) does not appear to be an "
                "electron type (e)", this->ZAID() );
    throw std::exception();
  }
}
