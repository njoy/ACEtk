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

    // mimic standard library behaviour: stream position has not changed and
    // stream state is in fail
    // nothing to do here: the constructor handles the stream state
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
