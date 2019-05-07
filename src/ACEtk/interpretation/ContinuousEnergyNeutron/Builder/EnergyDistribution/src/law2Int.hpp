static int law2Int( LAWS& law ){
  constexpr static std::array< int, 14 > keys{{
    1, 2, 3, 4, 5, 7, 9, 11, 22, 24, 44, 61, 66, 67 }};
  return keys[ law.index() ];
}
