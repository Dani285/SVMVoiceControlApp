#include "site_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction.h"

#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024NormalizedProbabilisticFunction_Evaluate(
  JNIEnv* env,
  jobject thisObj,
  jobject sample)
{
  return memoryManager.Get<normalized_probabilistic_function_type>(
    env, thisObj)(memoryManager.Get<sample_type>(env, sample));
}

void
Java_site_selyerobotics_jdlib_JDlib_00024NormalizedProbabilisticFunction_SetNormalizer(
  JNIEnv* env,
  jobject thisObj,
  jobject normalizer)
{
  memoryManager.Get<normalized_probabilistic_function_type>(env, thisObj)
    .normalizer = memoryManager.Get<normalizer_type>(env, normalizer);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024NormalizedProbabilisticFunction_SetFunction(
  JNIEnv* env,
  jobject thisObj,
  jobject function)
{
  memoryManager.Get<normalized_probabilistic_function_type>(env, thisObj)
    .function = memoryManager.Get<probabilistic_funct_type>(env, function);
}

jlong
Java_site_selyerobotics_jdlib_JDlib_00024NormalizedProbabilisticFunction_BasisVectorsSize(
  JNIEnv* env,
  jobject thisObj)
{
  return memoryManager.Get<normalized_probabilistic_function_type>(env, thisObj)
    .function.decision_funct.basis_vectors.size();
}

void
Java_site_selyerobotics_jdlib_JDlib_00024NormalizedProbabilisticFunction_init(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Create<normalized_probabilistic_function_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024NormalizedProbabilisticFunction_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
