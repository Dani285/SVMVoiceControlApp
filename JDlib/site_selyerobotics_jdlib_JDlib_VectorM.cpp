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
  memoryManager.Get<samples_type>(thisObj).push_back(
    memoryManager.Get<sample_type>(matrix));
}

jlong
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Size(JNIEnv* env,
                                                      jobject thisObj)
{
  return memoryManager.Get<samples_type>(thisObj).size();
}

jobject
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Get(JNIEnv* env,
                                                     jobject thisObj,
                                                     jlong index)
{

  jobject object = memoryManager.CreateNative<dlib::matrix<double>>(
    env, "site/selyerobotics/jdlib/JDlib/Matrix");

  memoryManager.Get<dlib::matrix<double>>(object) =
    memoryManager.Get<samples_type>(thisObj).at(index);

  return object;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Set(JNIEnv* env,
                                                     jobject thisObj,
                                                     jlong index,
                                                     jobject matrixObj)
{
  memoryManager.Get<samples_type>(thisObj).at(index) =
    memoryManager.Get<sample_type>(matrixObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_init(JNIEnv* env,
                                                      jobject thisObj)
{
  memoryManager.Create<samples_type>(thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorM_Dispose(JNIEnv* env,
                                                         jobject thisObj)
{
  memoryManager.Dispose(thisObj);
}
