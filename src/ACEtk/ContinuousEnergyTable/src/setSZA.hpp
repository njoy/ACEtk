void setSZA() {

  // check for S, Z, A in NXS(9), NXS(10) and NXS(11)
  // using MCNP rules
  if ( this->data().NXS(10) == 0 ) {

    unsigned int za = this->ZA();
    unsigned int a = za % 1000;
    unsigned int z = ( za - a ) / 1000;
    unsigned int s = 0;
    if ( z > 999 ) {

      unsigned int sz = z;
      z = z % 1000;
      s = ( sz - z ) / 1000;
    }

    if ( a != 999 ) {

      if ( a > 3 * z ) {

        a -= 400;
        s = 1;
        while ( a > 3 * z ) {

          a -= 100;
          ++s;
        }
      }

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