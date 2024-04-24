void verifyType() {

  char type = this->ZAID().back();
  if ( ( type != 'u' ) ) {


    Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                "photonuclear type (u)", this->ZAID() );
    throw std::exception();
  }
}
