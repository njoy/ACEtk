/**
 *  @brief Print the xsdir
 *
 *  @param[in] ostream   the output stream to write to
 */
void print( std::ostream& ostream ) const {

  // print the directory
  ostream << "directory" << std::endl;
  for ( const auto& entry : this->entries() ) {

    ostream << entry;
  }
}
