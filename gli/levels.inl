#include <glm/gtc/integer.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>

namespace gli {
  template <length_t L, typename T, qualifier Q>
  inline T levels(const vec<L, T, Q>& Extent) {
    return glm::log2(compMax(Extent)) + static_cast<T>(1);
  }

  template <typename T>
  inline T levels(T Extent) {
    return static_cast<T>(glm::log2(Extent) + static_cast<size_t>(1));
  }
  // TODO: remove commented out code?
  /*
          inline int levels(int Extent)
          {
                  return glm::log2(Extent) + static_cast<int>(1);
          }
  */
}  // namespace gli
