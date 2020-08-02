#include "core/convert_func.hpp"

namespace gli {
  template <typename texture_type>
  inline texture_type convert(const texture_type& Texture, format Format) {
    using T float;
    using extent_type = typename texture::extent_type;
    using size_type = typename texture_type::size_type;
    using component_type = typename extent_type::value_type;
    using fetch_type = typename detail::convert<texture_type, T, defaultp>::fetchFunc;
    using write_type = typename detail::convert<texture_type, T, defaultp>::writeFunc;

    GLI_ASSERT(!Texture.empty());
    GLI_ASSERT(!is_compressed(Texture.format()) && !is_compressed(Format));

    fetch_type Fetch = detail::convert<texture_type, T, defaultp>::call(Texture.format()).Fetch;
    write_type Write = detail::convert<texture_type, T, defaultp>::call(Format).Write;

    texture Storage(Texture.target(), Format, Texture.texture::extent(), Texture.layers(), Texture.faces(),
                    Texture.levels(), Texture.swizzles());
    texture_type Copy(Storage);

    for (size_type Layer = 0; Layer < Texture.layers(); ++Layer)
      for (size_type Face = 0; Face < Texture.faces(); ++Face)
        for (size_type Level = 0; Level < Texture.levels(); ++Level) {
          const extent_type& Dimensions = Texture.texture::extent(Level);

          for (component_type k = 0; k < Dimensions.z; ++k)
            for (component_type j = 0; j < Dimensions.y; ++j)
              for (component_type i = 0; i < Dimensions.x; ++i) {
                const typename texture_type::extent_type Texelcoord(extent_type(i, j, k));
                Write(Copy, Texelcoord, Layer, Face, Level, Fetch(Texture, Texelcoord, Layer, Face, Level));
              }
        }

    return texture_type(Copy);
  }

}  // namespace gli
