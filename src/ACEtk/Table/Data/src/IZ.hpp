auto& IZ( std::size_t index ){
  return fetch( this->izaw.first, index );
}

CONST_OVERLOAD( IZ )

auto& IZ(){ return this->izaw.first; }
const auto& IZ() const { return this->izaw.first; }
