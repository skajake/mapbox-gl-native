#!/usr/bin/env bash

VERSION=$( git tag | grep ^osx | sed 's/^osx-//' | sort -r | grep -v '\-rc.' | grep -v '\-pre.' | sed -n '1p' | sed 's/^v//' )
plutil \
    -replace CFBundleShortVersionString -string ${VERSION:=0.0.1} \
    $TARGET_BUILD_DIR/Mapbox.framework/Versions/Current/Resources/Info.plist
plutil \
    -replace CFBundleVersion -string ${VERSION} \
    $TARGET_BUILD_DIR/Mapbox.framework/Versions/Current/Resources/Info.plist
