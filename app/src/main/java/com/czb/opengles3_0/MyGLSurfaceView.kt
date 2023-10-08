package com.czb.opengles3_0

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet

class MyGLSurfaceView(context: Context, attrs: AttributeSet?) : GLSurfaceView(context, attrs) {

  var renderer: MyGLSurfaceRenderer? = null
    set(r) {
      field = r
      setRenderer(r)
      renderMode = r?.rendererMode ?: -1
    }

  init {
    setEGLContextClientVersion(2)
    setEGLConfigChooser(8, 8, 8, 8, 16, 8);
  }

  constructor(context: Context) : this(context, null)
}