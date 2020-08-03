namespace gli {
  inline texture_cube_array::texture_cube_array() {}

  inline texture_cube_array::texture_cube_array(format_type Format, const extent_type& Extent, size_type Layers,
                                                const swizzles_type& Swizzles)
      : texture(TARGET_CUBE_ARRAY, Format, texture::extent_type(Extent, 1), Layers, 6, gli::levels(Extent), Swizzles) {}

  inline texture_cube_array::texture_cube_array(format_type Format, const extent_type& Extent, size_type Layers,
                                                size_type Levels, const swizzles_type& Swizzles)
      : texture(TARGET_CUBE_ARRAY, Format, texture::extent_type(Extent, 1), Layers, 6, Levels, Swizzles) {}

  inline texture_cube_array::texture_cube_array(const texture& Texture)
      : texture(Texture, gli::TARGET_CUBE_ARRAY, Texture.format()) {}

  inline texture_cube_array::texture_cube_array(const texture& Texture, format_type Format, size_type BaseLayer,
                                                size_type MaxLayer, size_type BaseFace, size_type MaxFace,
                                                size_type BaseLevel, size_type MaxLevel, const swizzles_type& Swizzles)
      : texture(Texture, TARGET_CUBE_ARRAY, Format, BaseLayer, MaxLayer, BaseFace, MaxFace, BaseLevel, MaxLevel,
                Swizzles) {}

  inline texture_cube_array::texture_cube_array(const texture_cube_array& Texture, size_type BaseLayer,
                                                size_type MaxLayer, size_type BaseFace, size_type MaxFace,
                                                size_type BaseLevel, size_type MaxLevel)
      : texture(Texture, TARGET_CUBE_ARRAY, Texture.format(), Texture.base_layer() + BaseLayer,
                Texture.base_layer() + MaxLayer, Texture.base_face() + BaseFace, Texture.base_face() + MaxFace,
                Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel) {}

  inline texture_cube texture_cube_array::operator[](size_type Layer) const {
    GLI_ASSERT(Layer < this->layers());

    return texture_cube(*this, this->format(), this->base_layer() + Layer, this->base_layer() + Layer,
                        this->base_face(), this->max_face(), this->base_level(), this->max_level());
  }

  inline texture_cube_array::extent_type texture_cube_array::extent(size_type Level) const {
    return extent_type(this->texture::extent(Level));
  }

  template <typename gen_type>
  inline gen_type texture_cube_array::load(const extent_type& TexelCoord, size_type Layer, size_type Face,
                                           size_type Level) const {
    return this->texture::load<gen_type>(texture::extent_type(TexelCoord, 0), Layer, Face, Level);
  }

  template <typename gen_type>
  inline void texture_cube_array::store(const extent_type& TexelCoord, size_type Layer, size_type Face, size_type Level,
                                        const gen_type& Texel) {
    this->texture::store<gen_type>(texture::extent_type(TexelCoord, 0), Layer, Face, Level, Texel);
  }
}  // namespace gli
