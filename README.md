# Computación Paralela y Distribuída

Alumno: Jerson Zúñiga Coayla

## Requirements
- [CImg, C++ template image processing toolkit](https://www.cimg.eu/index.html).
- [Python packages](requirements.txt).

## Compile
---
**NOTE**

You must also have installed [ImageMagick](https://imagemagick.org/script/download.php) because `CImg` needs to recognize picture formats such as `jpg`, `png`, among others.

---

### Linux
```sh
g++ -o parallel.out parallel.cpp -O2 -lm -lpthread -lX11
```
### MacOS
```sh
clang++ -std=c++17 -o parallel.out src/parallel.cpp -O2 -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lpthread -lX11
```

## Run
```sh
./parallel.out <input_image> <color> <num_threads>
```
