Builder&
addPhotonProduction( PhotonProduction&& pp ){
  this->photonProduction_ = std::move( pp );
  return *this;
}
