Builder&
addCrossSection( CrossSection&& XS ){
  this->totalFissionXS_ = std::move( XS );
  return *this;
}

