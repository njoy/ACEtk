/* helper functions */
static constexpr const char*
name( const decltype(xss)& ){ return "XSS"; }

static constexpr const char*
name( const decltype(nxs)& ){ return "NXS"; }

static constexpr const char*
name( const decltype(jxs)& ){ return "JXS"; }

static constexpr const char*
name( const decltype(izaw)&, Index<0> ){ return "IZ"; }

static constexpr const char*
name( const decltype(izaw)&, Index<1> ){ return "AW"; }
