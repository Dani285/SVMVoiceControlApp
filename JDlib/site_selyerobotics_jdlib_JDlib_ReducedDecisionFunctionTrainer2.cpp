#include "site_selyerobotics_jdlib_JDlib_ReducedDecisionFunctionTrainer2.h"
#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;
void
Java_site_selyerobotics_jdlib_JDlib_00024ReducedDecisionFunctionTrainer2_init(
  JNIEnv* env,
  jobject thisObj)
{
  assert(env);
  assert(thisObj);
  memoryManager.Create<probabilistic_funct_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024ReducedDecisionFunctionTrainer2_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  assert(env);
  assert(thisObj);
  memoryManager.Dispose(env, thisObj);
}

jobject
Java_site_selyerobotics_jdlib_JDlib_00024ReducedDecisionFunctionTrainer2_Train(
  JNIEnv* env,
  jobject thisObj,
  jobject jsamples,
  jobject jlabels)
{
  assert(env);
  assert(thisObj);
  assert(jsamples);
  assert(jlabels);

  auto& reduced =
    memoryManager.Get<ReducedDecisionFunctionTrainer2_type>(env, thisObj);
  auto& samples = memoryManager.Get<samples_type>(env, jsamples);
  auto& labels = memoryManager.Get<labels_type>(env, jlabels);

  decision_funct_type decision_function = reduced.train(samples, labels);

  return memoryManager.CreateNative(
    env, "site/selyerobotics/jdlib/JDlib$DecisionFunction", decision_function);
}
