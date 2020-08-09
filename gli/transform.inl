namespace gli {
  namespace detail {
    template <typename vec_type>
    struct compute_transform_1d {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture1d::size_type;
      using extent_type = texture1d::extent_type;

      static void call(texture1d& Output, const texture1d& A, const texture1d& B, func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
          const extent_type TexelCount(A.extent(LevelIndex));
          extent_type TexelIndex(0);

          for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
            Output.store<vec_type>(
                TexelIndex, LevelIndex,
                Func(A.load<vec_type>(TexelIndex, LevelIndex), B.load<vec_type>(TexelIndex, LevelIndex)));
          }
        }
      }
    };

    template <typename vec_type>
    struct compute_transform_1d_array {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture1d_array::size_type;
      using extent_type = texture1d_array::extent_type;

      static void call(texture1d_array& Output, const texture1d_array& A, const texture1d_array& B, func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.layers() == B.layers());
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type LayerIndex = 0, LayerCount = A.layers(); LayerIndex < LayerCount; ++LayerIndex)
          for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
            const extent_type TexelCount(A.extent(LevelIndex));
            extent_type TexelIndex(0);

            for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
              Output.store<vec_type>(TexelIndex, LayerIndex, LevelIndex,
                                     Func(A.load<vec_type>(TexelIndex, LayerIndex, LevelIndex),
                                          B.load<vec_type>(TexelIndex, LayerIndex, LevelIndex)));
            }
          }
      }
    };

    template <typename vec_type>
    struct compute_transform_2d {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture2d::size_type;
      using extent_type = texture2d::extent_type;

      static void call(texture2d& Output, const texture2d& A, const texture2d& B, func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
          const extent_type TexelCount(A.extent(LevelIndex));
          extent_type TexelIndex(0);

          for (TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
            for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
              Output.store<vec_type>(
                  TexelIndex, LevelIndex,
                  Func(A.load<vec_type>(TexelIndex, LevelIndex), B.load<vec_type>(TexelIndex, LevelIndex)));
            }
        }
      }
    };

    template <typename vec_type>
    struct compute_transform_2d_array {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture2d_array::size_type;
      using extent_type = texture2d_array::extent_type;

      static void call(texture2d_array& Output, const texture2d_array& A, const texture2d_array& B, func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.layers() == B.layers());
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type LayerIndex = 0, LayerCount = A.layers(); LayerIndex < LayerCount; ++LayerIndex)
          for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
            const extent_type TexelCount(A.extent(LevelIndex));
            extent_type TexelIndex(0);

            for (TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
              for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                Output.store<vec_type>(TexelIndex, LayerIndex, LevelIndex,
                                       Func(A.load<vec_type>(TexelIndex, LayerIndex, LevelIndex),
                                            B.load<vec_type>(TexelIndex, LayerIndex, LevelIndex)));
              }
          }
      }
    };

    template <typename vec_type>
    struct compute_transform_3d {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture3d::size_type;
      using extent_type = texture3d::extent_type;

      static void call(texture3d& Output, const texture3d& A, const texture3d& B, func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
          const extent_type TexelCount(A.extent(LevelIndex));
          extent_type TexelIndex(0);

          for (TexelIndex.z = 0; TexelIndex.z < TexelCount.z; ++TexelIndex.z)
            for (TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
              for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                Output.store<vec_type>(
                    TexelIndex, LevelIndex,
                    Func(A.load<vec_type>(TexelIndex, LevelIndex), B.load<vec_type>(TexelIndex, LevelIndex)));
              }
        }
      }
    };

    template <typename vec_type>
    struct compute_transform_cube {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture_cube::size_type;
      using extent_type = texture_cube::extent_type;

      static void call(texture_cube& Output, const texture_cube& A, const texture_cube& B, func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.faces() == B.faces());
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type FaceIndex = 0, FaceCount = A.faces(); FaceIndex < FaceCount; ++FaceIndex)
          for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
            const extent_type TexelCount(A.extent(LevelIndex));
            extent_type TexelIndex(0);

            for (TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
              for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                Output.store<vec_type>(TexelIndex, FaceIndex, LevelIndex,
                                       Func(A.load<vec_type>(TexelIndex, FaceIndex, LevelIndex),
                                            B.load<vec_type>(TexelIndex, FaceIndex, LevelIndex)));
              }
          }
      }
    };

    template <typename vec_type>
    struct compute_transform_cube_array {
      using func_type = typename transform_func<vec_type>::type;
      using size_type = texture_cube_array::size_type;
      using extent_type = texture_cube_array::extent_type;

      static void call(texture_cube_array& Output, const texture_cube_array& A, const texture_cube_array& B,
                       func_type Func) {
        GLI_ASSERT(all(equal(A.extent(), B.extent())));
        GLI_ASSERT(A.layers() == B.layers());
        GLI_ASSERT(A.levels() == B.levels());
        GLI_ASSERT(A.size() == B.size());

        for (size_type LayerIndex = 0, LayerCount = A.layers(); LayerIndex < LayerCount; ++LayerIndex)
          for (size_type FaceIndex = 0, FaceCount = A.faces(); FaceIndex < FaceCount; ++FaceIndex)
            for (size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
              const extent_type TexelCount(A.extent(LevelIndex));
              extent_type TexelIndex(0);

              for (TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
                for (TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                  Output.store<vec_type>(TexelIndex, LayerIndex, FaceIndex, LevelIndex,
                                         Func(A.load<vec_type>(TexelIndex, LayerIndex, FaceIndex, LevelIndex),
                                              B.load<vec_type>(TexelIndex, LayerIndex, FaceIndex, LevelIndex)));
                }
            }
      }
    };
  }  // namespace detail

  template <typename vec_type>
  inline void transform(texture1d& Out, const texture1d& In0, const texture1d& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_1d<vec_type>::call(Out, In0, In1, Func);
  }

  template <typename vec_type>
  inline void transform(texture1d_array& Out, const texture1d_array& In0, const texture1d_array& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_1d_array<vec_type>::call(Out, In0, In1, Func);
  }

  template <typename vec_type>
  inline void transform(texture2d& Out, const texture2d& In0, const texture2d& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_2d<vec_type>::call(Out, In0, In1, Func);
  }

  template <typename vec_type>
  inline void transform(texture2d_array& Out, const texture2d_array& In0, const texture2d_array& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_2d_array<vec_type>::call(Out, In0, In1, Func);
  }

  template <typename vec_type>
  inline void transform(texture3d& Out, const texture3d& In0, const texture3d& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_3d<vec_type>::call(Out, In0, In1, Func);
  }

  template <typename vec_type>
  inline void transform(texture_cube& Out, const texture_cube& In0, const texture_cube& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_cube<vec_type>::call(Out, In0, In1, Func);
  }

  template <typename vec_type>
  inline void transform(texture_cube_array& Out, const texture_cube_array& In0, const texture_cube_array& In1,
                        typename transform_func<vec_type>::type Func) {
    detail::compute_transform_cube_array<vec_type>::call(Out, In0, In1, Func);
  }
}  // namespace gli
