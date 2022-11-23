#include "site_selyerobotics_jdlib_JDlib_RBF.h"

#include "memorymanager.hpp"
#include <dlib/svm.h>

extern MemoryManager memoryManager;

using sample_type = dlib::matrix<double>;
using kernel_type = dlib::radial_basis_kernel<sample_type>;

void
Java_site_selyerobotics_jdlib_JDlib_00024RBF_init(JNIEnv* env,
                                                  jobject thisObj,
                                                  jdouble gamma)
{
  memoryManager.Create<kernel_type>(env, thisObj, gamma);
}

void
Java_site_selyerobotics_jdlib_JDlib_00024RBF_Dispose(JNIEnv* env,
                                                     jobject thisObj)
{
  memoryManager.Dispose(env, thisObj);
}
