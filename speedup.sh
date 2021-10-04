#!/bin/bash

input_image="data/pexels-jess-loiterton-4783851.jpg"
color="RED"
num_threads=2

results="speedup.csv"
iterations=10

echo "num_threads,time_ms" > $results
for ((i = 1 ; i <= iterations ; i++)); do
  ./parallel.out $input_image $color $num_threads >> $results
  num_threads=$((num_threads*2))
done
