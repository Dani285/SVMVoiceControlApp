#include "site_selyerobotics_jdlib_JDlib_Vectord.h"

#include "memorymanager.hpp"
#include "types.hpp"
#include <vector>

extern MemoryManager memoryManager;

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Add(JNIEnv* env,
                                                     jobject thisObj,
                                                     jdouble value)
{
  memoryManager.Get<labels_type>(env,thisObj).push_back(value);
}

jlong
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Size(JNIEnv*env, jobject thisObj)
{
  return memoryManager.Get<labels_type>(env,thisObj).size();
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_init(JNIEnv*env, jobject thisObj)
{
  memoryManager.Create<labels_type>(env,thisObj);
}

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Get(JNIEnv*env,
                                                     jobject thisObj,
                                                     jlong index)
{
  return memoryManager.Get<labels_type>(env,thisObj).at(index);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Set(JNIEnv*env,
                                                     jobject thisObj,
                                                     jlong index,
                                                     jdouble value)
{
  memoryManager.Get<labels_type>(env,thisObj).at(index) = value;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Dispose(JNIEnv*env,
                                                         jobject thisObj)
{
  memoryManager.Dispose(env,thisObj);
}
