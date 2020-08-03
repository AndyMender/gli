/// @brief Include to use cube map array textures.
/// @file gli/texture_cube_array.hpp

#pragma once

#include "texture_cube.hpp"

namespace gli {
  /// Cube map array texture
  class texture_cube_array : public texture {
   public:
    using extent_type = extent2d;

    /// Create an empty texture cube array
    texture_cube_array();

    /// Create a texture_cube_array and allocate a new storage_linear
    texture_cube_array(format_type Format, const extent_type& Extent, size_type Layers, size_type Levels,
                       const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                                     SWIZZLE_ALPHA));

    /// Create a texture_cube_array and allocate a new storage_linear with a complete mipmap chain
    texture_cube_array(format_type Format, const extent_type& Extent, size_type Layers,
                       const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                                     SWIZZLE_ALPHA));

    /// Create a texture_cube_array view with an existing storage_linear
    explicit texture_cube_array(const texture& Texture);

    /// Reference a subset of an exiting storage_linear constructor
    texture_cube_array(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer,
                       size_type BaseFace, size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
                       const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                                     SWIZZLE_ALPHA));

    /// Create a texture view, reference a subset of an exiting texture_cube_array instance
    texture_cube_array(const texture_cube_array& Texture, size_type BaseLayer, size_type MaxLayer, size_type BaseFace,
                       size_type MaxFace, size_type BaseLevel, size_type MaxLevel);

    /// Create a view of the texture identified by Layer in the texture array
    texture_cube operator[](size_type Layer) const;

    /// Return the dimensions of a texture instance: width and height where both should be equal.
    extent_type extent(size_type Level = 0) const;

    /// Fetch a texel from a texture. The texture format must be uncompressed.
    template <typename gen_type>
    gen_type load(const extent_type& TexelCoord, size_type Layer, size_type Face, size_type Level) const;

    /// Write a texel to a texture. The texture format must be uncompressed.
    template <typename gen_type>
    void store(const extent_type& TexelCoord, size_type Layer, size_type Face, size_type Level, const gen_type& Texel);
  };
}  // namespace gli

#include "./texture_cube_array.inl"
