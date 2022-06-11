// Shadow Element helper definitions
template <typename T1>
ShadowElement<T1>::ShadowElement():
  element{ },
  next{nullptr}
{}

template <typename T1>
ShadowElement<T1>::ShadowElement(T1 element):
  element{element},
  next{nullptr}
{}

template <typename T1>
ShadowElement<T1>::ShadowElement(T1 element, ShadowElement<T1> *next): 
  element{element}, 
  next{next}
{}

// TODO: seems fishy
template <typename T1>
ShadowElement<T1>::~ShadowElement()
{
  ShadowElement *temp = this, *deletePt;
  while (temp->next != nullptr)
  {
    deletePt = temp;
    temp = temp->next;
    delete deletePt;
  }
}