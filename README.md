# BitOp Library

This is a simple library for bit operations. Currently imlpemented `is_power_of_two`, `get_endianness` and `xor_swap` functions.

## How to Use the Library

### Option 1: Copy Header File

If you prefer a minimal setup:

1. Copy the `bit_op.hpp` file into your project's source directory.
2. Include it in your source code:

`#include "bit_op.hpp"`

You're ready to use the library.

### Option 2: Add as a Subdirectory (CMake Integration)

For a more modular and maintainable approach:

1. Clone this project into your project directory, for example:

```bash 
git clone https://github.com/Hayk10002/bit_op.git external/bit_op
```

2. In your project's `CMakeLists.txt`, add the following lines:

```cmake
add_subdirectory(external/bit_op)  
target_link_libraries(your_project PRIVATE bit_op)
```

3. Then, include the header in your source files using:

```cpp
#include <bit_op.hpp>
```
