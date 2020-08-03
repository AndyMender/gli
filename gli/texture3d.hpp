/// @brief Include to use 3d textures.
/// @file gli/texture3d.hpp

#pragma once

#include "image.hpp"
#include "texture.hpp"

namespace gli {
  /// 3d texture
  class texture3d : public texture {
   public:
    using extent_type = extent3d;

   public:
    /// Create an empty texture 3D
    texture3d();

    /// Create a texture3d and allocate a new storage_linear
    texture3d(format_type Format, const extent_type& Extent, size_type Levels,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture3d and allocate a new storage_linear with a complete mipmap chain
    texture3d(format_type Format, const extent_type& Extent,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture3d view with an existing storage_linear
    explicit texture3d(const texture& Texture);

    /// Create a texture3d view with an existing storage_linear
    texture3d(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer, size_type BaseFace,
              size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture3d view, reference a subset of an existing texture3d instance
    texture3d(const texture3d& Texture, size_type BaseLevel, size_type MaxLevel);

    /// Create a view of the image identified by Level in the mipmap chain of the texture
    image operator[](size_type Level) const;

    /// Return the dimensions of a texture instance: width, height and depth
    extent_type extent(size_type Level = 0) const;

    /// Fetch a texel from a texture. The texture format must be uncompressed.
    template <typename gen_type>
    gen_type load(const extent_type& TexelCoord, size_type Level) const;

    /// Write a texel to a texture. The texture format must be uncompressed.
    template <typename gen_type>
    void store(const extent_type& TexelCoord, size_type Level, const gen_type& Texel);
  };
}  // namespace gli

#include "./texture3d.inl"
