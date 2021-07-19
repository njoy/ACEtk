template< typename Ostream >
void print( Ostream& ostream ) const {

  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using IZAWLine = Record< Integer<7>, FixedPoint<11, 7>,
                           Integer<7>, FixedPoint<11, 7>,
                           Integer<7>, FixedPoint<11, 7>,
                           Integer<7>, FixedPoint<11, 7> >;

  IZAWLine::write( it,
                   this->IZ(1), this->AW(1), this->IZ(2), this->AW(2),
                   this->IZ(3), this->AW(3), this->IZ(4), this->AW(4) );
  IZAWLine::write( it,
                   this->IZ(5), this->AW(5), this->IZ(6), this->AW(6),
                   this->IZ(7), this->AW(7), this->IZ(8), this->AW(8) );
  IZAWLine::write( it,
                   this->IZ(9),  this->AW(9), this->IZ(10), this->AW(10),
                   this->IZ(11), this->AW(11), this->IZ(12), this->AW(12) );
  IZAWLine::write( it,
                   this->IZ(13), this->AW(13), this->IZ(14), this->AW(14),
                   this->IZ(15), this->AW(15), this->IZ(16), this->AW(16) );

  using NXSLine = Record< Integer<9>, Integer<9>,
                          Integer<9>, Integer<9>,
                          Integer<9>, Integer<9>,
                          Integer<9>, Integer<9> >;

  NXSLine::write( it,
                  this->XSS().size(), this->NXS(2), this->NXS(3), this->NXS(4),
                  this->NXS(5), this->NXS(6), this->NXS(7), this->NXS(8) );

  NXSLine::write( it,
                  this->NXS(9), this->NXS(10), this->NXS(11), this->NXS(12),
                  this->NXS(13), this->NXS(14), this->NXS(15), this->NXS(16) );

  using JXSLine = Record< Integer<9>, Integer<9>,
                          Integer<9>, Integer<9>,
                          Integer<9>, Integer<9>,
                          Integer<9>, Integer<9> >;

  JXSLine::write( it,
                  this->JXS(1), this->JXS(2), this->JXS(3), this->JXS(4),
                  this->JXS(5), this->JXS(6), this->JXS(7), this->JXS(8) );

  JXSLine::write( it,
                  this->JXS(9), this->JXS(10), this->JXS(11), this->JXS(12),
                  this->JXS(13), this->JXS(14), this->JXS(15), this->JXS(16) );

  JXSLine::write( it,
                  this->JXS(17), this->JXS(18), this->JXS(19), this->JXS(20),
                  this->JXS(21), this->JXS(22), this->JXS(23), this->JXS(24) );

  JXSLine::write( it,
                  this->JXS(25), this->JXS(26), this->JXS(27), this->JXS(28),
                  this->JXS(29), this->JXS(30), this->JXS(31), this->JXS(32) );

  auto remainingLines = this->XSS().size() / 4;
  auto remainingEntries = this->XSS().size() % 4;
  auto iterator = this->XSS().begin();

  using XSSLine = Record< Scientific< 20, 12 >,
                          Scientific< 20, 12 >,
                          Scientific< 20, 12 >,
                          Scientific< 20, 12 > >;

  while ( remainingLines-- ) {

    XSSLine::write( it, iterator[0], iterator[1], iterator[2], iterator[3] );
    std::advance( iterator, 4 );
  }

  if ( remainingEntries ) {

    while( remainingEntries-- ) {

      Scientific< 20, 12 >::write( *iterator, it );
      ++iterator;
    }
    Record<>::write( it );
  }
}
