package com.czb.opengles3_0

import android.content.res.AssetManager

class AssetUtils {

  companion object {
    init {
      System.loadLibrary("cpp_libs")
    }

    external fun setNativeAssetManager(assetManager: AssetManager)
  }

}