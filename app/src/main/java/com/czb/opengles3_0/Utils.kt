package com.czb.opengles3_0

import android.util.Log

class Utils {

    companion object {
        private const val TAG = "jni_opengl"

        fun log(content: String, tag: String = TAG, logLevel: LogLevel = LogLevel.D) {
            when (logLevel) {
                LogLevel.I -> Log.i(tag, content)
                LogLevel.D -> Log.d(tag, content)
                LogLevel.W -> Log.w(tag, content)
                LogLevel.E -> Log.e(tag, content)
            }
        }
    }

    enum class LogLevel {
        I,
        D,
        W,
        E
    }
}
