void verifyType() {

  char type = this->ZAID().back();
  if ( ( type != 'c' ) && ( type != 'h' ) && ( type != 'o' ) &&
       ( type != 'r' ) && ( type != 's' ) && ( type != 'a' ) ) {


    Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                "continuous energy type (c, h, o, r, s, a)", this->ZAID() );
    throw std::exception();
  }
}
