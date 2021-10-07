/**
 *  @brief Print the xsdir
 *
 *  @param[in] ostream   the output stream to write to
 */
void print( std::ostream& ostream ) const {

  // print the atomic weight ratios
  ostream << "atomic weight ratios" << std::endl;
  int count = -1;
  for ( const auto& entry : this->atomicWeightRatios() ) {

    if ( entry.first == 1 || entry.first%1000 == 0 ) {

      if ( entry.first != 1 ) {

        ostream << std::endl;
      }
      count = -1;
    }

    if ( count != 0 && count%3 == 0 ) {

      ostream << std::endl << std::setw( 21 ) << ' ';
    }

    ostream << std::right;
    ostream << std::setw( 8 ) << entry.first;
    ostream << std::setw( 13 )<< std::fixed << std::setprecision( 8 ) << entry.second;

    ++count;
  }

  // print the directory
  ostream << std::endl;
  ostream << "directory" << std::endl;
  for ( const auto& entry : this->entries() ) {

    ostream << entry;
  }
}
