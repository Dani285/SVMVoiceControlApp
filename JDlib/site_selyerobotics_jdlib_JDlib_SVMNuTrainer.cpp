#include "site_selyerobotics_jdlib_JDlib_SVMNuTrainer.h"

#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_SetKernel(JNIEnv* env,
                                                                jobject thisObj,
                                                                jobject jkernel)
{
  svm_nu_trainer_type& svm_nu_trainer =
    memoryManager.Get<svm_nu_trainer_type>(env, thisObj);
  kernel_type& kernel = memoryManager.Get<kernel_type>(env, jkernel);

  svm_nu_trainer.set_kernel(kernel);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_SetNu(JNIEnv* env,
                                                            jobject thisObj,
                                                            jdouble nu)
{
  svm_nu_trainer_type& svm_nu_trainer =
    memoryManager.Get<svm_nu_trainer_type>(env, thisObj);

  svm_nu_trainer.set_nu(nu);
}

jobject
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_Train(JNIEnv* env,
                                                            jobject thisObj,
                                                            jobject jsamples,
                                                            jobject jlabels)
{
  svm_nu_trainer_type& svm_nu_trainer =
    memoryManager.Get<svm_nu_trainer_type>(env, thisObj);
  samples_type& samples = memoryManager.Get<samples_type>(env, jsamples);
  labels_type& labels = memoryManager.Get<labels_type>(env, jlabels);

  decision_funct_type decision_function = svm_nu_trainer.train(samples, labels);

  auto jlearned_function = memoryManager.CreateNative(
    env, "site/selyerobotics/jdlib/JDlib$LearnedFunction", decision_function);

  return jlearned_function;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_init(JNIEnv* env,
                                                           jobject thisObj)
{
  memoryManager.Create<svm_nu_trainer_type>(env, thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_Dispose(JNIEnv* env,
                                                              jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
