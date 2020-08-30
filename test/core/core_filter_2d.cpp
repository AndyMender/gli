#include <gli/gli.hpp>
#include <glm/ext/vector_relational.hpp>

namespace filter2d {
  int test() {
    int Error = 0;

    const gli::vec4 ColorFill(1.0f, 0.5f, 0.0f, 1.0f);
    const gli::vec4 ColorBorder(0.0f, 0.5f, 1.0f, 1.0f);

    gli::texture2d Texture(gli::FORMAT_RGBA8_UNORM_PACK8, gli::texture2d::extent_type(2, 2), 1);
    Texture.clear(glm::packUnorm<gli::u8>(ColorFill));

    {
      gli::fsampler2D Sampler(Texture, gli::WRAP_CLAMP_TO_EDGE, gli::FILTER_LINEAR, gli::FILTER_LINEAR, ColorBorder);

      const gli::vec4 TexelA = Sampler.texture_lod(gli::vec2(0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelA, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelB = Sampler.texture_lod(gli::vec2(-0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelB, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelC = Sampler.texture_lod(gli::vec2(1.5f), 0.0f);
      Error += gli::all(glm::equal(TexelC, ColorFill, 0.01f)) ? 0 : 1;
    }
    {
      gli::fsampler2D Sampler(Texture, gli::WRAP_CLAMP_TO_BORDER, gli::FILTER_LINEAR, gli::FILTER_LINEAR, ColorBorder);

      const gli::vec4 TexelA = Sampler.texture_lod(gli::vec2(0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelA, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelB = Sampler.texture_lod(gli::vec2(-1.0f, -1.0f), 0.0f);
      Error += gli::all(glm::equal(TexelB, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelC = Sampler.texture_lod(gli::vec2(+2.0f, +2.0f), 0.0f);
      Error += gli::all(glm::equal(TexelC, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelD = Sampler.texture_lod(gli::vec2(+2.0f, -1.0f), 0.0f);
      Error += gli::all(glm::equal(TexelD, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelE = Sampler.texture_lod(gli::vec2(-1.0f, +2.0f), 0.0f);
      Error += gli::all(glm::equal(TexelE, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelF = Sampler.texture_lod(gli::vec2(-0.5f, +0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelF, (ColorFill + ColorBorder) * 0.5f, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelG = Sampler.texture_lod(gli::vec2(+0.5f, +1.5f), 0.0f);
      Error += gli::all(glm::equal(TexelG, (ColorFill + ColorBorder) * 0.5f, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelH = Sampler.texture_lod(gli::vec2(+0.5f, -0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelH, (ColorFill + ColorBorder) * 0.5f, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelI = Sampler.texture_lod(gli::vec2(1.5f, 0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelI, (ColorFill + ColorBorder) * 0.5f, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelJ = Sampler.texture_lod(gli::vec2(+0.0f, +0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelJ, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelK = Sampler.texture_lod(gli::vec2(+0.5f, +1.0f), 0.0f);
      Error += gli::all(glm::equal(TexelK, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelL = Sampler.texture_lod(gli::vec2(+0.5f, -0.0f), 0.0f);
      Error += gli::all(glm::equal(TexelL, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelM = Sampler.texture_lod(gli::vec2(1.0f, 0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelM, ColorFill, 0.01f)) ? 0 : 1;
    }
    {
      gli::fsampler2D Sampler(Texture, gli::WRAP_CLAMP_TO_EDGE, gli::FILTER_NEAREST, gli::FILTER_NEAREST, ColorBorder);
      const gli::vec4 TexelA = Sampler.texture_lod(gli::vec2(0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelA, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelB = Sampler.texture_lod(gli::vec2(-0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelB, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelC = Sampler.texture_lod(gli::vec2(1.5f), 0.0f);
      Error += gli::all(glm::equal(TexelC, ColorFill, 0.01f)) ? 0 : 1;
    }
    {
      gli::fsampler2D Sampler(Texture, gli::WRAP_CLAMP_TO_BORDER, gli::FILTER_NEAREST, gli::FILTER_NEAREST,
                              ColorBorder);

      const gli::vec4 TexelA = Sampler.texture_lod(gli::vec2(0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelA, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelB = Sampler.texture_lod(gli::vec2(-0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelB, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelC = Sampler.texture_lod(gli::vec2(1.5f), 0.0f);
      Error += gli::all(glm::equal(TexelC, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelD = Sampler.texture_lod(gli::vec2(+0.5f, -0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelD, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelE = Sampler.texture_lod(gli::vec2(+0.5f, 1.5f), 0.0f);
      Error += gli::all(glm::equal(TexelE, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelF = Sampler.texture_lod(gli::vec2(-0.5f, 0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelF, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelG = Sampler.texture_lod(gli::vec2(+1.5f, 0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelG, ColorBorder, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelH = Sampler.texture_lod(gli::vec2(+0.5f, +0.0f), 0.0f);
      Error += gli::all(glm::equal(TexelH, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelI = Sampler.texture_lod(gli::vec2(+0.5f, +1.0f), 0.0f);
      Error += gli::all(glm::equal(TexelI, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelJ = Sampler.texture_lod(gli::vec2(+0.0f, +0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelJ, ColorFill, 0.01f)) ? 0 : 1;

      const gli::vec4 TexelK = Sampler.texture_lod(gli::vec2(+1.0f, +0.5f), 0.0f);
      Error += gli::all(glm::equal(TexelK, ColorFill, 0.01f)) ? 0 : 1;
    }

    return Error;
  }
}  // namespace filter2d

int main() {
  int Error = 0;

  Error += filter2d::test();

  return Error;
}
