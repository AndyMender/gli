/// @brief Include to use 1d array textures.
/// @file gli/texture1d_array.hpp

#pragma once

#include "texture1d.hpp"

namespace gli {
  /// 1d array texture
  class texture1d_array : public texture {
   public:
    using extent_type = extent1d;

   public:
    /// Create an empty texture 1D array
    texture1d_array();

    /// Create a texture1d_array and allocate a new storage_linear
    texture1d_array(format_type Format, const extent_type& Extent, size_type Layers, size_type Levels,
                    const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                                  SWIZZLE_ALPHA));

    /// Create a texture1d_array and allocate a new storage_linear with a complete mipmap chain
    texture1d_array(format_type Format, const extent_type& Extent, size_type Layers,
                    const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                                  SWIZZLE_ALPHA));

    /// Create a texture1d_array view with an existing storage_linear
    explicit texture1d_array(const texture& Texture);

    /// Create a texture1d_array view with an existing storage_linear
    texture1d_array(const texture& Texture, format_type Format, size_type BaseLayer, size_type MaxLayer,
                    size_type BaseFace, size_type MaxFace, size_type BaseLevel, size_type MaxLevel,
                    const swizzles_type& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE,
                                                                  SWIZZLE_ALPHA));

    /// Create a texture view, reference a subset of an exiting storage_linear
    texture1d_array(const texture1d_array& Texture, size_type BaseLayer, size_type MaxLayer, size_type BaseLevel,
                    size_type MaxLevel);

    /// Create a view of the texture identified by Layer in the texture array
    texture1d operator[](size_type Layer) const;

    /// Return the width of a texture instance
    extent_type extent(size_type Level = 0) const;

    /// Fetch a texel from a texture. The texture format must be uncompressed.
    template <typename gen_type>
    gen_type load(const extent_type& TexelCoord, size_type Layer, size_type Level) const;

    /// Write a texel to a texture. The texture format must be uncompressed.
    template <typename gen_type>
    void store(const extent_type& TexelCoord, size_type Layer, size_type Level, const gen_type& Texel);
  };
}  // namespace gli

#include "./texture1d_array.inl"
