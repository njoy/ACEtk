Builder&
addYields( Yields&& yields ){
  this->crossSection_ = std::make_optional< MFType >( std::move( yields ) );
  return *this;
}

