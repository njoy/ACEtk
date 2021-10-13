/**
 *  @brief operator>> for an xsdir
 *
 *  @param[in] in       the input stream
 *  @param[in] entry    the xsdir
 *
 *  @return the input stream
 */
inline std::istream &operator>>( std::istream& in, Xsdir& xsdir ) {

  try {

    Xsdir temp( in );
    xsdir = std::move( temp );
  }
  catch ( ... ) {

    // mimic standard library behaviour: stream position has not changed and
    // stream state is in fail
    // nothing to do here: the constructor handles the stream state
  }

  return in;
}

/**
 *  @brief operator<< for an xsdir
 *
 *  @param[in] in       the output stream
 *  @param[in] xsdir    the xsdir
 *
 *  @return the input stream
 */
inline std::ostream &operator<<( std::ostream& out, Xsdir& xsdir ) {

  xsdir.print( out );
  return out;
}
