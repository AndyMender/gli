#pragma once

#include <glm/gtc/integer.hpp>

#include "coord.hpp"
#include "filter.hpp"

namespace gli {
  namespace detail {
    enum dimension { DIMENSION_1D, DIMENSION_2D, DIMENSION_3D };

    template <typename T>
    struct interpolate {
      typedef float type;
    };

    template <>
    struct interpolate<double> {
      typedef double type;
    };

    template <>
    struct interpolate<long double> {
      typedef long double type;
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type>
    struct filterBase {
      using size_type = typename texture_type::size_type;
      using extent_type = typename texture_type::extent_type;

      typedef texel_type (*filterFunc)(const texture_type& Texture, fetch_type Fetch,
                                       const normalized_type& SampleCoordWrap, size_type Layer, size_type Face,
                                       interpolate_type Level, const texel_type& BorderColor);
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type, bool is_float = true, bool support_border = true>
    struct nearest
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_nearest<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const extent_type TexelDim(Texture.extent(Level));
        const normalized_type TexelLast(normalized_type(TexelDim) - normalized_type(1));

        // extent_type const TexelCoord(SampleCoordWrap * TexelLast + interpolate_type(0.5));
        const extent_type TexelCoord = extent_type(round(SampleCoordWrap * TexelLast));
        const typename extent_type::bool_type UseTexelCoord = in_interval(TexelCoord, extent_type(0), TexelDim - 1);

        texel_type Texel(BorderColor);
        if (all(UseTexelCoord)) Texel = Fetch(Texture, TexelCoord, Layer, Face, Level);

        return Texel;
      }
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type>
    struct nearest<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, false>
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_nearest<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const normalized_type TexelLast(normalized_type(Texture.extent(Level)) - normalized_type(1));
        const extent_type TexelCoord(SampleCoordWrap * TexelLast + interpolate_type(0.5));
        // TODO: remove obsolete code?
        // extent_type const TexelCoord = extent_type(round(SampleCoordWrap * TexelLast));

        return Fetch(Texture, TexelCoord, Layer, Face, Level);
      }
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type, bool is_float = true, bool support_border = true>
    struct linear
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        return static_cast<texel_type>(0);
      }
    };

    template <typename texture_type, typename interpolate_type, typename normalized_type, typename fetch_type,
              typename texel_type>
    struct linear<DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, true>
        : public filterBase<DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const coord_type& Coord = make_coord_linear_border(Texture.extent(Level), SampleCoordWrap);

        texel_type Texel0(BorderColor);
        if (Coord.UseTexelFloor.s) Texel0 = Fetch(Texture, extent_type(Coord.TexelFloor.s), Layer, Face, Level);

        texel_type Texel1(BorderColor);
        if (Coord.UseTexelCeil.s) Texel1 = Fetch(Texture, extent_type(Coord.TexelCeil.s), Layer, Face, Level);

        return mix(Texel0, Texel1, Coord.Blend.s);
      }
    };

    template <typename texture_type, typename interpolate_type, typename normalized_type, typename fetch_type,
              typename texel_type>
    struct linear<DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, false>
        : public filterBase<DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const coord_type& Coord = make_coord_linear(Texture.extent(Level), SampleCoordWrap);

        const texel_type Texel0 = Fetch(Texture, extent_type(Coord.TexelFloor.s), Layer, Face, Level);
        const texel_type Texel1 = Fetch(Texture, extent_type(Coord.TexelCeil.s), Layer, Face, Level);

        return mix(Texel0, Texel1, Coord.Blend.s);
      }
    };

    template <typename texture_type, typename interpolate_type, typename normalized_type, typename fetch_type,
              typename texel_type>
    struct linear<DIMENSION_2D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, true>
        : public filterBase<DIMENSION_2D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<DIMENSION_2D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const coord_type& Coord = make_coord_linear_border(Texture.extent(Level), SampleCoordWrap);

        texel_type Texel00(BorderColor);
        if (Coord.UseTexelFloor.s && Coord.UseTexelFloor.t)
          Texel00 = Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelFloor.t), Layer, Face, Level);

        texel_type Texel10(BorderColor);
        if (Coord.UseTexelCeil.s && Coord.UseTexelFloor.t)
          Texel10 = Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelFloor.t), Layer, Face, Level);

        texel_type Texel11(BorderColor);
        if (Coord.UseTexelCeil.s && Coord.UseTexelCeil.t)
          Texel11 = Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelCeil.t), Layer, Face, Level);

        texel_type Texel01(BorderColor);
        if (Coord.UseTexelFloor.s && Coord.UseTexelCeil.t)
          Texel01 = Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelCeil.t), Layer, Face, Level);

        const texel_type ValueA(mix(Texel00, Texel10, Coord.Blend.s));
        const texel_type ValueB(mix(Texel01, Texel11, Coord.Blend.s));

        return mix(ValueA, ValueB, Coord.Blend.t);
      }
    };

    template <typename texture_type, typename interpolate_type, typename normalized_type, typename fetch_type,
              typename texel_type>
    struct linear<DIMENSION_2D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, false>
        : public filterBase<DIMENSION_2D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<DIMENSION_2D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const coord_type& Coord = make_coord_linear(Texture.extent(Level), SampleCoordWrap);

        const texel_type& Texel00 =
            Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelFloor.t), Layer, Face, Level);
        const texel_type& Texel10 =
            Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelFloor.t), Layer, Face, Level);
        const texel_type& Texel11 =
            Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelCeil.t), Layer, Face, Level);
        const texel_type& Texel01 =
            Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelCeil.t), Layer, Face, Level);

        const texel_type ValueA(mix(Texel00, Texel10, Coord.Blend.s));
        const texel_type ValueB(mix(Texel01, Texel11, Coord.Blend.s));

        return mix(ValueA, ValueB, Coord.Blend.t);
      }
    };

    template <typename texture_type, typename interpolate_type, typename normalized_type, typename fetch_type,
              typename texel_type>
    struct linear<DIMENSION_3D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, true>
        : public filterBase<DIMENSION_3D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<DIMENSION_3D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const coord_type& Coord = make_coord_linear_border(Texture.extent(Level), SampleCoordWrap);

        // TODO: instantiate elements in a loop to reduce code duplication?
        texel_type Texel000(BorderColor);
        if (Coord.UseTexelFloor.s && Coord.UseTexelFloor.t && Coord.UseTexelFloor.p)
          Texel000 = Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelFloor.t, Coord.TexelFloor.p), Layer,
                           Face, Level);

        texel_type Texel100(BorderColor);
        if (Coord.UseTexelCeil.s && Coord.UseTexelFloor.t && Coord.UseTexelFloor.p)
          Texel100 = Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelFloor.t, Coord.TexelFloor.p), Layer, Face,
                           Level);

        texel_type Texel110(BorderColor);
        if (Coord.UseTexelCeil.s && Coord.UseTexelCeil.t && Coord.UseTexelFloor.p)
          Texel110 =
              Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelCeil.t, Coord.TexelFloor.p), Layer, Face, Level);

        texel_type Texel010(BorderColor);
        if (Coord.UseTexelFloor.s && Coord.UseTexelCeil.t && Coord.UseTexelFloor.p)
          Texel010 = Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelCeil.t, Coord.TexelFloor.p), Layer, Face,
                           Level);

        texel_type Texel001(BorderColor);
        if (Coord.UseTexelFloor.s && Coord.UseTexelFloor.t && Coord.UseTexelCeil.p)
          Texel001 = Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelFloor.t, Coord.TexelCeil.p), Layer, Face,
                           Level);

        texel_type Texel101(BorderColor);
        if (Coord.UseTexelCeil.s && Coord.UseTexelFloor.t && Coord.UseTexelCeil.p)
          Texel101 =
              Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelFloor.t, Coord.TexelCeil.p), Layer, Face, Level);

        texel_type Texel111(BorderColor);
        if (Coord.UseTexelCeil.s && Coord.UseTexelCeil.t && Coord.UseTexelCeil.p)
          Texel111 =
              Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelCeil.t, Coord.TexelCeil.p), Layer, Face, Level);

        texel_type Texel011(BorderColor);
        if (Coord.UseTexelFloor.s && Coord.UseTexelCeil.t && Coord.UseTexelCeil.p)
          Texel011 =
              Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelCeil.t, Coord.TexelCeil.p), Layer, Face, Level);

        const texel_type ValueA(mix(Texel000, Texel100, Coord.Blend.s));
        const texel_type ValueB(mix(Texel010, Texel110, Coord.Blend.s));

        const texel_type ValueC(mix(Texel001, Texel101, Coord.Blend.s));
        const texel_type ValueD(mix(Texel011, Texel111, Coord.Blend.s));

        const texel_type ValueE(mix(ValueA, ValueB, Coord.Blend.t));
        const texel_type ValueF(mix(ValueC, ValueD, Coord.Blend.t));

        return mix(ValueE, ValueF, Coord.Blend.p);
      }
    };

    template <typename texture_type, typename interpolate_type, typename normalized_type, typename fetch_type,
              typename texel_type>
    struct linear<DIMENSION_3D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, true, false>
        : public filterBase<DIMENSION_3D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<DIMENSION_3D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, size_type Level, const texel_type& BorderColor) {
        const coord_type& Coord = make_coord_linear(Texture.extent(Level), SampleCoordWrap);

        const texel_type& Texel000 =
            Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelFloor.t, Coord.TexelFloor.p), Layer, Face, Level);
        const texel_type& Texel100 =
            Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelFloor.t, Coord.TexelFloor.p), Layer, Face, Level);
        const texel_type& Texel110 =
            Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelCeil.t, Coord.TexelFloor.p), Layer, Face, Level);
        const texel_type& Texel010 =
            Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelCeil.t, Coord.TexelFloor.p), Layer, Face, Level);
        const texel_type& Texel001 =
            Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelFloor.t, Coord.TexelCeil.p), Layer, Face, Level);
        const texel_type& Texel101 =
            Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelFloor.t, Coord.TexelCeil.p), Layer, Face, Level);
        const texel_type& Texel111 =
            Fetch(Texture, extent_type(Coord.TexelCeil.s, Coord.TexelCeil.t, Coord.TexelCeil.p), Layer, Face, Level);
        const texel_type& Texel011 =
            Fetch(Texture, extent_type(Coord.TexelFloor.s, Coord.TexelCeil.t, Coord.TexelCeil.p), Layer, Face, Level);

        const texel_type ValueA(mix(Texel000, Texel100, Coord.Blend.s));
        const texel_type ValueB(mix(Texel010, Texel110, Coord.Blend.s));

        const texel_type ValueC(mix(Texel001, Texel101, Coord.Blend.s));
        const texel_type ValueD(mix(Texel011, Texel111, Coord.Blend.s));

        const texel_type ValueE(mix(ValueA, ValueB, Coord.Blend.t));
        const texel_type ValueF(mix(ValueC, ValueD, Coord.Blend.t));

        return mix(ValueE, ValueF, Coord.Blend.p);
      }
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type, bool is_float, bool support_border>
    struct nearest_mipmap_nearest
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, interpolate_type Level, const texel_type& BorderColor) {
        return nearest<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, is_float,
                       support_border>::call(Texture, Fetch, SampleCoordWrap, Layer, Face, glm::iround(Level),
                                             BorderColor);
      }
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type, bool is_float, bool support_border>
    struct nearest_mipmap_linear
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, interpolate_type Level, const texel_type& BorderColor) {
        const texel_type MinTexel =
            nearest<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, is_float,
                    support_border>::call(Texture, Fetch, SampleCoordWrap, Layer, Face,
                                          static_cast<size_type>(floor(Level)), BorderColor);
        const texel_type MaxTexel =
            nearest<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, is_float,
                    support_border>::call(Texture, Fetch, SampleCoordWrap, Layer, Face,
                                          static_cast<size_type>(ceil(Level)), BorderColor);
        return mix(MinTexel, MaxTexel, fract(Level));
      }
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type, bool is_float, bool support_border>
    struct linear_mipmap_nearest
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, interpolate_type Level, const texel_type& BorderColor) {
        return linear<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, is_float,
                      support_border>::call(Texture, Fetch, SampleCoordWrap, Layer, Face, glm::iround(Level),
                                            BorderColor);
      }
    };

    template <dimension Dimension, typename texture_type, typename interpolate_type, typename normalized_type,
              typename fetch_type, typename texel_type, bool is_float, bool support_border>
    struct linear_mipmap_linear
        : public filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type> {
      using base_type = filterBase<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>;
      using size_type = typename base_type::size_type;
      using extent_type = typename base_type::extent_type;
      using coord_type = coord_linear_border<extent_type, normalized_type>;

      static texel_type call(const texture_type& Texture, fetch_type Fetch, const normalized_type& SampleCoordWrap,
                             size_type Layer, size_type Face, interpolate_type Level, const texel_type& BorderColor) {
        const size_type FloorLevel = static_cast<size_type>(floor(Level));
        const size_type CeilLevel = static_cast<size_type>(ceil(Level));
        const texel_type MinTexel =
            linear<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, is_float,
                   support_border>::call(Texture, Fetch, SampleCoordWrap, Layer, Face, FloorLevel, BorderColor);
        const texel_type MaxTexel =
            linear<Dimension, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, is_float,
                   support_border>::call(Texture, Fetch, SampleCoordWrap, Layer, Face, CeilLevel, BorderColor);

        return mix(MinTexel, MaxTexel, fract(Level));
      }
    };

    template <typename filter_type, dimension Dimensions, typename texture_type, typename interpolate_type,
              typename normalized_type, typename fetch_type, typename texel_type, typename T>
    inline filter_type get_filter(filter Mip, filter Min, bool Border) {
      // TODO: use a vector instead?
      static filter_type Table[][FILTER_COUNT][2] = {
          {{nearest_mipmap_nearest<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                   std::numeric_limits<T>::is_iec559, false>::call,
            nearest_mipmap_nearest<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                   std::numeric_limits<T>::is_iec559, true>::call},
           {linear_mipmap_nearest<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                  std::numeric_limits<T>::is_iec559, false>::call,
            linear_mipmap_nearest<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                  std::numeric_limits<T>::is_iec559, true>::call}},
          {{nearest_mipmap_linear<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                  std::numeric_limits<T>::is_iec559, false>::call,
            nearest_mipmap_linear<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                  std::numeric_limits<T>::is_iec559, true>::call},
           {linear_mipmap_linear<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                 std::numeric_limits<T>::is_iec559, false>::call,
            linear_mipmap_linear<Dimensions, texture_type, interpolate_type, normalized_type, fetch_type, texel_type,
                                 std::numeric_limits<T>::is_iec559, true>::call}}};
      static_assert(sizeof(Table) / sizeof(Table[0]) == FILTER_COUNT,
                    "GLI ERROR: 'Table' doesn't match the number of supported filters");

      GLI_ASSERT(Table[Mip - FILTER_FIRST][Min - FILTER_FIRST][Border ? 1 : 0]);

      return Table[Mip - FILTER_FIRST][Min - FILTER_FIRST][Border ? 1 : 0];
    }
  }  // namespace detail
}  // namespace gli
