// TODO: use C++ time constructs?
#include <ctime>
#include <gli/gli.hpp>
#include <glm/gtc/color_space.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/packing.hpp>
#include <glm/gtc/vec1.hpp>

namespace {
  struct params {
    params(const std::string& Filename, gli::format Format) : Filename(Filename), Format(Format) {}

    std::string Filename;
    gli::format Format;
  };
}  // namespace

namespace gen_rect {
  int test() {
    int Error = 0;

    for (int TargetIndex = gli::TARGET_RECT, TargetCount = gli::TARGET_RECT_ARRAY; TargetIndex <= TargetCount;
         ++TargetIndex) {
      for (int FormatIndex = gli::FORMAT_FIRST, FormatCount = gli::FORMAT_LAST; FormatIndex < FormatCount;
           ++FormatIndex) {
        gli::target Target = static_cast<gli::target>(TargetIndex);
        gli::format Format = static_cast<gli::format>(FormatIndex);

        if (gli::is_compressed(Format) && (Target == gli::TARGET_3D)) continue;

        const gli::size_t Layers = gli::is_target_array(Target) ? 2 : 1;
        const gli::size_t Faces = gli::is_target_cube(Target) ? 6 : 1;
        const gli::ivec3 BlockExtent = gli::block_extent(Format);

        gli::texture Texture(Target, Format, BlockExtent * gli::ivec3(BlockExtent.y, BlockExtent.x, 1), 
							Layers, Faces, 2);
        Texture.clear();

        gli::save(Texture, "gen_rect_test.kmg");
        gli::texture TextureKMG(gli::load("gen_rect_test.kmg"));
        Error += (Texture == TextureKMG) ? 0 : 1;

        GLI_ASSERT(!Error);
      }
	}

    return Error;
  }
}  // namespace gen_rect

int main() {
  int Error = 0;

  Error += gen_rect::test();

  return Error;
}
