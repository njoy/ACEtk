/**
 *  @brief Print the entry
 *
 *  @param[in] ostream   the output stream to write to
 */
void print( std::ostream& ostream ) const {

  // print the entry
  std::ostringstream out;
  out << std::right;
  out << std::setw( 10 ) << this->ZAID();
  out << std::setw( 13 )<< std::fixed << std::setprecision( 6 ) << this->AWR();
  out << ' ' << this->fileName();
  out << ' ' << ( this->accessRoute() ? this->accessRoute().value() : "0" );
  out << ' ' << this->fileType();
  out << ' ' << this->address();
  out << ' ' << this->tableLength();
  if ( this->recordLength() && this->entriesPerRecord() ) {

    out << ' ' << this->recordLength().value()
        << ' ' << this->entriesPerRecord().value();
  }
  else {

    if ( this->temperature() || this->ptable() ) {

      out << " 0 0";
    }
  }
  if ( this->temperature() ){

    out << std::setw( 13 ) << std::scientific << std::setprecision( 6 )
        << this->temperature().value();
  }
  else {

    if ( this->ptable() ) {

      out << " 0";
    }
  }
  out << ( this->ptable() ? " ptable" : "" );
  out << std::endl;

  // check size and split as required (we assume we have to split more than once)
  std::string entry = out.str();
  if ( entry.size() > 100 ) {

    auto size = entry.size();
    while ( size > 100 ) {

      auto begin = entry.rbegin();
      auto iter = begin + size;
      while ( std::distance( begin, iter ) > 100 ) {

        begin = std::find( begin, iter, ' ' ) + 1; // move past the space
      }
      auto pos = std::distance( begin, entry.rend() );
      entry.insert( pos, " +\n    " );
      size = entry.size() - ( pos + 3 ); // remaining characters after the \n
    }
  }

  ostream << entry;
}
