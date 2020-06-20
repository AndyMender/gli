/// @brief Include to use filter enum, to select filtering methods.
/// @file gli/core/filter.hpp

#pragma once

namespace gli {
  /// Texture filtering modes
  enum filter {
    FILTER_NONE = 0,
    FILTER_NEAREST,
    FILTER_FIRST = FILTER_NEAREST,
    FILTER_LINEAR,
    FILTER_LAST = FILTER_LINEAR
  };

  enum { FILTER_COUNT = FILTER_LAST - FILTER_FIRST + 1, FILTER_INVALID = -1 };
}  // namespace gli

// TODO: should the 'gli' and 'detail' namespaces not be moved here instead?
#include "filter.inl"
