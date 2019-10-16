Builder&
addCrossSection( ContinuousEnergyNeutron::Builder::CrossSection&& XS ){
  this->crossSection_ = std::make_optional< MFType >(
      CrossSection{ this->MF, std::move( XS ) } );
  return *this;
}
