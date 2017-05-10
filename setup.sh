#!/bin/bash
mkdir -p ${PWD}/src/third_party
here=${PWD}
cd ${here}/src/third_party
svn co https://projects.coin-or.org/svn/Clp/stable/1.16 coin-Clp
cd coin-Clp
./configure -C
make
make test
make install
