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

find_package(SWIG COMPONENTS java)
include(UseJava)
include (UseSWIG)

add_subdirectory("/home/ujoimro/doc/university/sje/2022-11-21_kalocsanyi_daniel/dlib" "dlib_build")

add_executable(svmtrain main.cpp)

set( CMAKE_SWIG_FLAGS -package site.selyerobotics.jdlib )
set( CMAKE_SWIG_OUTDIR "site.selyerobotics.jdlib" )
#SET_SOURCE_FILES_PROPERTIES(Train.i PROPERTIES CPLUSPLUS 1)
#SET_SOURCE_FILES_PROPERTIES(Train.i PROPERTIES SWIG_FLAGS "-includeall")

set(CMAKE_JNI_TARGET TRUE)
#add_jar(jsvm_jar ${EXAMPLE_JAVA_FILES}
#       	VERSION 1.2.0
#	ENTRY_POINT example)
#install_jar(example_swig_jar ${LIB_INSTALL_DIR}/example)
#install_jni_symlink(example_swig_jar .)

#swig_add_module(example_swig java example.i "example.hpp" "example.cpp")
#swig_link_libraries(example_swig Example)

#set(JAVA_BUNDLE "${CMAKE_HOME_DIRECTORY}/java_bundle.sh")
#set(JAVA_BUNDLE_SO_FILES "${CMAKE_HOME_DIRECTORY}/libexample_swig.so")
#set(MANIFEST_FILE "${CMAKE_HOME_DIRECTORY}/MANIFEST")
#ADD_CUSTOM_COMMAND(TARGET example_swig
#                   POST_BUILD
#		   DEPEND example_swig_jar
#		   COMMAND ${JAVA_BUNDLE} "example_swig_jar.jar" "${Java_JAVA_EXECUTABLE}" "example.NativeLib" "${CMAKE_STRIP}" -so ${JAVA_BUNDLE_SO_FILES} -txt ${JAVA_BUNDLE_TXT_FILES}
#                   COMMAND ${JAVA_ARCHIVE} -uvf "example_swig_jar.jar" "NATIVE"
#		   COMMAND ${CMAKE_COMMAND} -E echo "Class-Path: ." > ${MANIFEST_FILE}
#                   COMMAND ${JAVA_ARCHIVE} -uvmf "MANIFEST" "example_swig_jar.jar"
#                   COMMAND ${CMAKE_COMMAND} -E remove ${MANIFEST_FILE}
#		   )

#ADD_CUSTOM_COMMAND(TARGET example_swig
#                   POST_BUILD
#	           COMMAND ${JAVA_COMPILE} "example_test.java")

#enable_testing()
#ADD_TEST(example-test "java" "example_test")

set_property(SOURCE Train.i PROPERTY CPLUSPLUS ON)
swig_add_library( SwigDlib LANGUAGE java SOURCES Train.i train.hpp train.cpp )

install(TARGETS svmtrain
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS SwigDlib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(svmtrain dlib::dlib)

target_link_libraries(SwigDlib dlib::dlib ${JAVA_JVM_LIBRARY})
