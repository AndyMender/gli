/// @brief Include create views of textures, either to isolate a subset or to reinterpret data without memory copy.
/// @file gli/view.hpp

#pragma once

#include "image.hpp"
#include "texture.hpp"
#include "texture1d.hpp"
#include "texture1d_array.hpp"
#include "texture2d.hpp"
#include "texture2d_array.hpp"
#include "texture3d.hpp"
#include "texture_cube.hpp"
#include "texture_cube_array.hpp"

namespace gli {
  /// Create an image view of an existing image, sharing the same memory storage_linear.
  image view(const image& Image);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear.
  texture view(const texture& Texture);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of layers, levels and faces.
  texture view(const texture& Texture, texture::size_type BaseLayer, texture::size_type MaxLayer,
               texture::size_type BaseFace, texture::size_type MaxFace, texture::size_type BaseLevel,
               texture::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear.
  template <typename texType>
  texture view(const texType& Texture);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but a different format.
  /// The format must be a compatible format, a format which block size match the original format.
  template <typename texType>
  texture view(const texType& Texture, format Format);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of levels.
  texture view(const texture1d& Texture, texture1d::size_type BaseLevel, texture1d::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of levels and layers.
  texture view(const texture1d_array& Texture, texture1d_array::size_type BaseLayer,
               texture1d_array::size_type MaxLayer, texture1d_array::size_type BaseLevel,
               texture1d_array::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of levels.
  texture view(const texture2d& Texture, texture2d::size_type BaseLevel, texture2d::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of levels and layers.
  texture view(const texture2d_array& Texture, texture2d_array::size_type BaseLayer,
               texture2d_array::size_type MaxLayer, texture2d_array::size_type BaseLevel,
               texture2d_array::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of levels.
  texture view(const texture3d& Texture, texture3d::size_type BaseLevel, texture3d::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of levels and faces.
  texture view(const texture_cube& Texture, texture_cube::size_type BaseFace, texture_cube::size_type MaxFace,
               texture_cube::size_type BaseLevel, texture_cube::size_type MaxLevel);

  /// Create a texture view of an existing texture, sharing the same memory storage_linear but giving access only to a
  /// subset of layers, levels and faces.
  texture view(const texture_cube_array& Texture, texture_cube_array::size_type BaseLayer,
               texture_cube_array::size_type MaxLayer, texture_cube_array::size_type BaseFace,
               texture_cube_array::size_type MaxFace, texture_cube_array::size_type BaseLevel,
               texture_cube_array::size_type MaxLevel);
}  // namespace gli

#include "./view.inl"
