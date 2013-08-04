# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libfutz
LOCAL_CFLAGS    := -Werror -D ANDROID -D OPENGLES1

LOCAL_SRC_FILES += Futz.cpp \
      GameBase.cpp \
      TimeKeeper.cpp \
      platforms/SystemLayerBase.cpp \
      platforms/FutzAndroid.cpp \
      renderers/dummy/DummyRenderer.cpp \
      renderers/gles1/GLES1Renderer.cpp \
      camera/Camera.cpp \
      input/InputEventQueue.cpp \
      core/Node.cpp \
      core/Transform.cpp \
      scenegraph/SceneGraph.cpp \
      models/Model.cpp \
      models/Material.cpp \
      models/Triangle.cpp \
      models/dummy/DummyModel.cpp \
      models/wavefront/WavefrontModel.cpp \
      math/Matrix4.cpp math/Vector3.cpp math/Quaternion.cpp \
      3rdParty/stb_image.cpp

LOCAL_LDLIBS    := -llog -lGLESv1_CM -lm -landroid
include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := libfutzdemo
LOCAL_CFLAGS    := -Werror -D ANDROID -D OPENGLES1

LOCAL_SRC_FILES += demo/Android.cpp \
      demo/Demo.cpp \
      demo/Asteroids.cpp \
      demo/Ships.cpp \
  

LOCAL_SHARED_LIBRARIES := libfutz
LOCAL_LDLIBS    := -llog -lGLESv1_CM -lm -landroid
include $(BUILD_SHARED_LIBRARY)
