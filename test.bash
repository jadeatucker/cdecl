# Test script for cdecl
CMD=./cdecl

echo "Running Make..."
make

echo
echo "Running examples..."
printf "char ch" | $CMD
printf "char *str" | $CMD
printf "int arr[10]" | $CMD
printf "char* const *(*next)()" | $CMD

echo "Done."
