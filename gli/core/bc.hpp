/// @brief Include to compress and decompress the BC/DXT compression scheme
/// @file gli/bc.hpp

#pragma once

#include "s3tc.hpp"

namespace gli {
  namespace detail {
    // BC1, 2, 3 formats are equivalent to DXT1, 3, 5 formats
    typedef dxt1_block bc1_block;
    typedef dxt3_block bc2_block;
    typedef dxt5_block bc3_block;

    struct bc4_block {
      uint8_t Red0;       // start color in greyscale
      uint8_t Red1;       // end color in greyscale
      uint8_t Bitmap[6];  // indices along vector in greyscale space
    };

    struct bc5_block {
      // bc4 block #1
      uint8_t Red0;
      uint8_t Red1;
      uint8_t RedBitmap[6];
      // bc4 block #2
      uint8_t Green0;
      uint8_t Green1;
      uint8_t GreenBitmap[6];
    };

    glm::vec4 decompress_bc1(const bc1_block& Block, const extent2d& BlockTexelCoord);
    texel_block4x4 decompress_dxt1_block(const dxt1_block& Block);

    glm::vec4 decompress_bc2(const bc2_block& Block, const extent2d& BlockTexelCoord);
    texel_block4x4 decompress_dxt3_block(const bc2_block& Block);

    glm::vec4 decompress_bc3(const bc3_block& Block, const extent2d& BlockTexelCoord);
    texel_block4x4 decompress_bc3_block(const dxt5_block& Block);

    glm::vec4 decompress_bc4unorm(const bc4_block& Block, const extent2d& BlockTexelCoord);
    glm::vec4 decompress_bc4snorm(const bc4_block& Block, const extent2d& BlockTexelCoord);
    texel_block4x4 decompress_bc4unorm_block(const bc4_block& Block);
    texel_block4x4 decompress_bc4snorm_block(const bc4_block& Block);

    glm::vec4 decompress_bc5unorm(const bc5_block& Block, const extent2d& BlockTexelCoord);
    glm::vec4 decompress_bc5snorm(const bc5_block& Block, const extent2d& BlockTexelCoord);
    texel_block4x4 decompress_bc5unorm_block(const bc5_block& Block);
    texel_block4x4 decompress_bc5snorm_block(const bc5_block& Block);

    // TODO: implement BC6 and BC7 compression?
  }  // namespace detail
}  // namespace gli

#include "bc.inl"
