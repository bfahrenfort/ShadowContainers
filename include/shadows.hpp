// shadows.hpp
// Definitions for the shadow container classes.

#include <vector>
#include <array>
#include <bitset>
#include <exception>
#include <stdexcept>

struct InvalidShadowException : public std::exception {
   const char* what () const 
    throw () 
    {
        return "The shadow reference ID the program attempted to reference is invalid";
    }
};
typedef const int& r_shadow;

// An element of a shadow and the next shadow's element at its position
template <typename T1>
struct ShadowElement
{
  ShadowElement();
  ShadowElement(T1 element);
  ShadowElement(T1 element, ShadowElement<T1> *next);
  ~ShadowElement();

  T1 element;
  ShadowElement<T1> *next;
};

#include "shadows_impl/shadow_element.tpp"

template <std::size_t N1>
struct ShadowStatic
{
  ShadowStatic(int id);

  int shadow_id;
  std::bitset<N1> modified; // Whether each of the items of the shadow differ from the base collection
};

#include "shadows_impl/shadow_static.tpp"

template <typename T, std::size_t N>
class ShadowArray
{
  public:
    ShadowArray();
    // NOTE: This container is for large data. Don't try to deep copy it. I left out a copy constructor for a reason.
    ~ShadowArray();
    
    // Allocate a new shadow
    r_shadow shadow(); // From the base collection
    r_shadow shadow(r_shadow base); // From another shadow

    // Delete a shadow
    int shadow_free(r_shadow shadow);
    
    inline T& operator[](int i); // Access or set an element in the base collection
    T& operator()(r_shadow p, int i); // Access an element in a shadow at a position
    void set(r_shadow p, int i, T element); // Set the element in a shadow at a position

    // Iteration
    // typedef ShadowElement<T>* iterator;
    // typedef const ShadowElement<T>* const_iterator;
    // iterator begin()
    // { return &items[0]; }
    // const_iterator begin() const
    // { return &items[0]; }
    // iterator end()
    // { return &items[N]; }
    // const_iterator end() const
    // { return &items[N]; }

  private:
    std::array<ShadowElement<typename T>, N> items; // Array of linked lists. Head nodes are the base collection and subsequent nodes correspond to elements in shadows
    std::vector<ShadowStatic<N>> shadows; // Contains the modification data and reference id for each shadow
};

#include "shadows_impl/shadow_array.tpp"