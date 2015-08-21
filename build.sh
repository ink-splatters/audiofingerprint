rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=install
make -j4 && make install
cp ../settings_af.json  install/
cp ../license.lic install/
cd install
./AudioFingerPrint --settings=settings_af.json --input=blah --output=blah
cd ../..
