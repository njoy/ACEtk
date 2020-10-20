Builder& addHeader( Table::Header&& header ){
  this->header_ = std::move( header );
  return *this;
}
