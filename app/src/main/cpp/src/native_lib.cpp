//
// Created by 曹璐韬 on 2023/10/8.
//
#include <jni.h>
#include <string>
#include "globalAssetManager.h"
#include "log_utils.h"
#include "MyGLRenderContext.h"

#define NATIVE_RENDER_CLASS_NAME "com/czb/opengles3_0/MyNativeRenderer"
#define NATIVE_ASSET_UTILS_CLASS_NAME "com/czb/opengles3_0/MyNativeRenderer"
#define NATIVE_ASSET_UTILS_COMPANION_CLASS_NAME "com/czb/opengles3_0/AssetUtils$Companion"

AAssetManager *globalAssetManager;

#ifdef __cplusplus
extern "C" {
#endif

void nativeOnSurfaceCreated(JNIEnv *env, jobject thiz) {
  MyGLRenderContext::getInstance()->onSurfaceCreated();
}

void nativeOnSurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
  MyGLRenderContext::getInstance()->onSurfaceChanged(width, height);
}

void nativeOnDrawFrame(JNIEnv *env, jobject thiz) {
  MyGLRenderContext::getInstance()->onDrawFrame();
}

void nativeDestroy(JNIEnv *env, jobject thiz) {
  MyGLRenderContext::getInstance()->destroy();
}

void setNativeAssetManager(JNIEnv *env, jobject thiz, jobject assetManager) {
  globalAssetManager = AAssetManager_fromJava(env, assetManager);
  LOGE("setNativeAssetManager globalAssetManager address:%d", globalAssetManager);
//  AAsset *asset = AAssetManager_open(globalAssetManager, "triangle_vs.glsl",
//                                     AASSET_MODE_BUFFER);
//
//  if (asset != nullptr) {
//    // 读取文件内容
//    const void *data = AAsset_getBuffer(asset);
//
//    // 将内容写入 Android Logcat
//    __android_log_print(ANDROID_LOG_ERROR, "YourAppTag", "Asset Content: %s",
//                        static_cast<const char *>(data));
//
//    // 关闭文件
//    AAsset_close(asset);
//  } else {
//    __android_log_print(ANDROID_LOG_ERROR, "YourAppTag", "Asset Content: %s",
//                        "AAssetManager open failed");
//  }
}

#ifdef __cplusplus
}
#endif


static JNINativeMethod renderMethods[] = {
    {"nativeOnSurfaceCreated", "()V",   (void *) nativeOnSurfaceCreated},
    {"nativeOnSurfaceChanged", "(II)V", (void *) nativeOnSurfaceChanged},
    {"nativeOnDrawFrame",      "()V",   (void *) nativeOnDrawFrame},
    {"nativeDestroy",          "()V",   (void *) nativeDestroy}
};

static JNINativeMethod assetUtilsMethods[] = {
    {"setNativeAssetManager", "(Landroid/content/res/AssetManager;)V",
     (void *) setNativeAssetManager}
};

static int
RegisterNatives(JNIEnv *env, const char *className, JNINativeMethod methods[], int length) {
  LOGE("Register %s Natives", className);
  jclass clazz = env->FindClass(className);
  if (clazz == nullptr) {
    LOGE("can't find class: %s", className);
    return JNI_ERR;
  }
  return env->RegisterNatives(clazz, methods, length);
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

extern "C"
jint JNI_OnLoad(JavaVM *jvm, void *p) {
  LOGE("=== JNI_OnLoad ===");
  // 置空 env
  JNIEnv *env = nullptr;
  // 判断 JNI 版本
  if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }
  // 注册 Native 方法
  jint renderResult =
      RegisterNatives(env, NATIVE_RENDER_CLASS_NAME, renderMethods,
                      sizeof(renderMethods) / sizeof(renderMethods[0]));
  jint assetResult =
      RegisterNatives(env, NATIVE_ASSET_UTILS_COMPANION_CLASS_NAME, assetUtilsMethods,
                      sizeof(assetUtilsMethods) / sizeof(assetUtilsMethods[0]));
  LOGE("renderResult: %d", renderResult);
  LOGE("assetResult: %d", assetResult);
  if (renderResult != JNI_OK && assetResult != JNI_OK) {
    return JNI_OK;
  }
  return JNI_VERSION_1_6;
}

extern "C"
void JNI_OnUnload(JavaVM *jvm, void *p) {
  // 置空 env
  JNIEnv *env = nullptr;
  if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
    return;
  }

  // 注销 Native 方法
  UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);
  UnregisterNativeMethods(env, NATIVE_ASSET_UTILS_COMPANION_CLASS_NAME);
}
