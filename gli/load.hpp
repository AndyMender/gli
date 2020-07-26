/// @brief Include to load DDS, KTX or KMG textures from files or memory.
/// @file gli/load.hpp

#pragma once

#include "texture.hpp"

namespace gli {
  /// Loads a texture storage_linear from file. Returns an empty storage_linear in case of failure.
  ///
  /// @param Path Path of the file to open including filaname and filename extension
  texture load(const char* Path);

  /// Loads a texture storage_linear from file. Returns an empty storage_linear in case of failure.
  ///
  /// @param Path Path of the file to open including filaname and filename extension
  texture load(const std::string& Path);

  /// Loads a texture storage_linear from memory. Returns an empty storage_linear in case of failure.
  ///
  /// @param Data Data of a texture
  /// @param Size Size of the data
  texture load(const char* Data, std::size_t Size);
}  // namespace gli

#include "./load.inl"
