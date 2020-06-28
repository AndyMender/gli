#pragma once

#include <array>

#include "../texture2d.hpp"
#include "../texture2d_array.hpp"
#include "../texture_cube.hpp"
#include "../texture_cube_array.hpp"

namespace gli {
  template <typename texture_type>
  texture_type flip(const texture_type& Texture);

}  // namespace gli

#include "flip.inl"
