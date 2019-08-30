FROM python:3.7
MAINTAINER David Lindgren "guslindaaq@student.gu.se"

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        cmake \
        git \
        wget \
        unzip \
        yasm \
        pkg-config \
        libswscale-dev \
        libtbb2 \
        libtbb-dev \
        libjpeg-dev \
        libpng-dev \
        libtiff-dev \
        libavformat-dev \
        libpq-dev \
        g++ \
        make \
        ca-certificates \
#        libgtest-dev \
        software-properties-common \
    && rm -rf /var/lib/apt/lists/*

#Installing hayai #Can not be found at the moment.
#RUN apt-add-repository ppa:bruun/hayai \
#    && apt-get update \
#    && apt-get install libhayai-dev

RUN pip install numpy

WORKDIR /
#Building Opencv
# ENV OPENCV_VERSION="4.1.0" #Originial version
ENV OPENCV_VERSION="3.4.6"
RUN wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip \
&& unzip ${OPENCV_VERSION}.zip \
&& mkdir /opencv-${OPENCV_VERSION}/cmake_binary \
&& cd /opencv-${OPENCV_VERSION}/cmake_binary \
&& cmake -DBUILD_TIFF=ON \
  -DBUILD_opencv_java=OFF \
  -DWITH_CUDA=OFF \
  -DWITH_OPENGL=ON \
  -DWITH_OPENCL=ON \
  -DWITH_IPP=ON \
  -DWITH_TBB=ON \
  -DWITH_EIGEN=ON \
  -DWITH_V4L=ON \
  -DBUILD_TESTS=OFF \
  -DBUILD_PERF_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=RELEASE \
  -DCMAKE_INSTALL_PREFIX=$(python3.7 -c "import sys; print(sys.prefix)") \
  -DPYTHON_EXECUTABLE=$(which python3.7) \
  -DPYTHON_INCLUDE_DIR=$(python3.7 -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") \
  -DPYTHON_PACKAGES_PATH=$(python3.7 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())") \
  .. \
&& make install \
&& rm /${OPENCV_VERSION}.zip \
&& rm -r /opencv-${OPENCV_VERSION}
RUN ln -s \
  /usr/local/python/cv2/python-3.7/cv2.cpython-37m-x86_64-linux-gnu.so \
  /usr/local/lib/python3.7/site-packages/cv2.so

#Here is the stuff added in by David.  
#Building googletest

#RUN cd /usr/src/googletest && \
#    cmake . && \
#    cmake --build . --target install

RUN cd /usr/local/lib && \
    ls && \
    ls
#Building the project
ADD . ../~/git/group_09 
RUN cd ../~/git/group_09 && \
      cmake . && \
      echo chach &&\
    	make && \ 
      ./runTests

