/// @brief Include to load DDS textures from files or memory.
/// @file gli/load_dds.hpp

#pragma once

#include "texture.hpp"

namespace gli {
  /// Loads a texture storage_linear from DDS file. Returns an empty storage_linear in case of failure.
  ///
  /// @param Path Path of the file to open including filaname and filename extension
  texture load_dds(const char* Path);

  /// Loads a texture storage_linear from DDS file. Returns an empty storage_linear in case of failure.
  ///
  /// @param Path Path of the file to open including filaname and filename extension
  texture load_dds(const std::string& Path);

  /// Loads a texture storage_linear from DDS memory. Returns an empty storage_linear in case of failure.
  ///
  /// @param Data Pointer to the beginning of the texture container data to read
  /// @param Size Size of texture container Data to read
  texture load_dds(const char* Data, std::size_t Size);
}  // namespace gli

#include "./load_dds.inl"
