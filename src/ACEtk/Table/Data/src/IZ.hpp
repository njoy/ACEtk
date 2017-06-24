auto& IZ( std::size_t index ){
  return fetch( this->izaw, index, Index<0>() );
}

CONST_OVERLOAD( IZ )
