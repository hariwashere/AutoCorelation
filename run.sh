echo "Serial Implamentation"
time ./main.o 64 1 0

echo "CUDA Implementation"
time ./main.o 64 0 1
