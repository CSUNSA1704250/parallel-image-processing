# Computación Paralela y Distribuída

Alumno: Jerson Zúñiga Coayla

## Requirements
- [CImg, C++ template image processing toolkit](https://www.cimg.eu/index.html).
- [Python packages](requirements.txt).

## Compile
### Linux
```sh
g++ -std=c++17 -o parallel.out src/parallel.cpp -O2 -lm -lpthread -lX11
```
### MacOS
```sh
clang++ -std=c++17 -o parallel.out src/parallel.cpp -O2 -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lpthread -lX11
```

## Run
```sh
./parallel.out <input_image> <color> <num_threads>
```
### Speedup
The [speedup.sh](speedup.sh) script benchmarks [parallel.cpp](src/parallel.cpp) on multiple cores. It outputs a result image of execution time by number of threads.
1. Configuration of `speedup.sh`: 
```sh
input_image=<input_image>
color=<color> # Available colors are RED, GREEN and BLUE
```

2. Running
```sh
./speedup.sh
```