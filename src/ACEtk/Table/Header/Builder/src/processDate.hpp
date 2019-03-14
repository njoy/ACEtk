Builder& processDate( year_month_day&& date ){
  if( not date.ok() ){
    Log::error( "{} is an invalid process date", date );
    throw std::exception();
  }
  this->processDate_ = std::move( date );
  return *this;
}

Builder& processDate( int y, unsigned int m, unsigned int d ){
  return this->processDate( date::year{ y }/date::month{ m }/date::day{ d } );
}
