package com.czb.opengles3_0

import android.content.pm.PackageManager
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.czb.opengles3_0.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

  private lateinit var binding: ActivityMainBinding

  private lateinit var glSurfaceView: MyGLSurfaceView
  private val glSurfaceRenderer = MyGLSurfaceRenderer()

  private val permissions = arrayOf(
    "android.permission.WRITE_EXTERNAL_STORAGE",
    "android.permission.READ_EXTERNAL_STORAGE"
  )

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    binding = ActivityMainBinding.inflate(layoutInflater)
    setContentView(binding.root)

    for (per in permissions) {
      if (ActivityCompat.checkSelfPermission(this, per) != PackageManager.PERMISSION_GRANTED) {
        requestPermissions(permissions, 100)
        return
      }
    }
    glSurfaceView.renderer = glSurfaceRenderer
  }

  override fun onRequestPermissionsResult(
    requestCode: Int,
    permissions: Array<String?>,
    grantResults: IntArray
  ) {
    super.onRequestPermissionsResult(requestCode, permissions, grantResults)
    if (requestCode == 100) {
      if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
        glSurfaceView.renderer = glSurfaceRenderer
      }
    }
  }

  override fun onDestroy() {
    super.onDestroy()
    glSurfaceRenderer.destroy()
  }
}