include "levels.hpp"

namespace gli {
  inline texture1d::texture1d() {}

  inline texture1d::texture1d(format_type Format, const extent_type& Extent, const swizzles_type& Swizzles)
      : texture(TARGET_1D, Format, texture::extent_type(Extent.x, 1, 1), 1, 1, gli::levels(Extent), Swizzles) {}

  inline texture1d::texture1d(format_type Format, const extent_type& Extent, size_type Levels,
                              const swizzles_type& Swizzles)
      : texture(TARGET_1D, Format, texture::extent_type(Extent.x, 1, 1), 1, 1, Levels, Swizzles) {}

  inline texture1d::texture1d(const texture& Texture) : texture(Texture, TARGET_1D, Texture.format()) {}

  inline texture1d::texture1d(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer,
                              size_type BaseFace, size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
                              const swizzles_type& Swizzles)
      : texture(Texture, TARGET_1D, Format, BaseLayer, MaxLayer, BaseFace, MaxFace, BaseLevel, MaxLevel, Swizzles) {}

  inline texture1d::texture1d(const texture1d& Texture, size_type BaseLevel, size_type MaxLevel)
      : texture(Texture, TARGET_1D, Texture.format(), Texture.base_layer(), Texture.max_layer(), Texture.base_face(),
                Texture.max_face(), Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel) {}

  inline image texture1d::operator[](texture1d::size_type Level) const {
    GLI_ASSERT(Level < this->levels());

    return image(this->Storage, this->format(), this->base_layer(), this->base_face(), this->base_level() + Level);
  }

  inline texture1d::extent_type texture1d::extent(size_type Level) const {
    return extent_type(this->texture::extent(Level));
  }

  template <typename gen_type>
  inline gen_type texture1d::load(const extent_type& TexelCoord, size_type Level) const {
    return this->texture::load<gen_type>(texture::extent_type(TexelCoord.x, 0, 0), 0, 0, Level);
  }

  template <typename gen_type>
  inline void texture1d::store(const extent_type& TexelCoord, size_type Level, const gen_type& Texel) {
    this->texture::store<gen_type>(texture::extent_type(TexelCoord.x, 0, 0), 0, 0, Level, Texel);
  }
}  // namespace gli
