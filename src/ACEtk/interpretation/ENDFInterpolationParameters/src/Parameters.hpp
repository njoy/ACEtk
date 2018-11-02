struct Parameters {
  int scheme_;
  Indices indices_;
  
  int scheme() const { return scheme_; }
  Indices indices() const { return indices_; }
};
