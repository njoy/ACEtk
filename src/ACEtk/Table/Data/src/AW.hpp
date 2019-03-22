auto& AW( std::size_t index ){
  return fetch( this->izaw.second, index );
}

CONST_OVERLOAD( AW )

auto& AW(){ return this->izaw.second; }
const auto& AW() const { return this->izaw.second; }
