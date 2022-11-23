#include "site_selyerobotics_jdlib_JDlib_Matrix.h"

#include "memorymanager.hpp"
#include "types.hpp"
#include <dlib/matrix.h>

extern MemoryManager memoryManager;

void
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_set(JNIEnv* env,
                                                    jobject thisObj,
                                                    jint row,
                                                    jint col,
                                                    jdouble value)
{
  memoryManager.Get<sample_type>(env, thisObj)(row, col) = value;
}

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_get(JNIEnv* env,
                                                    jobject thisObj,
                                                    jint row,
                                                    jint col)
{
  return memoryManager.Get<sample_type>(env, thisObj)(row, col);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_Dispose(JNIEnv* env,
                                                        jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_init__(JNIEnv* env,
                                                       jobject thisObj)
{
  memoryManager.Create<sample_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_init__II(JNIEnv* env,
                                                         jobject thisObj,
                                                         jint rows,
                                                         jint cols)
{
  memoryManager.Create<sample_type>(env, thisObj, rows, cols);
}

jint
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_nc(JNIEnv* env, jobject thisObj)
{
  assert(env);
  assert(thisObj);

  auto& matrix = memoryManager.Get<sample_type>(env, thisObj);

  return matrix.nc();
}

jint
Java_site_selyerobotics_jdlib_JDlib_00024Matrix_nr(JNIEnv* env, jobject thisObj)
{
  assert(env);
  assert(thisObj);

  auto& matrix = memoryManager.Get<sample_type>(env, thisObj);

  return matrix.nr();
}
