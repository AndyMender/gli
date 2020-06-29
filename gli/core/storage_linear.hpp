#pragma once

// STD
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "../format.hpp"
#include "../type.hpp"

// GLM
#include <glm/gtc/bitfield.hpp>
#include <glm/gtc/round.hpp>
#include <glm/gtx/component_wise.hpp>
// TODO: remove redundant includes?
//#include <glm/gtx/integer.hpp>
//#include <glm/gtx/bit.hpp>
//#include <glm/gtx/wrap.hpp>

// TODO: this should be resolved by cmake!
static_assert(GLM_VERSION >= 97, "GLI requires at least GLM 0.9.7");

namespace gli {
  class storage_linear {
   public:
    typedef extent3d extent_type;
    typedef size_t size_type;
    typedef gli::format format_type;
    typedef gli::byte data_type;

   public:
    storage_linear();

    storage_linear(format_type Format, const extent_type& Extent, size_type Layers, size_type Faces, size_type Levels);

    bool empty() const;
    size_type size() const;  // in bytes
    size_type layers() const;
    size_type levels() const;
    size_type faces() const;

    size_type block_size() const;
    extent_type block_extent() const;
    extent_type block_count(size_type Level) const;
    extent_type extent(size_type Level) const;

    data_type* data();
    const data_type * const data() const;

    /// Compute the relative memory offset to access the data for a specific layer, face and level
    size_type base_offset(size_type Layer, size_type Face, size_type Level) const;

    size_type image_offset(const extent1d& Coord, const extent1d& Extent) const;

    size_type image_offset(const extent2d& Coord, const extent2d& Extent) const;

    size_type image_offset(const extent3d& Coord, const extent3d& Extent) const;

    /// Copy a subset of a specific image of a texture
    void copy(const storage_linear& StorageSrc, size_t LayerSrc, size_t FaceSrc, size_t LevelSrc,
              const extent_type& BlockIndexSrc, size_t LayerDst, size_t FaceDst, size_t LevelDst,
              const extent_type& BlockIndexDst, const extent_type& BlockCount);

    size_type level_size(size_type Level) const;
    size_type face_size(size_type BaseLevel, size_type MaxLevel) const;
    size_type layer_size(size_type BaseFace, size_type MaxFace, size_type BaseLevel, size_type MaxLevel) const;

   private:
    // TODO: should these really be 'const'?
    const size_type Layers;
    const size_type Faces;
    const size_type Levels;
    const size_type BlockSize;
    const extent_type BlockCount;
    const extent_type BlockExtent;
    const extent_type Extent;
    std::vector<data_type> Data;
  };
}  // namespace gli

#include "storage_linear.inl"
