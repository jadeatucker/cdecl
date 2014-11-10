# Test script for cdecl
CMD=./cdecl

function cdecl {
  echo "$1"
  printf "$1" | $CMD
  echo
}

echo "Running Make..."
make

echo
echo "Running examples..."
cdecl "char ch"
cdecl "int **n"
cdecl "char *str"
cdecl "int arr[10]"
cdecl "int arr[]"
cdecl "char* const *(*next)()"

echo "Done."
