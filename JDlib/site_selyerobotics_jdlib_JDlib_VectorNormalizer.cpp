#include "site_selyerobotics_jdlib_JDlib_VectorNormalizer.h"
#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorNormalizer_Train(
  JNIEnv* env,
  jobject thisObj,
  jobject jsamples)
{
  auto& normalizer = memoryManager.Get<normalizer_type>(env, thisObj);
  auto& samples = memoryManager.Get<samples_type>(env, jsamples);
  normalizer.train(samples);
}

jobject
Java_site_selyerobotics_jdlib_JDlib_00024VectorNormalizer_Normalize(
  JNIEnv* env,
  jobject thisObj,
  jobject jsample)
{
  auto& normalizer = memoryManager.Get<normalizer_type>(env, thisObj);
  auto& sample = memoryManager.Get<sample_type>(env, jsample);
  auto normalized_sample = normalizer(sample);
  jobject jresult = memoryManager.CreateNative(
    env, "site/selyerobotics/jdlib/JDlib$Matrix", normalized_sample);

  return jresult;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorNormalizer_init(JNIEnv* env,
                                                               jobject thisObj)
{
  memoryManager.Create<normalizer_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024VectorNormalizer_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
