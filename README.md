* HOW TO BUILD


** OSX
If you install openssl via homebrew, you need to set OPENSSL_ROOT_DIR variable manually like...

$ mkdir build
$ cd build
$ cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl ../
$ make