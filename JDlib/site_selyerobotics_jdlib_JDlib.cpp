#include "site_selyerobotics_jdlib_JDlib.h"
#include "memorymanager.hpp"
#include "types.hpp"
#include <string>

extern MemoryManager memoryManager;

std::string
jstring2string(JNIEnv* env, jstring jStr)
{
  if (!jStr)
    return "";

  const jclass stringClass = env->GetObjectClass(jStr);
  const jmethodID getBytes =
    env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
  const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(
    jStr, getBytes, env->NewStringUTF("UTF-8"));

  size_t length = (size_t)env->GetArrayLength(stringJbytes);
  jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

  std::string ret = std::string((char*)pBytes, length);
  env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

  env->DeleteLocalRef(stringJbytes);
  env->DeleteLocalRef(stringClass);
  return ret;
}

jobject
Java_site_selyerobotics_jdlib_JDlib_Reduced2(JNIEnv* env,
                                             jclass parent,
                                             jobject jtrainer,
                                             jlong num_bv,
                                             jdouble eps)
{

  auto& trainer = memoryManager.Get<svm_nu_trainer_type>(env, jtrainer);

  auto reduced = dlib::reduced2(trainer, num_bv, eps);

  auto jresult = memoryManager.CreateNative(
    env,
    "site/selyerobotics/jdlib/JDlib$ReducedDecisionFunctionTrainer2",
    reduced);

  return jresult;
}

void
Java_site_selyerobotics_jdlib_JDlib_RandomizeSamples(JNIEnv* env,
                                                     jclass parent,
                                                     jobject jsamples,
                                                     jobject jlabels)
{
  auto& samples = memoryManager.Get<samples_type>(env, jsamples);
  auto& labels = memoryManager.Get<labels_type>(env, jlabels);
  dlib::randomize_samples(samples, labels);
}

jdouble
Java_site_selyerobotics_jdlib_JDlib_MaximumNu(JNIEnv* env,
                                              jclass parent,
                                              jobject jlabels)
{
  auto& labels = memoryManager.Get<labels_type>(env, jlabels);
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
  auto& trainer = memoryManager.Get<svm_nu_trainer_type>(env, jtrainer);
  auto& samples = memoryManager.Get<samples_type>(env, jsamples);
  auto& labels = memoryManager.Get<labels_type>(env, jlabels);

  sample_type confusion =
    dlib::cross_validate_trainer(trainer, samples, labels, fold);

  jobject jresult = memoryManager.CreateNative<sample_type>(
    env, "site/selyerobotics/jdlib/JDlib$Matrix", confusion);

  return jresult;
}

void
Java_site_selyerobotics_jdlib_JDlib_Serialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_LearnedFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring jfileName,
  jobject jdecisionFunction)
{
  auto fileName = jstring2string(env, jfileName);
  auto& decisionFunction =
    memoryManager.Get<normalized_function_type>(env, jdecisionFunction);
  dlib::serialize(fileName) << decisionFunction;
}

void
Java_site_selyerobotics_jdlib_JDlib_Serialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring jfileName,
  jobject jProbabilisticDecisionFunction)
{
  auto fileName = jstring2string(env, jfileName);
  auto& probabilisticDecisionFunction =
    memoryManager.Get<normalized_probabilistic_function_type>(
      env, jProbabilisticDecisionFunction);
  dlib::serialize(fileName) << probabilisticDecisionFunction;
}

void
Java_site_selyerobotics_jdlib_JDlib_Deserialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_LearnedFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring jfileName,
  jobject jdecisionFunction)
{
  auto fileName = jstring2string(env, jfileName);
  auto& decisionFunction =
    memoryManager.Get<normalized_function_type>(env, jdecisionFunction);
  dlib::deserialize(fileName) >> decisionFunction;
}

void
Java_site_selyerobotics_jdlib_JDlib_Deserialize__Ljava_lang_String_2Lsite_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction_2(
  JNIEnv* env,
  jclass parent,
  jstring jfileName,
  jobject jProbabilisticDecisionFunction)
{
  auto fileName = jstring2string(env, jfileName);
  auto& probabilisticDecisionFunction =
    memoryManager.Get<normalized_probabilistic_function_type>(
      env, jProbabilisticDecisionFunction);
  dlib::deserialize(fileName) >> probabilisticDecisionFunction;
}

jobject
Java_site_selyerobotics_jdlib_JDlib_TrainProbabilisticDecisionFunction__Lsite_selyerobotics_jdlib_JDlib_SVMNuTrainer_2Lsite_selyerobotics_jdlib_JDlib_VectorM_2Lsite_selyerobotics_jdlib_JDlib_Vectord_2J(
  JNIEnv* env,
  jclass parent,
  jobject jtrainer,
  jobject jsamples,
  jobject jlabels,
  jlong fold)
{
  auto& trainer = memoryManager.Get<svm_nu_trainer_type>(env, jtrainer);
  auto& samples = memoryManager.Get<samples_type>(env, jsamples);
  auto& labels = memoryManager.Get<labels_type>(env, jlabels);

  auto ProbabilisticDecisionFunction =
    dlib::train_probabilistic_decision_function(trainer, samples, labels, fold);

  return memoryManager.CreateNative(
    env,
    "site/selyerobotics/jdlib/JDlib$ProbabilisticDecisionFunction",
    ProbabilisticDecisionFunction);
}

jobject
Java_site_selyerobotics_jdlib_JDlib_TrainProbabilisticDecisionFunction__Lsite_selyerobotics_jdlib_JDlib_ReducedDecisionFunctionTrainer2_2Lsite_selyerobotics_jdlib_JDlib_VectorM_2Lsite_selyerobotics_jdlib_JDlib_Vectord_2J(
  JNIEnv* env,
  jclass thisObj,
  jobject jtrainer,
  jobject jsamples,
  jobject jlabels,
  jlong fold)
{
  auto& trainer =
    memoryManager.Get<ReducedDecisionFunctionTrainer2_type>(env, jtrainer);
  auto& samples = memoryManager.Get<samples_type>(env, jsamples);
  auto& labels = memoryManager.Get<labels_type>(env, jlabels);

  auto ProbabilisticDecisionFunction =
    dlib::train_probabilistic_decision_function(trainer, samples, labels, fold);

  return memoryManager.CreateNative(
    env,
    "site/selyerobotics/jdlib/JDlib$ProbabilisticDecisionFunction",
    ProbabilisticDecisionFunction);
}
