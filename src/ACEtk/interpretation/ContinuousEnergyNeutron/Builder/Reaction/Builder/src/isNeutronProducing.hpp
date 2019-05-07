bool isNeutronProducing() const{
  if( ( MT_ > 100 ) or ( MT_ == 4 ) ){
    return false;
  } else {
    return true;
  }
}
