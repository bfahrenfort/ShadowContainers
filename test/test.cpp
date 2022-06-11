#include "shadows.hpp"
#include <iostream>

using std::cout;
using std::endl;
int main()
{
  cout << "Creating sequential base collection" << endl;
  auto arr = ShadowArray<int, 10>();
  for (int i = 0; i < 10; ++i)
  {
    arr[i] = i;
  }

  cout << "Iterating over base collection" << endl;
  for (int i = 0; i < 10; ++i)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  cout << "Creating shadow" << endl;
  auto first_shdw = arr.shadow();

  cout << "Iterating first (unmodified) shadow" << endl;
  for (int i = 0; i < 10; ++i)
  {
    cout << arr(first_shdw, i) << " ";
  }
  cout << endl;

  cout << "Modifying first shadow" << endl;
  arr.set(first_shdw, 1, 10);

  cout << "Accessing modified element" << endl;
  cout << arr(first_shdw, 1) << endl;

  cout << "Iterating first (modified) shadow" << endl;
  for (int i = 0; i < 10; ++i)
  {
    cout << arr(first_shdw, i) << " ";
  }
  cout << endl;

  

  std::cout << "Ha" << std::endl;
  return 0;
}