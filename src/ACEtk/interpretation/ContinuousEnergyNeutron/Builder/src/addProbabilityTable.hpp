Builder& addProbabilityTable( ProbabilityTable&& pTable ){
  this->probabilityTable_ = std::move( pTable );
  return *this;
}
