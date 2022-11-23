#include "site_selyerobotics_jdlib_JDlib_Vectord.h"

#include "memorymanager.hpp"
#include <vector>

extern MemoryManager memoryManager;
using OType = std::vector<double>;

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Add(JNIEnv*,
                                                     jobject thisObj,
                                                     jdouble value)
{
  memoryManager.Get<OType>(thisObj).push_back(value);
}

jlong
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Size(JNIEnv*, jobject thisObj)
{
  return memoryManager.Get<OType>(thisObj).size();
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_init(JNIEnv*, jobject thisObj)
{
  memoryManager.Create<OType>(thisObj);
}

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Get(JNIEnv*,
                                                     jobject thisObj,
                                                     jlong index)
{
  return memoryManager.Get<OType>(thisObj).at(index);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Set(JNIEnv*,
                                                     jobject thisObj,
                                                     jlong index,
                                                     jdouble value)
{
  memoryManager.Get<OType>(thisObj).at(index) = value;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024Vectord_Dispose(JNIEnv*,
                                                         jobject thisObj)
{
  memoryManager.Dispose(thisObj);
}
