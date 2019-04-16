#!/bin/bash

# Version for distribution?
#mkdir -p dist/native/
#cp build/Release/torch-js.node dist/native
#cp extern/libtorch/lib dist/native

EXTERN_DIR=extern
LIBTORCH_DIR=$EXTERN_DIR/libtorch/
MKLML_DIR=$EXTERN_DIR/mklml/
BUILT_PRODUCTS_DIR=build/Release

echo "Copying prebuilt libraries to ${BUILT_PRODUCTS_DIR}"
cp -a $LIBTORCH_DIR/lib/. $BUILT_PRODUCTS_DIR
cp -a $MKLML_DIR/lib/. $BUILT_PRODUCTS_DIR