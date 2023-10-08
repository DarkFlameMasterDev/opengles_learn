package com.czb.opengles3_0

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLSurfaceRenderer : GLSurfaceView.Renderer {

  val rendererMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
  private var nativeRenderer: MyNativeRenderer = MyNativeRenderer()

  override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
    nativeRenderer.nativeOnSurfaceCreated()
  }

  override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
    nativeRenderer.nativeOnSurfaceChanged(width, height)
  }

  override fun onDrawFrame(gl: GL10?) {
    nativeRenderer.nativeOnDrawFrame()
  }

  fun destroy() {
    nativeRenderer.nativeDestroy()
  }

}