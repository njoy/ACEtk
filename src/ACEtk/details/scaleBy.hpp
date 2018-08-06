struct ScaleBy {
  template<typename T>
  auto operator()(T scale) const {
    return [scale](auto&& value){ return value * scale; };
  }
};

static constexpr ScaleBy scaleBy{};
