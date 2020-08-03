/// @brief Include to use 2d textures.
/// @file gli/texture2d.hpp

#pragma once

#include "image.hpp"
#include "texture.hpp"

namespace gli {
  /// 2d texture
  class texture2d : public texture {
   public:
    using extent_type = extent2d;

    /// Create an empty texture 2D.
    texture2d();

    /// Create a texture2d and allocate a new storage_linear.
    texture2d(format_type Format, const extent_type& Extent, size_type Levels,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture2d and allocate a new storage_linear with a complete mipmap chain.
    texture2d(format_type Format, const extent_type& Extent,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture2d view with an existing storage_linear.
    explicit texture2d(const texture& Texture);

    /// Create a texture2d view with an existing storage_linear.
    texture2d(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer, size_type BaseFace,
              size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
              const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

    /// Create a texture2d view, reference a subset of an existing texture2d instance.
    texture2d(const texture2d& Texture, size_type BaseLevel, size_type MaxLevel);

    /// Create a view of the image identified by Level in the mipmap chain of the texture.
    image operator[](size_type Level) const;

    /// Return the dimensions of a texture instance: width and height.
    extent_type extent(size_type Level = 0) const;

    /// Fetch a texel from a texture. The texture format must be uncompressed.
    template <typename gen_type>
    gen_type load(const extent_type& TexelCoord, size_type Level) const;

    /// Write a texel to a texture. The texture format must be uncompressed.
    template <typename gen_type>
    void store(const extent_type& TexelCoord, size_type Level, const gen_type& Texel);
  };
}  // namespace gli

#include "./texture2d.inl"
