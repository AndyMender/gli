/// @brief Include to perform arithmetic per texel between two textures.
/// @file gli/transform.hpp

#pragma once

#include "texture1d.hpp"
#include "texture1d_array.hpp"
#include "texture2d.hpp"
#include "texture2d_array.hpp"
#include "texture3d.hpp"
#include "texture_cube.hpp"
#include "texture_cube_array.hpp"

namespace gli {
  template <typename vec_type>
  struct transform_func {
    typedef vec_type (*type)(const vec_type& A, const vec_type& B);
  };

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture1d& Out, const texture1d& In0, const texture1d& In1,
                 typename transform_func<vec_type>::type TexelFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture1d_array& Out, const texture1d_array& In0, const texture1d_array& In1,
                 typename transform_func<vec_type>::type TexelFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture2d& Out, const texture2d& In0, const texture2d& In1,
                 typename transform_func<vec_type>::type TexelFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture2d_array& Out, const texture2d_array& In0, const texture2d_array& In1,
                 typename transform_func<vec_type>::type TexelFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture3d& Out, const texture3d& In0, const texture3d& In1,
                 typename transform_func<vec_type>::type TexelFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture_cube& Out, const texture_cube& In0, const texture_cube& In1,
                 typename transform_func<vec_type>::type TexelFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param Out Output texture.
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function.
  template <typename vec_type>
  void transform(texture_cube_array& Out, const texture_cube_array& In0, const texture_cube_array& In1,
                 typename transform_func<vec_type>::type TexelFunc);

}  // namespace gli

#include "./transform.inl"
