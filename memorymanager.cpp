#include "memorymanager.hpp"

int64_t MemoryManager::IncrementID = 1000;

MemoryManager memoryManager;

int64_t
MemoryManager::AutoKey()
{
  return IncrementID++;
}

void
MemoryManager::SetKey(JNIEnv* env, jobject thisObj, int64_t key)
{
  auto jclass = env->GetObjectClass(thisObj);
  assert(jclass);

  jfieldID field =
    env->GetFieldID(jclass, "NativeHandle", "J"); // "J" = long field
  assert(field);
  env->SetLongField(thisObj, field, key);

  return;
}

int64_t
MemoryManager::GetKey(JNIEnv* env, jobject thisObj)
{
  auto jclass = env->GetObjectClass(thisObj);
  assert(jclass);

  jfieldID field =
    env->GetFieldID(jclass, "NativeHandle", "J"); // "J" = long field

  assert(field);
  jlong key = env->GetLongField(thisObj, field);

  return key;
}

void
MemoryManager::Dispose(JNIEnv* env, jobject parent)
{
  auto key = GetKey(env, parent);
  _Cache.erase(key);
}
