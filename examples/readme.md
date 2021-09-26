## Compile
### Linux
```sh
g++ -o example01.out example01.cpp -O2 -lm -lpthread -lX11
```
### MacOS
Get a version of the X-Org X Window System by installing [XQuartz](https://www.xquartz.org/).
```sh
g++ -o example01.out example01.cpp -O2 -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lpthread -lX11
```

## Run
It is recommended to install [ImageMagick](https://imagemagick.org/script/download.php) because `CImg` needs to recognize picture formats such as `jpg`, `png`, among others.
```sh
./example01.out
```
