cd build
###
 # @Descripttion: 
 # @version: 
 # @Author: Hubery-Lee
 # @Date: 2021-08-06 18:02:51
 # @E-mail: hrbeulh@126.com
 # @LastEditors: Hubery-Lee
 # @LastEditTime: 2021-08-06 20:19:13
### 
rm -rf *
cd ../bin
rm -rf *
cd ../build
cmake ..
make -j4 && make install -j4
