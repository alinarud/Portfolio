#!/bin/bash
PPP=$(pwd)
VERSION=1.4.11

echo "install libs to /usr/lib"

echo "Installing $PPP/libCommLibX.so.$VERSION"
rm /usr/lib/libCommLibX.*
cp -rp $PPP/libCommLibX.so.$VERSION /usr/lib/
ln -s -f /usr/lib/libCommLibX.so.$VERSION /usr/lib/libCommLibX.so

echo "Installing $PPP/libECRLibX.so.$VERSION"
rm /usr/lib/libECRLibX.*
cp -rp $PPP/libECRLibX.so.$VERSION /usr/lib/
ln -s -f /usr/lib/libECRLibX.so.$VERSION /usr/lib/libECRLibX.so

echo "Installing $PPP/libBPOSLib.so.$VERSION"
rm /usr/lib/libBPOSLib.*
cp -rp $PPP/libBPOSLib.so.$VERSION /usr/lib/
ln -s -f /usr/lib/libBPOSLib.so.$VERSION /usr/lib/libBPOSLib.so

