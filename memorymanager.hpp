#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <any>
#include <cassert>
#include <jni.h>
#include <map>
#include <memory>

class MemoryManager
{
private:
  std::map<int64_t, std::any> _Cache;
  static int64_t IncrementID;

public:
  int64_t AutoKey();

  void SetKey(JNIEnv* env, jobject thisObj, int64_t key);

  int64_t GetKey(JNIEnv* env, jobject thisObj);

  void Dispose(JNIEnv* env, jobject parent);

  template<class T0, class... MTs>
  T0& Create(JNIEnv* env, jobject parent, MTs... mts)
  {
    auto key = AutoKey();
    SetKey(env, parent, key);

    _Cache[key] = std::make_any<T0>(mts...);
    return std::any_cast<T0&>(_Cache.at(key));
  }

  template<class T0>
  T0& Get(JNIEnv* env, jobject parent)
  {
    auto key = GetKey(env, parent);
    return std::any_cast<T0&>(_Cache.at(key));
  }

  template<class T0>
  jobject CreateNative(JNIEnv* env, std::string className, T0& t0)
  {
    assert(env);
    jclass jcls = env->FindClass(className.c_str());
    if (!jcls) {
      throw std::runtime_error("class not found: " + className);
    }
    assert(jcls);
    jmethodID constructor = env->GetMethodID(jcls, "<init>", "()V");
    assert(constructor);
    jobject object = env->NewObject(jcls, constructor);
    assert(object);
    auto& obj = Create<T0>(env, object);
    obj = t0;

    return object;
  }
};

#endif // MEMORYMANAGER_HPP
