###
 # @Descripttion: 
 # @version: 
 # @Author: Hubery-Lee
 # @Date: 2021-05-31 21:18:09
 # @E-mail: hrbeulh@126.com
 # @LastEditors: Hubery-Lee
 # @LastEditTime: 2021-08-06 20:17:38
### 

# clear
rm -rf ./build/*

rm -rf ./bin/*

echo "clear build bin"

# install gui
# cd code_gui/gui
# . installGui.sh

# rebuild

cd build

cmake ../
echo "========start make========="
make -j4
echo "========start make install========"
make install -j4
echo " "
echo " "

cd ../bin