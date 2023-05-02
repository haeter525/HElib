#！/usr/bin/bash
rm -rf ~/helib_install
rm -rf build
mkdir build

cd build && (
    cmake -DENABLE_TEST=ON -DPACKAGE_BUILD=ON -DCMAKE_INSTALL_PREFIX=/home/haeter/helib_install ..
    make -j16
)