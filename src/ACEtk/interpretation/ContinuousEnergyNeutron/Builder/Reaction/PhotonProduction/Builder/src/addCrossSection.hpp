Builder&
addCrossSection( CrossSection&& XS ){
  this->crossSection_ = std::make_optional< MFType >( std::move( XS ) );
  return *this;
}
