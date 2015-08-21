rm -rf build
mkdir build
cd build
cmake ../audiofingerprint -DCMAKE_INSTALL_PREFIX=install
make -j4 && make install
cp ../settings_af.json  install/
cp ../license.lic install/
