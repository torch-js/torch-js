#/bin/bash

EXTERN_DIR=extern

LIBTORCH_DIR=$EXTERN_DIR/libtorch/

# macOS url. TODO: detect platform and install correct prebuilt lib
TORCH_URL=https://download.pytorch.org/libtorch/cpu/libtorch-macos-latest.zip
#TORCH_URL=https://download.pytorch.org/libtorch/nightly/cu100/libtorch-shared-with-deps-latest.zip


if [ ! -d "${LIBTORCH_DIR}" ]; then
  echo "Downloading libtorch to ${LIBTORCH_DIR}..."
  mkdir -p ${LIBTORCH_DIR}

  curl -o libtorch.zip ${TORCH_URL}
  unzip libtorch.zip -d ${EXTERN_DIR}
  rm -f libtorch.zip
else
  echo "libtorch already installed in ${LIBTORCH_DIR}"
fi