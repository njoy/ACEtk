LAW24 construct(){
  this->y( std::move( tables_ ) );

  return TabBuilder::construct();
}
