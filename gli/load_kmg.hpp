/// @brief Include to load KMG textures from files or memory.
/// @file gli/load_kmg.hpp

#pragma once

#include "texture.hpp"

namespace gli {
  /// Loads a texture storage_linear from KMG (Khronos Image) file. Returns an empty storage_linear in case of failure.
  ///
  /// @param Path Path of the file to open including filaname and filename extension
  texture load_kmg(const char* Path);

  /// Loads a texture storage_linear from KMG (Khronos Image) file. Returns an empty storage_linear in case of failure.
  ///
  /// @param Path Path of the file to open including filaname and filename extension
  texture load_kmg(const std::string& Path);

  /// Loads a texture storage_linear from KMG (Khronos Image) memory. Returns an empty storage_linear in case of
  /// failure.
  ///
  /// @param Data Pointer to the beginning of the texture container data to read
  /// @param Size Size of texture container Data to read
  texture load_kmg(const char* Data, std::size_t Size);
}  // namespace gli

#include "./load_kmg.inl"
