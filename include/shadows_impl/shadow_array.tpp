// Shadow Array definitions

template <typename T, std::size_t N>
ShadowArray<T, N>::ShadowArray()
{ 
  items = std::array<ShadowElement<T>, N>{ };
}

template <typename T, std::size_t N>
ShadowArray<T, N>::~ShadowArray()
{

}

template <typename T, std::size_t N>
r_shadow ShadowArray<T, N>::shadow()
{
  int shdw_id = shadows.size();
  ShadowStatic<N> shdw(shdw_id);

  shadows.emplace_back(shdw);

  return shadows.back().shadow_id;
}

template <typename T, std::size_t N>
int ShadowArray<T, N>::shadow_free(r_shadow shadow)
{

}

template <typename T, std::size_t N>
inline T& ShadowArray<T, N>::operator[](int i)
{ return items[i].element; }

template <typename T, std::size_t N>
T& ShadowArray<T, N>::operator()(r_shadow p, int i)
{
  if (p == 0 || !shadows[p].modified.test(i)) // Base collection
    return items[i].element;
  else // differs from base
  {
    int pos = 1; // First shadow
    ShadowElement<T> *temp = items[i].next; // First shadow

    // Traverse to the shadow element
    while (pos < p && temp != nullptr)
    {
      temp = temp->next;
      ++pos;
    }

    return temp->element;
  }
}

template <typename T, std::size_t N>
void ShadowArray<T, N>::set(r_shadow p, int i, T element)
{
  if (i >= N) // Out of range
    throw std::range_error("Index out of ShadowArray range");
  else if (shadows[p].shadow_id != p) // Not a valid shadow
    throw InvalidShadowException();

  
  int pos = 1; // First shadow
  ShadowElement<T> *prev = &items[i]; // Base item
  ShadowElement<T> *temp = prev->next; // First shadow item

  // Traverse to the shadow element
  if (shadows[p].modified.test(i)) // Previously modified element
  {
    // Update the existing element
    while (pos < p)
    {
      temp = temp->next;
      ++pos;
    }

    temp->element = element;
  }
  else
  {
    while (pos <= p) // Traverse shadows until we find shadow p's element
    {
      if (temp == nullptr)
      {
        *temp = ShadowElement<T>(); // Don't care about the value, it's still marked unmodified in the shadow we're going through
        prev->next = temp;
      }

      prev = temp;
      temp = temp->next;
    }

    prev->element = element;
    shadows[p].modified.set(i); // Mark this shadow element as modified
  }
  
}