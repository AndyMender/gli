#include "levels.hpp"

namespace gli {
  inline texture3d::texture3d() {}

  inline texture3d::texture3d(format_type Format, const extent_type& Extent, const swizzles_type& Swizzles)
      : texture(TARGET_3D, Format, Extent, 1, 1, gli::levels(Extent), Swizzles) {}

  inline texture3d::texture3d(format_type Format, const extent_type& Extent, size_type Levels,
                              const swizzles_type& Swizzles)
      : texture(TARGET_3D, Format, Extent, 1, 1, Levels, Swizzles) {}

  inline texture3d::texture3d(const texture& Texture) : texture(Texture, TARGET_3D, Texture.format()) {}

  inline texture3d::texture3d(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer,
                              size_type BaseFace, size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
                              const swizzles_type& Swizzles)
      : texture(Texture, TARGET_3D, Format, BaseLayer, MaxLayer, BaseFace, MaxFace, BaseLevel, MaxLevel, Swizzles) {}

  inline texture3d::texture3d(const texture3d& Texture, size_type BaseLevel, size_type MaxLevel)
      : texture(Texture, TARGET_3D, Texture.format(), Texture.base_layer(), Texture.max_layer(), Texture.base_face(),
                Texture.max_face(), Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel) {}

  inline image texture3d::operator[](size_type Level) const {
    GLI_ASSERT(Level < this->levels());

    return image(this->Storage, this->format(), this->base_layer(), this->base_face(), this->base_level() + Level);
  }

  inline texture3d::extent_type texture3d::extent(size_type Level) const {
    return extent_type(this->texture::extent(Level));
  }

  template <typename gen_type>
  inline gen_type texture3d::load(const extent_type& TexelCoord, size_type Level) const {
    return this->texture::load<gen_type>(texture::extent_type(TexelCoord), 0, 0, Level);
  }

  template <typename gen_type>
  inline void texture3d::store(const extent_type& TexelCoord, size_type Level, const gen_type& Texel) {
    this->texture::store<gen_type>(texture::extent_type(TexelCoord), 0, 0, Level, Texel);
  }
}  // namespace gli
