struct InvalidENDFInterpolationParameter: std::exception {
  using std::exception::exception;

  using std::exception::what;
  virtual const char* what(){ return "Invalid ENDF interpolation parameter"; }
};
