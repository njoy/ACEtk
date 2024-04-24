void setSZA() {

  // check for S, Z, A in NXS(9), NXS(10) and NXS(11)
  // using MCNP rules
  if ( ( this->data().NXS(9) == 0 ) &&
       ( this->data().NXS(10) == 0 ) &&
       ( this->data().NXS(11) == 0 ) ) {

    std::string zaid = this->ZAID();
    unsigned int za = std::stoi( zaid.substr( 0, zaid.size() - 4 ) );
    unsigned int a = za % 1000;
    unsigned int z = ( za - a ) / 1000;
    unsigned int s = 0;
    if ( z > 999 ) {

      unsigned int sz = z;
      z = z % 1000;
      s = ( sz - z ) / 1000;
    }

    if ( z != 999 ) { // z = 999 is considered an unphysical z value in MCNP

      // MCNP uses this formula to approximate the value of the atomic mass
      unsigned int estimate =
      static_cast< unsigned int >( std::round((0.0064*z+2.0009)*z-0.281));

      if ( ( a > 400 ) && ( a > estimate + 40 ) ) {

        a -= 400;
        s = 1;
        while ( ( a > 100 ) && ( a > estimate + 40 ) ) {

          a -= 100;
          ++s;
        }
      }

      // exception for Am242 and Am242m1 (Am242m1 has historically been
      // associated with the 95242 zaid value)
      if ( ( z == 95 ) && ( a == 242 ) ) {

        if ( s < 2 ) {

          s = s == 0 ? 1 : 0;
        }
      }
    }

    this->data().NXS(9) = s;
    this->data().NXS(10) = z;
    this->data().NXS(11) = a;
  }
}