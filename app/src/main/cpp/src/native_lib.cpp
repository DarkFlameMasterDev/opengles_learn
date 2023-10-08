//
// Created by 曹璐韬 on 2023/10/8.
//
#include <jni.h>
#include <string>
#include "android_log.h"

#define NATIVE_RENDER_CLASS_NAME "com/czb/opengles3_0/MyNativeRenderer"

#ifdef __cplusplus
extern "C" {
#endif

void nativeOnSurfaceCreated(JNIEnv *env, jobject thiz) {
  // TODO: implement native_OnSurfaceCreated()
}

void nativeOnSurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height) {

}

void nativeOnDrawFrame(JNIEnv *env, jobject thiz) {

}

void nativeDestroy(JNIEnv *env, jobject thiz) {

}

#ifdef __cplusplus
}
#endif

static JNINativeMethod methods[] = {
    {"nativeOnSurfaceCreated", "()V",   (void *) nativeOnSurfaceCreated},
    {"nativeOnSurfaceChanged", "(II)V", (void *) nativeOnSurfaceChanged},
    {"nativeOnDrawFrame",      "()V",   (void *) nativeOnDrawFrame},
    {"nativeDestroy",          "()V",   (void *) nativeDestroy}
};

static int RegisterNatives(JNIEnv *env) {
  LOGE("RegisterNatives");
  jclass clazz = env->FindClass(NATIVE_RENDER_CLASS_NAME);
  if (clazz == nullptr) {
    LOGE("can't find class: %s", NATIVE_RENDER_CLASS_NAME);
    return JNI_ERR;
  }
  int len = sizeof(methods) / sizeof(methods[0]);
  return env->RegisterNatives(clazz, methods, len);
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className) {
  LOGE("UnregisterNativeMethods");
  jclass clazz = env->FindClass(className);
  if (clazz == nullptr) {
    LOGE("UnregisterNativeMethods fail. %s == NULL", className);
    return;
  }
  env->UnregisterNatives(clazz);
}

extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p) {
  LOGE("=== JNI_OnLoad ===");
  // 置空 env
  JNIEnv *env = nullptr;
  // 判断 JNI 版本
  if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }
  // 注册 Native 方法
  jint result = RegisterNatives(env);
  LOGE("result: %d", result);
  if (result != JNI_OK) {
    return result;
  }
  return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p) {
  // 置空 env
  JNIEnv *env = nullptr;
  if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
    return;
  }

  // 注销 Native 方法
  UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);
}