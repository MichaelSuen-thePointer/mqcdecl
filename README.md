# mqcdecl
A "clean room" and "naive" implementation of cdecl.org

##What is supported
legal variable declaraion

e.g.
```C
double (*(*(*fp1)())[10])()
```
legal type name

e.g.
```C
char**
```

pointers, arrays and functions

the following type names are supported
```C
int
short
long
double
float
char
void
```

##What is not supported
type name with space is not supported, such as 'long long int'

storage specifiers are not supported

const, volatile and other qualifiers are not supported
