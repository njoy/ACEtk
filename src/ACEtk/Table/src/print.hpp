/**
 *  @brief Print the table
 *
 *  @param[in] ostream   the output stream to write to
 */
template< typename Ostream >
void print( Ostream& ostream ) const {

  this->header_.print( ostream );
  this->data_.print( ostream );
}
