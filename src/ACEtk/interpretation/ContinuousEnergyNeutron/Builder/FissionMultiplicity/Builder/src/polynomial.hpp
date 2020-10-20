Polynomial::Builder polynomial(){ 
  if( this->nuType == "delayed" ){
    Log::error( 
        "delayed fission multiplicity must be given in tabulated form" );
    throw std::exception();
  }
  return Polynomial::Builder{ parent, this->nuType };
}
