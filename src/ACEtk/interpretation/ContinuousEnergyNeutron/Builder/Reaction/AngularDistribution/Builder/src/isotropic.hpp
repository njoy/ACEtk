Builder& isotropic() {
  this->representations_.emplace_back( Isotropic{} );
  return *this;
}
