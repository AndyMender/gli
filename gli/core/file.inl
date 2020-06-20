#pragma once

#include <glm/simd/platform.h>

namespace gli {
  namespace detail {
  	// TODO: use fstream instead?
    inline FILE *open_file(const char *Filename, const char *Mode) {
#if GLM_COMPILER & GLM_COMPILER_VC
      FILE *File = nullptr;
      fopen_s(&File, Filename, Mode);
      return File;
#else
      return std::fopen(Filename, Mode);
#endif
    }
  }  // namespace detail
}  // namespace gli
