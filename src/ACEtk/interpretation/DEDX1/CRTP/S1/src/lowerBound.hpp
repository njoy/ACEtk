auto lowerBound(const SubRange& range,
		 const Unit parameter) const {
  const auto& projection = static_cast<const Projection&>(*this);
  { 
    const auto bounds = this->computeBounds( range, projection );
    const bool ob =
      outOfBounds( parameter, std::get<0>(bounds), std::get<1>(bounds) );
  }
  return
    ranges::lower_bound( range, parameter, std::less<void>{}, projection );
}
