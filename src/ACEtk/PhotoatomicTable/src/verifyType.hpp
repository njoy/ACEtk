void verifyType() {

  char type = this->ZAID().back();
  if ( ( type != 'p' ) ) {


    Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                "photoatomic type (p)", this->ZAID() );
    throw std::exception();
  }
}
