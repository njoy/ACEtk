/**
 *  @brief operator>> for xsdir entries
 *
 *  @param[in] in       the input stream
 *  @param[in] entry    the xsdir entry
 *
 *  @return the input stream
 */
inline std::istream &operator>>( std::istream& in, XsdirEntry& entry ) {

  try {

    XsdirEntry temp( in );
    entry = std::move( temp );
  }
  catch ( ... ) {

    // nothing to do to recover from the error: in is already in fail state
  }

  return in;
}

/**
 *  @brief operator<< for xsdir entries
 *
 *  @param[in] in       the output stream
 *  @param[in] entry    the xsdir entry
 *
 *  @return the input stream
 */
inline std::ostream &operator<<( std::ostream& out, const XsdirEntry& entry ) {

  entry.print( out );
  return out;
}
