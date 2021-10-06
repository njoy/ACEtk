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

    // nothing to do to recover from the error: in is already in fail state
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
