/**
 *  @brief Print the table
 *
 *  @param[in] ostream   the output stream to write to
 */
template< int... values, typename Ostream >
void print( Ostream& ostream ) const {

  this->header_.print< values... >( ostream );
  this->data_.print( ostream );
}
