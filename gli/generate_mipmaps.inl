#include "sampler1d.hpp"
#include "sampler1d_array.hpp"
#include "sampler2d.hpp"
#include "sampler2d_array.hpp"
#include "sampler3d.hpp"
#include "sampler_cube.hpp"
#include "sampler_cube_array.hpp"

namespace gli {
  inline texture1d generate_mipmaps(const texture1d& Texture,
				    texture1d::size_type BaseLevel,
                                    texture1d::size_type MaxLevel,
				    filter Minification) {
    fsampler1D Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  inline texture1d_array generate_mipmaps(const texture1d_array& Texture,
					  texture1d_array::size_type BaseLayer,
                                          texture1d_array::size_type MaxLayer,
					  texture1d_array::size_type BaseLevel,
                                          texture1d_array::size_type MaxLevel,
					  filter Minification) {
    fsampler1DArray Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseLayer, MaxLayer, BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  inline texture2d generate_mipmaps(const texture2d& Texture,
				    texture2d::size_type BaseLevel,
                                    texture2d::size_type MaxLevel,
				    filter Minification) {
    fsampler2D Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  inline texture2d_array generate_mipmaps(const texture2d_array& Texture,
					  texture2d_array::size_type BaseLayer,
                                          texture2d_array::size_type MaxLayer,
					  texture2d_array::size_type BaseLevel,
                                          texture2d_array::size_type MaxLevel,
					  filter Minification) {
    fsampler2DArray Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseLayer, MaxLayer, BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  inline texture3d generate_mipmaps(const texture3d& Texture,
				    texture3d::size_type BaseLevel,
                                    texture3d::size_type MaxLevel,
				    filter Minification) {
    fsampler3D Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  inline texture_cube generate_mipmaps(const texture_cube& Texture,
				       texture_cube::size_type BaseFace,
                                       texture_cube::size_type MaxFace,
				       texture_cube::size_type BaseLevel,
                                       texture_cube::size_type MaxLevel,
				       filter Minification) {
    fsamplerCube Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseFace, MaxFace, BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  inline texture_cube_array generate_mipmaps(const texture_cube_array& Texture,
					     texture_cube_array::size_type BaseLayer,
                                             texture_cube_array::size_type MaxLayer,
                                             texture_cube_array::size_type BaseFace,
                                             texture_cube_array::size_type MaxFace,
                                             texture_cube_array::size_type BaseLevel,
                                             texture_cube_array::size_type MaxLevel,
					     filter Minification) {
    fsamplerCubeArray Sampler(Texture, WRAP_CLAMP_TO_EDGE);
    Sampler.generate_mipmaps(BaseLayer, MaxLayer, BaseFace, MaxFace, BaseLevel, MaxLevel, Minification);

    return Sampler();
  }

  template <>
  inline texture1d generate_mipmaps<texture1d>(const texture1d& Texture, filter Minification) {
    return generate_mipmaps(Texture, Texture.base_level(), Texture.max_level(), Minification);
  }

  template <>
  inline texture1d_array generate_mipmaps<texture1d_array>(const texture1d_array& Texture, filter Minification) {
    return generate_mipmaps(Texture, Texture.base_layer(), Texture.max_layer(), Texture.base_level(),
                            Texture.max_level(), Minification);
  }

  template <>
  inline texture2d generate_mipmaps<texture2d>(const texture2d& Texture, filter Minification) {
    return generate_mipmaps(Texture, Texture.base_level(), Texture.max_level(), Minification);
  }

  template <>
  inline texture2d_array generate_mipmaps<texture2d_array>(const texture2d_array& Texture, filter Minification) {
    return generate_mipmaps(Texture, Texture.base_layer(), Texture.max_layer(), Texture.base_level(),
                            Texture.max_level(), Minification);
  }

  template <>
  inline texture3d generate_mipmaps<texture3d>(const texture3d& Texture, filter Minification) {
    return generate_mipmaps(Texture, Texture.base_level(), Texture.max_level(), Minification);
  }

  template <>
  inline texture_cube generate_mipmaps<texture_cube>(const texture_cube& Texture, filter Minification) {
    return generate_mipmaps(Texture, Texture.base_face(), Texture.max_face(), Texture.base_level(), Texture.max_level(),
                            Minification);
  }

  template <>
  inline texture_cube_array generate_mipmaps<texture_cube_array>(const texture_cube_array& Texture,
                                                                 filter Minification) {
    return generate_mipmaps(Texture, Texture.base_layer(), Texture.max_layer(), Texture.base_face(), Texture.max_face(),
                            Texture.base_level(), Texture.max_level(), Minification);
  }
}  // namespace gli
