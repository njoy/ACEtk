Builder& spectrum( S&& spectrum ){
  this->spectrum_ = std::move( spectrum );
  return *this;
}
