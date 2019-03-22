auto& JXS( std::size_t index ){ return fetch(this->jxs, index); }

CONST_OVERLOAD( JXS )

auto& JXS(){ return this->jxs; }
const auto& JXS() const{ return this->jxs; }
