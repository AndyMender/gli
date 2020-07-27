/// @brief Include to sample 1d textures.
/// @file gli/sampler1d.hpp

#pragma once

#include "core/convert_func.hpp"
#include "core/mipmaps_compute.hpp"
#include "sampler.hpp"
#include "texture1d.hpp"

namespace gli {
  /// 1d texture sampler
  /// @tparam T Sampler can fetch, write and interpret any texture format but will expose and process the data through
  /// type T conversions.
  /// @tparam P Precision in term of ULPs
  template <typename T, qualifier P = defaultp>
  class sampler1d : public sampler {
   private:
    using interpolate_type = typename detail::interpolate<T>::type;

   public:
    using texture_type = texture1d;
    using size_type = typename texture_type::size_type;
    using extent_type = typename texture_type::extent_type;
    using level_type = interpolate_type;
    using normalized_type = vec<1, interpolate_type, P>;
    using texel_type = vec<4, T, P>;

    sampler1d(const texture_type& Texture, wrap Wrap, filter Mip = FILTER_NEAREST, filter Min = FILTER_NEAREST,
              const texel_type & BorderColor = texel_type(0, 0, 0, 1));

    /// Access the sampler texture object
    const texture_type& operator()() const;

    /// Fetch a texel from the sampler texture
    texel_type texel_fetch(const extent_type& TexelCoord, const size_type& Level) const;

    /// Write a texel in the sampler texture
    void texel_write(const extent_type& TexelCoord, const size_type& Level, const texel_type& Texel);

    /// Clear the sampler texture with a uniform texel
    void clear(const texel_type& Texel);

    /// Sample the sampler texture at a specific level
    texel_type texture_lod(const normalized_type& SampleCoord, level_type Level) const;

    /// Generate all the mipmaps of the sampler texture from the texture base level
    void generate_mipmaps(filter Minification);

    /// Generate the mipmaps of the sampler texture from the texture base level to the texture max level included
    void generate_mipmaps(size_type BaseLevel, size_type MaxLevel, filter Minification);

   private:
    using convert_type = typename detail::convert<texture_type, T, P>::func;
    using fetch_type = typename detail::convert<texture_type, T, P>::fetchFunc;
    using write_type = typename detail::convert<texture_type, T, P>::writeFunc;
    using filter_type = typename detail::filterBase<detail::DIMENSION_1D, texture_type, interpolate_type,
						    normalized_type, fetch_type, texel_type>::filterFunc;

    texture_type Texture;
    convert_type Convert;
    texel_type BorderColor;
    filter_type Filter;
  };

  using fsampler1D = sampler1d<float>;
  using dsampler1D = sampler1d<double>;
  using usampler1D = sampler1d<unsigned int>;
  using isampler1D = sampler1d<int>;
}  // namespace gli

#include "./sampler1d.inl"
