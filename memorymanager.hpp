#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <any>
#include <jni.h>
#include <map>
#include <memory>

class MemoryManager
{
private:
  std::map<jobject, std::any> _Cache;

public:
  template<class T0, class... MTs>
  void Create(jobject parent, MTs... mts)
  {
    _Cache[parent] = std::make_any<T0>(mts...);
  }

  template<class T0>
  T0& Get(jobject parent)
  {
    return std::any_cast<T0&>(_Cache.at(parent));
  }

  void Dispose(jobject parent) { _Cache.erase(parent); }

  template<class T0>
  jobject CreateNative(JNIEnv* env, std::string className)
  {
    jclass jcls = env->FindClass(className.c_str());
    jmethodID constructor = env->GetMethodID(jcls, "<init>", "()V");
    jobject object = env->NewObject(jcls, constructor);

    return object;
  }
};

#endif // MEMORYMANAGER_HPP
