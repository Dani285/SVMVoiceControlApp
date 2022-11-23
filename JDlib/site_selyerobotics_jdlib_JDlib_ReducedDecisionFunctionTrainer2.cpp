#include "site_selyerobotics_jdlib_JDlib_ReducedDecisionFunctionTrainer2.h"
#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;
void
Java_site_selyerobotics_jdlib_JDlib_00024ReducedDecisionFunctionTrainer2_init(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Create<probabilistic_funct_type>(env,thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024ReducedDecisionFunctionTrainer2_Dispose(
  JNIEnv* env,
  jobject thisObj)
{
  memoryManager.Dispose(env,thisObj);
}
