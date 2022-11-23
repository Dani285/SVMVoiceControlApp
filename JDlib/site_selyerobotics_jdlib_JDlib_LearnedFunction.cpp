#include "site_selyerobotics_jdlib_JDlib_LearnedFunction.h"

#include "memorymanager.hpp"
#include "types.hpp"
#include <dlib/svm.h>
extern MemoryManager memoryManager;

jdouble
Java_site_selyerobotics_jdlib_JDlib_00024LearnedFunction_Evaluate(
  JNIEnv* env,
  jobject thisObj,
  jobject jsample)
{
  auto& normalized_function =
    memoryManager.Get<normalized_function_type>(env, thisObj);
  auto& sample = memoryManager.Get<sample_type>(env, jsample);

  return normalized_function(sample);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024LearnedFunction_SetNormalizer(
  JNIEnv* env,
  jobject thisObj,
  jobject jnormalizer)
{
  auto& normalized_function =
    memoryManager.Get<normalized_function_type>(env, thisObj);
  auto& normalizer = memoryManager.Get<normalizer_type>(env, jnormalizer);
  normalized_function.normalizer = normalizer;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024LearnedFunction_SetFunction(
  JNIEnv* env,
  jobject thisObj,
  jobject jfunction)
{
  auto& normalized_function =
    memoryManager.Get<normalized_function_type>(env, thisObj);
  auto& function = memoryManager.Get<decision_funct_type>(env, jfunction);
  normalized_function.function = function;
}

jlong
Java_site_selyerobotics_jdlib_JDlib_00024LearnedFunction_BasisVectorsSize(
  JNIEnv* env,
  jobject thisObj)
{
  auto& normalized_function =
    memoryManager.Get<normalized_function_type>(env, thisObj);
  return normalized_function.function.basis_vectors.size();
}

void
Java_site_selyerobotics_jdlib_JDlib_00024LearnedFunction_init(JNIEnv* env,
                                                              jobject thisObj)
{
  memoryManager.Create<normalized_function_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024LearnedFunction_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
