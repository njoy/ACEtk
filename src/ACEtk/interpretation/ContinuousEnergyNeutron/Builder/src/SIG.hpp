template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void SIG(int indexJXS, int NMT, Range&& reactions ){

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  // LSIG(P) Block
  auto LXS = xss.size() + 1;
  jxs[ indexJXS ] = LXS;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );
  LXS += NMT;

  auto enumerated = ranges::view::enumerate( reactions );

  // SIG(P) Block
  jxs[ indexJXS + 1 ] = xss.size() + 1;
  for( auto it = enumerated.begin(); it != enumerated.end(); ++it ){

    auto index = std::get< 0 >( *it );
    auto reac = std::get< 1 >( *it );
    xss[ LXS + index - 1 ] = xss.size() - LXS + 2;

    reac.ACEify( tData );

  }
}
