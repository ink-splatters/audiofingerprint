rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=install
make -j4 && make install
cp ../settings_af.json  install/
cp ../license.lic install/
cp ../teen_spirit_14s.wav install/
cd install
./AudioFingerPrint --settings=settings_af.json --input=teen_spirit_14s.wav --output=output.json
cd ../..
