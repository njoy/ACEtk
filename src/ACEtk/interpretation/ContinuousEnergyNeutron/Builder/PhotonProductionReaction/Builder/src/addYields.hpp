Builder&
addYields( Tabulated1D&& yields ){
  this->crossSection_ = std::move( yields );
  return *this;
}

