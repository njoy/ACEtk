Equiprobable construct() {
  return Equiprobable{
    std::move( this->cosineBins_.value() )
  };
}
