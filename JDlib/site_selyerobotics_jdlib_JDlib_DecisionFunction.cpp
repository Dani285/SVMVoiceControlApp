#include "site_selyerobotics_jdlib_JDlib_DecisionFunction.h"
#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;

void
Java_site_selyerobotics_jdlib_JDlib_00024DecisionFunction_init(JNIEnv* env,
                                                               jobject thisObj)
{
  memoryManager.Create<decision_funct_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024DecisionFunction_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024DecisionFunction_Evaluate(
  JNIEnv* env,
  jobject thisObj,
  jobject jsample)
{
  auto& decisionFunction = memoryManager.Get<decision_funct_type>(env, thisObj);
  auto& sample = memoryManager.Get<sample_type>(env, jsample);

  return decisionFunction(sample);
}
