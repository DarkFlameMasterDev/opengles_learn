package com.czb.opengles3_0

import android.app.Application

class MyApplication:Application() {
  override fun onCreate() {
    super.onCreate()
    val assetManager = resources.assets
    AssetUtils.setNativeAssetManager(assetManager)
  }
}