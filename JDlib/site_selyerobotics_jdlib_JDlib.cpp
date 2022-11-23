#include "site_selyerobotics_jdlib_JDlib.h"
#include "memorymanager.hpp"
#include "types.hpp"

extern MemoryManager memoryManager;

jobject
Java_site_selyerobotics_jdlib_JDlib_TrainProbabilisticDecisionFunction(
  JNIEnv* env,
  jclass parent,
  jobject,
  jobject,
  jobject,
  jlong)
{}

jobject
Java_site_selyerobotics_jdlib_JDlib_Reduced2(JNIEnv* env,
                                             jclass parent,
                                             jobject,
                                             jlong,
                                             jdouble)
{}

void
Java_site_selyerobotics_jdlib_JDlib_RandomizeSamples(JNIEnv* env,
                                                     jclass parent,
                                                     jobject jsamples,
                                                     jobject jlabels)
{
  auto& samples = memoryManager.Get<samples_type>(jsamples);
  auto& labels = memoryManager.Get<labels_type>(jlabels);
  dlib::randomize_samples(samples, labels);
}

jdouble
Java_site_selyerobotics_jdlib_JDlib_MaximumNu(JNIEnv* env,
                                              jclass parent,
                                              jobject jlabels)
{
  auto& labels = memoryManager.Get<labels_type>(jlabels);
  return dlib::maximum_nu(labels);
}

jobject
Java_site_selyerobotics_jdlib_JDlib_CrossValidateTrainer(JNIEnv* env,
                                                         jclass parent,
                                                         jobject jtrainer,
                                                         jobject jsamples,
                                                         jobject jlabels,
                                                         jlong fold)
{
  auto& trainer = memoryManager.Get<svm_nu_trainer_type>(jtrainer);
  auto& samples = memoryManager.Get<samples_type>(jsamples);
  auto& labels = memoryManager.Get<labels_type>(jlabels);
  sample_type confusion =
    dlib::cross_validate_trainer(trainer, samples, labels, fold);

  jobject jresult = memoryManager.CreateNative<sample_type>(
    env, "/site/selyerobotics/jdlib/JDlib/Matrix");
  auto& result = memoryManager.Get<sample_type>(jresult);
  result = confusion;

  return jresult;
}

void
Java_site_selyerobotics_jdlib_JDlib_Serialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_LearnedFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring,
  jobject)
{}

void
Java_site_selyerobotics_jdlib_JDlib_Serialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring,
  jobject)
{}

void
Java_site_selyerobotics_jdlib_JDlib_Deserialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_LearnedFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring,
  jobject)
{}

void
Java_site_selyerobotics_jdlib_JDlib_Deserialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring,
  jobject)
{}
