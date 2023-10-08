package com.czb.opengles3_0

import android.content.pm.PackageManager
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.czb.opengles3_0.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

  private lateinit var binding: ActivityMainBinding

  private val glSurfaceRenderer = MyGLSurfaceRenderer()

  private val permissions = arrayOf(
    "android.permission.WRITE_EXTERNAL_STORAGE",
    "android.permission.READ_EXTERNAL_STORAGE"
  )

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    binding = ActivityMainBinding.inflate(layoutInflater)
    setContentView(binding.root)

    binding.glSurface.mRenderer = glSurfaceRenderer
  }

  override fun onDestroy() {
    super.onDestroy()
    glSurfaceRenderer.destroy()
  }
}