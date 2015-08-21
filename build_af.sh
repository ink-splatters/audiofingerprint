rm -rf build
mkdir build
cp settings_af.json build/
cp license.lic build/
cd build
cmake ../audiofingerprint -DCMAKE_INSTALL_PREFIX=install
make -j4 && make install
