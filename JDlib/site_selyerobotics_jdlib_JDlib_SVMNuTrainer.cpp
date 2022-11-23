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
    memoryManager.Get<svm_nu_trainer_type>(thisObj);
  kernel_type& kernel = memoryManager.Get<kernel_type>(jkernel);

  svm_nu_trainer.set_kernel(kernel);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_SetNu(JNIEnv* env,
                                                            jobject thisObj,
                                                            jdouble nu)
{
  svm_nu_trainer_type& svm_nu_trainer =
    memoryManager.Get<svm_nu_trainer_type>(thisObj);

  svm_nu_trainer.set_nu(nu);
}

jobject
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_Train(JNIEnv* env,
                                                            jobject thisObj,
                                                            jobject jsamples,
                                                            jobject jlabels)
{
  svm_nu_trainer_type& svm_nu_trainer =
    memoryManager.Get<svm_nu_trainer_type>(thisObj);
  samples_type& samples = memoryManager.Get<samples_type>(jsamples);
  labels_type& labels = memoryManager.Get<labels_type>(jlabels);

  decision_funct_type decision_function = svm_nu_trainer.train(samples, labels);

  auto jlearned_function = memoryManager.CreateNative<decision_funct_type>(
    env, "site/selyerobotics/jdlib/JDlib/LearnedFunction");
  memoryManager.Get<decision_funct_type>(jlearned_function) = decision_function;

  return jlearned_function;
}

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_init(JNIEnv* env,
                                                           jobject thisObj)
{
  memoryManager.Create<svm_nu_trainer_type>(thisObj);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024SVMNuTrainer_Dispose(JNIEnv* env,
                                                              jobject thisObj)
{
  memoryManager.Dispose(thisObj);
}
