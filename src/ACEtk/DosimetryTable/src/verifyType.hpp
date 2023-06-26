void verifyType() {

  char type = this->ZAID().back();
  if ( ( type != 'y' ) ) {


    Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                "dosimetry type (y)", this->ZAID() );
    throw std::exception();
  }
}
