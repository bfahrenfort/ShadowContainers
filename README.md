# Shadow Containers
This project is a work in progress.

An interesting collection of dynamic data structures for memory-efficient computing on a set of data.

A Shadow container houses one set of data and an arbitrary number of 'shadows': effectively a modifiable version of the base data without copying it, and while retaining the original for later use.

Here's a diagram:
![A simple Shadow container.](https://i.imgur.com/EnbeJtv.png)
You can create a Shadow container and assign values to its elements, then when you want to modify values for a task, allocate a shadow and perform modifications.

## Use cases
* A set of data too large to trivially deep copy needs to be altered in parallel without interference from other threads
* A set of data too large to trivially deep copy needs to be re-used for several consecutive tasks, each using the original data without modification

## Complexity
Accessing a random element of the underlying base data is O(1).

Iterating over the base data is O(N).

Iterating over a shadow is O(N, K, J), depending on the size of the base (N), the number of the shadow (K), and the number of modifications to the shadow from the base (J).

## How to build/use
This is a header-only library. Copy `shadows.hpp` and `shadows_impl/` from the `include` directory of this repository to where you include files in your project.

To run tests on the library, do:
```
mkdir build
cd build
cmake ..
cmake --build .
```
and then run ShadowTests.exe.

To use, add `auto collection = Shadow{Array/Vector/etc}<varies>;`, then get shadows of the base with `auto shdw = collection.shadow();` and shadows of another shadow with `auto shdw1 = collection.shadow(shdw);`. Access/set base elements with `collection[index]`, and shadow elements with `collection(shdw, index)` (note the parenthesis instead of brackets). Set shadow elements with `collection.set(shdw, index, value)`.