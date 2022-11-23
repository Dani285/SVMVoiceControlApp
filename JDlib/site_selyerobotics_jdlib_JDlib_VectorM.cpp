#include "site_selyerobotics_jdlib_JDlib_VectorM.h"
#include "memorymanager.hpp"
#include "types.hpp"
#include <dlib/matrix.h>
#include <vector>

extern MemoryManager memoryManager;

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Add(JNIEnv* env,
                                                     jobject thisObj,
                                                     jobject matrix)
{
  memoryManager.Get<samples_type>(env, thisObj)
    .push_back(memoryManager.Get<sample_type>(env, matrix));
}

jlong
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Size(JNIEnv* env,
                                                      jobject thisObj)
{
  return memoryManager.Get<samples_type>(env, thisObj).size();
}

jobject
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Get(JNIEnv* env,
                                                     jobject thisObj,
                                                     jlong index)
{
  assert(env);
  assert(thisObj);

  auto& value = memoryManager.Get<samples_type>(env, thisObj).at(index);
  jobject object = memoryManager.CreateNative(
    env, "site/selyerobotics/jdlib/JDlib$Matrix", value);

  assert(object);
  return object;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Set(JNIEnv* env,
                                                     jobject thisObj,
                                                     jlong index,
                                                     jobject matrixObj)
{
  assert(env);
  assert(thisObj);
  memoryManager.Get<samples_type>(env, thisObj).at(index) =
    memoryManager.Get<sample_type>(env, matrixObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_init(JNIEnv* env,
                                                      jobject thisObj)
{
  memoryManager.Create<samples_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Dispose(JNIEnv* env,
                                                         jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
