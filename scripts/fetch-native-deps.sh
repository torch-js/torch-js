#/bin/bash

# This script attempts to install the following dependencies as prebuilt libs
#   - libtorch (C++ library version of PyTorch)
#   - libmklml (https://github.com/intel/mkl-dnn/)
# Some platform detection is attempted, but very hacky!

EXTERN_DIR=extern
LIBTORCH_DIR=$EXTERN_DIR/libtorch/
MKLML_DIR=$EXTERN_DIR/mklml/

echo "Fetching libtorch and dependencies..."

# Detect OS via https://stackoverflow.com/a/8597411
# URLs are from https://pytorch.org/get-started/locally/
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  MKLML_URL=https://github.com/intel/mkl-dnn/releases/download/v0.18/mklml_lnx_2019.0.3.20190220.tgz
  # Detect whether CUDA is installed
  if [[ -z $CUDA_ROOT ]] && [[ -d "$CUDA_ROOT" ]]; then
    if [[ "$CUDA_VERSION" == "10"* ]]; then
      LIBTORCH_URL=https://download.pytorch.org/libtorch/nightly/cu100/libtorch-shared-with-deps-latest.zip
    elif [[ "$CUDA_VERSION" == "9"* ]]; then
      LIBTORCH_URL=https://download.pytorch.org/libtorch/cu90/libtorch-shared-with-deps-latest.zip
    fi
  else
    LIBTORCH_URL=https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-latest.zip
  fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
  # Mac OSX doesn't support CUDA anymore
  LIBTORCH_URL=https://download.pytorch.org/libtorch/cpu/libtorch-macos-latest.zip
  MKLML_URL=https://github.com/intel/mkl-dnn/releases/download/v0.18/mklml_mac_2019.0.3.20190220.tgz
elif [[ "$OSTYPE" == "cygwin" ]]; then
  # TODO
  # POSIX compatibility layer and Linux environment emulation for Windows
  MKLML_URL=https://github.com/intel/mkl-dnn/releases/download/v0.18/mklml_win_2019.0.3.20190220.tgz
  LIBTORCH_URL=""
elif [[ "$OSTYPE" == "msys" ]]; then
  # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
  LIBTORCH_URL=""
elif [[ "$OSTYPE" == "win32" ]]; then
  # I'm not sure this can happen.
  echo "win32 currently unsupported"
elif [[ "$OSTYPE" == "freebsd"* ]]; then
  echo "FreeBSD currently unsupported"
else
  # Unknown.
  echo "Unknown platform. Need to build LibTorch from source."
fi

# Install libtorch
if [ ! -d "${LIBTORCH_DIR}/lib" ]; then
  echo "Downloading libtorch from ${LIBTORCH_URL} to ${LIBTORCH_DIR}..."
  mkdir -p ${LIBTORCH_DIR}

  curl -L -o libtorch.zip ${LIBTORCH_URL}
  echo "Extracting libtorch to ${LIBTORCH_DIR}..."
  unzip -q libtorch.zip -d ${EXTERN_DIR}
  echo "Removing zip file."
  rm -f libtorch.zip
else
  echo "libtorch already installed in ${LIBTORCH_DIR}"
fi

# Install mklml
if [ ! -d "${MKLML_DIR}/lib" ]; then
  echo "Downloading MKLML from ${MKLML_URL} to ${MKLML_DIR}..."
  mkdir -p ${MKLML_DIR}

  curl -L -o mklml.tgz ${MKLML_URL}
  echo "Extracting MKLML to ${MKLML_DIR}..."
  tar -zxvf mklml.tgz --strip-components=1 -C ${MKLML_DIR}
  echo "Removing zip file."
  #rm -f mklml.tgz
else
  echo "MKLML already installed in ${MKLML_DIR}"
fi
