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
cdecl "int (*fp) ()"
cdecl "int (*daytab)[13]"
cdecl "void (*f[10]) (int, int)"
cdecl "char (*(*x[3])())[5]"
cdecl "int *(*(*arr[5])()) ()"

echo "Done."
