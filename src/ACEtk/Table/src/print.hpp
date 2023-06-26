/**
 *  @brief Print the table
 *
 *  @param[in] ostream   the output stream to write to
 */
template< typename Ostream >
void print( Ostream& ostream ) const {

  std::visit( [&ostream] ( const auto& header ) { header.print( ostream ); },
              this->header_ );
  this->data_.print( ostream );
}
