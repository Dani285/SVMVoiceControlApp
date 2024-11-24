cmake_minimum_required(VERSION 3.5)
# https://github.com/ptitpoulpe/cmake-swig-java-example/blob/master/CMakeLists.txt
project(svmtrain LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Concurrent)
add_subdirectory("aquila")

# assume built-in pthreads on MacOS
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    set(CMAKE_BUILD_RPATH "/usr/local/lib")
ENDIF()


set(JAVA_HOME "/Users/dani2000/Library/Java/JavaVirtualMachines/openjdk-21.0.2/Contents/Home")
find_package(Java COMPONENTS Development)
find_package(JNI REQUIRED)
include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/dlib)
include_directories(${CMAKE_SOURCE_DIR}/aquila)
# set( CMAKE_CXX_FLAGS "-fPIC -static -Wall -D_JNI_IMPLEMENTATION_ -Wl,--add-stdcall-alias" CACHE  STRING "" FORCE )
# set( CMAKE_C_FLAGS "-fPIC -static -Wall -D_JNI_IMPLEMENTATION_ -Wl,--add-stdcall-alias" CACHE  STRING "" FORCE )

include(UseJava)

find_package(DLib_LIBRARY NAMES dlib REQUIRED PATHS "/Users/dani2000/Desktop/Bachelor's thesis/build-dlib-Qt_6_6_2_for_macOS-Debug/install/lib/cmake/dlib")

add_executable(svmtrain
    main.cpp
)

set(CMAKE_JNI_TARGET TRUE)

add_library( JDlib SHARED
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

target_link_libraries(svmtrain PRIVATE dlib::dlib Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent Aquila)

target_link_libraries(JDlib dlib::dlib ${JAVA_JVM_LIBRARY})

qt_finalize_executable(svmtrain)
