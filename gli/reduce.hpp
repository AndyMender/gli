/// @brief Include to perform reduction operations.
/// @file gli/reduce.hpp

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
  struct reduce_func {
    typedef vec_type (*type)(const vec_type& A, const vec_type& B);
  };

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture1d& In0, const texture1d& In1,
		  typename reduce_func<vec_type>::type TexelFunc,
		  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture1d_array& In0, const texture1d_array& In1,
                  typename reduce_func<vec_type>::type TexelFunc,
		  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture2d& In0, const texture2d& In1,
		  typename reduce_func<vec_type>::type TexelFunc,
                  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture2d_array& In0, const texture2d_array& In1,
                  typename reduce_func<vec_type>::type TexelFunc,
		  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture3d& In0, const texture3d& In1,
		  typename reduce_func<vec_type>::type TexelFunc,
                  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture_cube& In0, const texture_cube& In1, typename reduce_func<vec_type>::type TexelFunc,
                  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename vec_type>
  vec_type reduce(const texture_cube_array& In0, const texture_cube_array& In1,
                  typename reduce_func<vec_type>::type TexelFunc,
		  typename reduce_func<vec_type>::type ReduceFunc);

  /// Compute per-texel operations using a user defined function.
  ///
  /// @param In0 First input texture.
  /// @param In1 Second input texture.
  /// @param TexelFunc Pointer to a binary function for per texel operation.
  /// @param ReduceFunc Pointer to a binary function to reduce texels.
  template <typename texture_type, typename vec_type>
  vec_type reduce(const texture_type& In0, const texture_type& In1,
		  typename reduce_func<vec_type>::type TexelFunc,
                  typename reduce_func<vec_type>::type ReduceFunc);
}  // namespace gli

#include "./reduce.inl"
