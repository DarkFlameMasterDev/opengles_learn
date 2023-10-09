package com.czb.opengles3_0

class MyNativeRenderer {
  companion object {
    init {
      System.loadLibrary("cpp_libs")
    }
  }

  external fun nativeOnSurfaceCreated()
  external fun nativeOnSurfaceChanged(width: Int, height: Int)
  external fun nativeOnDrawFrame()
  external fun nativeDestroy()
}