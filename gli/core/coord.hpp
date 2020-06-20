#pragma once

// TODO: improve include path resolution via cmake?
#include "../type.hpp"

namespace gli {
  namespace detail {
    template <typename extent_type, typename normalized_type>
    struct coord_nearest {
      extent_type Texel;
      typename extent_type::bool_type UseTexel;
    };

    template <typename extent_type, typename normalized_type>
    struct coord_linear {
      extent_type TexelFloor;
      extent_type TexelCeil;
      normalized_type Blend;
    };

    template <typename extent_type, typename normalized_type>
    struct coord_linear_border : public coord_linear<extent_type, normalized_type> {
      typename extent_type::bool_type UseTexelFloor;
      typename extent_type::bool_type UseTexelCeil;
    };

    /**
     * Create a binary mask of elements from 'Value' between corresponding elements from 'Min' and 'Max'
     */
    template <length_t L, typename T, qualifier Q>
    inline vec<L, bool, Q> in_interval(const vec<L, T, Q>& Value, const vec<L, T, Q>& Min, const vec<L, T, Q>& Max) {
      return greaterThanEqual(Value, Min) && lessThanEqual(Value, Max);
    }

    /**
     * Get the nearest coordinates from sample coordinates
     */
    template <typename extent_type, typename normalized_type>
    inline coord_nearest<extent_type, normalized_type> make_coord_nearest(const extent_type& TexelExtent,
                                                                          const normalized_type& SampleCoord) {
      const normalized_type TexelLast(static_cast<normalized_type>(TexelExtent) - static_cast<normalized_type>(1));

      coord_nearest<extent_type, normalized_type> Coord;
      Coord.Texel = static_cast<extent_type>(round(SampleCoord * TexelLast));
      Coord.UseTexel = in_interval(Coord.Texel, static_cast<extent_type>(0), TexelExtent - 1);

      return Coord;
    }

    /**
     * TODO: add docstring
     */
    template <typename extent_type, typename normalized_type>
    GLI_FORCE_INLINE coord_linear<extent_type, normalized_type> make_coord_linear(const extent_type& TexelExtent,
                                                                                  const normalized_type& SampleCoord) {
      coord_linear<extent_type, normalized_type> Coord;

      const normalized_type TexelExtentF(TexelExtent);
      const normalized_type TexelLast = TexelExtentF - static_cast<normalized_type>(1);
      const normalized_type ScaledCoord(SampleCoord * TexelLast);
      const normalized_type ScaledCoordFloor = static_cast<normalized_type>(extent_type(ScaledCoord));
      const normalized_type ScaledCoordCeil =
          static_cast<normalized_type>(extent_type(ScaledCoord + normalized_type(0.5)));

      // TODO: remove obsolete code?
      // normalized_type const ScaledCoordFloor(floor(ScaledCoord));
      // normalized_type const ScaledCoordCeil(ceil(ScaledCoord));

      Coord.Blend = ScaledCoord - ScaledCoordFloor;
      Coord.TexelFloor = extent_type(ScaledCoordFloor);
      Coord.TexelCeil = extent_type(ScaledCoordCeil);

      return Coord;
    }

    /**
     * TODO: add docstring
     */
    template <typename extent_type, typename normalized_type>
    GLI_FORCE_INLINE coord_linear_border<extent_type, normalized_type> make_coord_linear_border(
        const extent_type& TexelExtent, const normalized_type& SampleCoord) {
      coord_linear_border<extent_type, normalized_type> Coord;

      const normalized_type TexelExtentF(TexelExtent);
      const normalized_type TexelLast = TexelExtentF - normalized_type(1);
      const normalized_type ScaledCoord(SampleCoord * TexelLast);
      const normalized_type ScaledCoordFloor(floor(ScaledCoord));
      const normalized_type ScaledCoordCeil(ceil(ScaledCoord));

      Coord.Blend = ScaledCoord - ScaledCoordFloor;
      Coord.TexelFloor = static_cast<extent_type>(ScaledCoordFloor);
      Coord.TexelCeil = static_cast<extent_type>(ScaledCoordCeil);
      Coord.UseTexelFloor = in_interval(Coord.TexelFloor, static_cast<extent_type>(0), TexelExtent - 1);
      Coord.UseTexelCeil = in_interval(Coord.TexelCeil, static_cast<extent_type>(0), TexelExtent - 1);

      return Coord;
    }
  }  // namespace detail
}  // namespace gli
