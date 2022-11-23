#include "site_selyerobotics_jdlib_JDlib_ProbabilisticDecisionFunction.h"
#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024ProbabilisticDecisionFunction_Evaluate(
  JNIEnv* env,
  jobject thisObj,
  jobject jsample)
{
  auto& ProbabilisticDecisionFunction =
    memoryManager.Get<probabilistic_funct_type>(env, thisObj);
  auto& sample = memoryManager.Get<sample_type>(env, jsample);

  return ProbabilisticDecisionFunction(sample);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024ProbabilisticDecisionFunction_init(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Create<probabilistic_funct_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024ProbabilisticDecisionFunction_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
