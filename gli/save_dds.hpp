/// @brief Include to save DDS textures to files or memory.
/// @file gli/save_dds.hpp

#pragma once

#include "texture.hpp"

namespace gli {
  /// Save a texture storage_linear to a DDS file.
  ///
  /// @param Texture Source texture to save
  /// @param Path Path for where to save the file. It must include the filaname and filename extension.
  /// This function ignores the filename extension in the path and save to DDS anyway but keep the requested filename
  /// extension.
  /// @return Returns false if the function fails to save the file.
  bool save_dds(const texture& Texture, char const* Path);

  /// Save a texture storage_linear to a DDS file.
  ///
  /// @param Texture Source texture to save
  /// @param Path Path for where to save the file. It must include the filaname and filename extension.
  /// This function ignores the filename extension in the path and save to DDS anyway but keep the requested filename
  /// extension.
  /// @return Returns false if the function fails to save the file.
  bool save_dds(const texture& Texture, const std::string& Path);

  /// Save a texture storage_linear to a DDS file.
  ///
  /// @param Texture Source texture to save
  /// @param Memory Storage for the DDS container. The function resizes the containers to fit the necessary
  /// storage_linear.
  /// @return Returns false if the function fails to save the file.
  bool save_dds(const texture& Texture, std::vector<char>& Memory);
}  // namespace gli

#include "./save_dds.inl"
