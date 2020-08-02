/// @brief Include to use 1d textures.
/// @file gli/texture1d.hpp

#pragma once

#include "image.hpp"
#include "texture.hpp"

namespace gli {
  /// 1d texture
  class texture1d : public texture {
   public:
    using extent_type = extent1d;

    /// Create an empty texture 1D
    texture1d();

    /// Create a texture1d and allocate a new storage_linear
    texture1d(format_type Format, const extent_type& Extent, size_type Levels,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture1d and allocate a new storage_linear with a complete mipmap chain
    texture1d(format_type Format, const extent_type& Extent,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture1d view with an existing storage_linear
    explicit texture1d(const texture& Texture);

    /// Create a texture1d view with an existing storage_linear
    texture1d(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer, size_type BaseFace,
              size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture1d view, reference a subset of an existing texture1d instance
    texture1d(const texture1d& Texture, size_type BaseLevel, size_type MaxLevel);

    /// Create a view of the image identified by Level in the mipmap chain of the texture
    image operator[](size_type Level) const;

    /// Return the width of a texture instance
    extent_type extent(size_type Level = 0) const;

    /// Fetch a texel from a texture. The texture format must be uncompressed.
    template <typename gen_type>
    gen_type load(const extent_type& TexelCoord, size_type Level) const;

    /// Write a texel to a texture. The texture format must be uncompressed.
    template <typename gen_type>
    void store(const extent_type& TexelCoord, size_type Level, const gen_type& Texel);
  };
}  // namespace gli

#include "./texture1d.inl"
