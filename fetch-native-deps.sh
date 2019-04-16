#/bin/bash

EXTERN_DIR=extern
LIBTORCH_DIR=$EXTERN_DIR/libtorch/

# Detect OS via https://stackoverflow.com/a/8597411
# URLs are from https://pytorch.org/get-started/locally/
if [[ "$OSTYPE" == "linux-gnu" ]]; then
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
elif [[ "$OSTYPE" == "cygwin" ]]; then
  # TODO
  # POSIX compatibility layer and Linux environment emulation for Windows
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

if [ ! -d "${LIBTORCH_DIR}" ]; then
  echo "Downloading libtorch to ${LIBTORCH_DIR}..."
  mkdir -p ${LIBTORCH_DIR}

  curl -o libtorch.zip ${LIBTORCH_URL}
  echo "Extracting libtorch to ${LIBTORCH_DIR}..."
  unzip -q libtorch.zip -d ${EXTERN_DIR}
  rm -f libtorch.zip
else
  echo "libtorch already installed in ${LIBTORCH_DIR}"
fi