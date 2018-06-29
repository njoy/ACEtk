class ENDFInterpolationParameters {
  Table::Slice NBT_;
  Table::Slice schemes_;

public:
#include "ACEtk/interpretation/ENDFInterpolationParameters/src/ctor.hpp"
#include "ACEtk/interpretation/ENDFInterpolationParameters/src/range.hpp"

  auto operator[]( int index ) const { 
    return std::make_pair( NBT_[ index ], schemes_[ index ] ); }
  auto at( int index ) const { 
    return std::make_pair( NBT_.at( index ), schemes_.at( index ) ); }

  auto NBT() const { return NBT_; }
  auto schemes() const { return schemes_; }
  auto size() const { return NBT_.size(); }
};
