namespace gli {
  template <typename texture_type>
  inline void clear(texture_type& Texture) {
    Texture.clear();
  }

  template <typename texture_type, typename gen_type>
  inline void clear(texture_type& Texture, const gen_type& BlockData) {
    Texture.clear(BlockData);
  }

  template <typename texture_type, typename gen_type>
  inline void clear(texture_type& Texture, size_t Layer, size_t Face, size_t Level, const gen_type& BlockData) {
    Texture.clear(Layer, Face, Level, BlockData);
  }

  template <typename texture_type, typename gen_type>
  inline void clear_level(texture_type& Texture, size_t BaseLevel, size_t LevelCount, const gen_type& BlockData) {
    for (size_t LayerIndex = 0, LayerCount = Texture.layers(); LayerIndex < LayerCount; ++LayerIndex)
      for (size_t FaceIndex = 0, FaceCount = Texture.faces(); FaceIndex < FaceCount; ++FaceIndex)
        for (size_t LevelIndex = 0; LevelIndex < LevelCount; ++LevelIndex) {
          Texture.template clear<gen_type>(LayerIndex, FaceIndex, BaseLevel + LevelIndex, BlockData);
        }
  }

  template <typename texture_type, typename gen_type>
  inline void clear_level(texture_type& Texture, size_t BaseLevel, const gen_type& BlockData) {
    clear_level(Texture, BaseLevel, 1, BlockData);
  }

  template <typename texture_type, typename gen_type>
  inline void clear_face(texture_type& Texture, size_t BaseFace, size_t FaceCount, const gen_type& BlockData) {
    for (size_t LayerIndex = 0, LayerCount = Texture.layers(); LayerIndex < LayerCount; ++LayerIndex)
      for (size_t FaceIndex = 0; FaceIndex < FaceCount; ++FaceIndex)
        for (size_t LevelIndex = 0, LevelCount = Texture.levels(); LevelIndex < LevelCount; ++LevelIndex) {
          Texture.template clear<gen_type>(LayerIndex, BaseFace + FaceIndex, LevelIndex, BlockData);
        }
  }

  template <typename texture_type, typename gen_type>
  inline void clear_face(texture_type& Texture, size_t BaseFace, const gen_type& BlockData) {
    clear_face(Texture, BaseFace, 1, BlockData);
  }

  template <typename texture_type, typename gen_type>
  inline void clear_layer(texture_type& Texture, size_t BaseLayer, size_t LayerCount, const gen_type& BlockData) {
    for (size_t LayerIndex = 0; LayerIndex < LayerCount; ++LayerIndex)
      for (size_t FaceIndex = 0, FaceCount = Texture.faces(); FaceIndex < FaceCount; ++FaceIndex)
        for (size_t LevelIndex = 0, LevelCount = Texture.levels(); LevelIndex < LevelCount; ++LevelIndex) {
          Texture.template clear<gen_type>(LayerIndex + BaseLayer, FaceIndex, LevelIndex, BlockData);
        }
  }

  template <typename texture_type, typename gen_type>
  inline void clear_layer(texture_type& Texture, size_t BaseLayer, const gen_type& BlockData) {
    clear_layer(Texture, BaseLayer, 1, BlockData);
  }
}  // namespace gli