Tabulated construct(){
  equalSize( this->PDF_, "PDF" );
  equalSize( this->CDF_, "CDF");

  return Tabulated{
    std::move( interpretationFlag_.value() ),
    std::move( cosineGrid_.value() ),
    std::move( PDF_.value() ),
    std::move( CDF_.value() )
  };
}
