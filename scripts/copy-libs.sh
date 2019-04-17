#!/bin/bash

# TODO: Only copy necessary files for distribution

EXTERN_DIR=extern
LIBTORCH_DIR=$EXTERN_DIR/libtorch/
MKLML_DIR=$EXTERN_DIR/mklml/
BUILT_PRODUCTS_DIR=build/Release

echo "Copying prebuilt libraries to ${BUILT_PRODUCTS_DIR}"
cp -a $LIBTORCH_DIR/lib/. $BUILT_PRODUCTS_DIR
cp -a $MKLML_DIR/lib/. $BUILT_PRODUCTS_DIR