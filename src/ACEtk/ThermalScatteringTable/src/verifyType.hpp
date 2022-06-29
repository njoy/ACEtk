void verifyType() {

  char type = this->ZAID().back();
  if ( ( type != 't' ) ) {


    Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                "thermal scattering type (t)", this->ZAID() );
    throw std::exception();
  }
}
