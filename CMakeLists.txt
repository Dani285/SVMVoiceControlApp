cmake_minimum_required(VERSION 3.5)
# https://github.com/ptitpoulpe/cmake-swig-java-example/blob/master/CMakeLists.txt
project(svmtrain LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

set(JAVA_HOME "/usr/lib64/jvm/java-11-openjdk-11")
find_package(Java COMPONENTS Development)
find_package(JNI REQUIRED)
include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/dlib)

include(UseJava)

add_subdirectory(dlib)

add_executable(svmtrain main.cpp)

set(CMAKE_JNI_TARGET TRUE)

add_library( JDlib
  JDlib/site_selyerobotics_jdlib_JDlib.cpp
  JDlib/site_selyerobotics_jdlib_JDlib.h
  JDlib/site_selyerobotics_jdlib_JDlib_DecisionFunction.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_DecisionFunction.h
  JDlib/site_selyerobotics_jdlib_JDlib_LearnedFunction.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_LearnedFunction.h
  JDlib/site_selyerobotics_jdlib_JDlib_Matrix.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_Matrix.h
  JDlib/site_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_NormalizedProbabilisticFunction.h
  JDlib/site_selyerobotics_jdlib_JDlib_ProbabilisticDecisionFunction.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_ProbabilisticDecisionFunction.h
  JDlib/site_selyerobotics_jdlib_JDlib_RBF.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_RBF.h
  JDlib/site_selyerobotics_jdlib_JDlib_ReducedDecisionFunctionTrainer2.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_ReducedDecisionFunctionTrainer2.h
  JDlib/site_selyerobotics_jdlib_JDlib_SVMNuTrainer.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_SVMNuTrainer.h
  JDlib/site_selyerobotics_jdlib_JDlib_VectorM.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_VectorM.h
  JDlib/site_selyerobotics_jdlib_JDlib_VectorNormalizer.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_VectorNormalizer.h
  JDlib/site_selyerobotics_jdlib_JDlib_Vectord.cpp
  JDlib/site_selyerobotics_jdlib_JDlib_Vectord.h
  memorymanager.cpp
  memorymanager.hpp
  types.hpp

)

install(TARGETS svmtrain
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS JDlib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(svmtrain dlib::dlib)

target_link_libraries(JDlib dlib::dlib ${JAVA_JVM_LIBRARY})
