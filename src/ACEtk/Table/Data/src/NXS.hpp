auto& NXS( std::size_t index ){ return fetch(this->nxs, index); }

CONST_OVERLOAD( NXS )

auto& NXS(){ return this->nxs; }
const auto& NXS() const{ return this->nxs; }
