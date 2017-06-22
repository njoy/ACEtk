template< int... values, typename Ostream >
void print( Ostream& ostream ) const {
  this->header.print< values... >( ostream );
  this->data.print( ostream );
}
