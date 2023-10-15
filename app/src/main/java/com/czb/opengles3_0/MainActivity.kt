package com.czb.opengles3_0

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.czb.opengles3_0.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

  private lateinit var binding: ActivityMainBinding

  private val glSurfaceRenderer = MyGLSurfaceRenderer()

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    binding = ActivityMainBinding.inflate(layoutInflater)
    setContentView(binding.root)
    binding.glSurfaceView.mRenderer = glSurfaceRenderer
  }

  override fun onDestroy() {
    super.onDestroy()
    glSurfaceRenderer.destroy()
  }
}