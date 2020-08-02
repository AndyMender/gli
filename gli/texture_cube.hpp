/// @brief Include to use cube map textures.
/// @file gli/texture_cube.hpp

#pragma once

#include "texture2d.hpp"

namespace gli {
  /// Cube map texture
  class texture_cube : public texture {
   public:
    using extent_type = extent2d;

   public:
    /// Create an empty texture cube
    texture_cube();

    /// Create a texture_cube and allocate a new storage_linear
    texture_cube(format_type Format, const extent_type& Extent, size_type Levels,
                 const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                               SWIZZLE_ALPHA));

    /// Create a texture_cube and allocate a new storage_linear with a complete mipmap chain
    texture_cube(format_type Format, const extent_type& Extent,
                 const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                               SWIZZLE_ALPHA));

    /// Create a texture_cube view with an existing storage_linear
    explicit texture_cube(const texture& Texture);

    /// Create a texture_cube view with an existing storage_linear
    texture_cube(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer,
                 size_type BaseFace, size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
                 const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                               SWIZZLE_ALPHA));

    /// Create a texture_cube view, reference a subset of an existing texture_cube instance
    texture_cube(const texture_cube& Texture, size_type BaseFace, size_type MaxFace, size_type BaseLevel,
                 size_type MaxLevel);

    /// Create a view of the texture identified by Face in the texture cube
    texture2d operator[](size_type Face) const;

    /// Return the dimensions of a texture instance: width and height where both should be equal.
    extent_type extent(size_type Level = 0) const;

    /// Fetch a texel from a texture. The texture format must be uncompressed.
    template <typename gen_type>
    gen_type load(const extent_type& TexelCoord, size_type Face, size_type Level) const;

    /// Write a texel to a texture. The texture format must be uncompressed.
    template <typename gen_type>
    void store(const extent_type& TexelCoord, size_type Face, size_type Level, const gen_type& Texel);
  };
}  // namespace gli

#include "./texture_cube.inl"
