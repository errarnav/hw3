#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> items_;
  int m_;
  PComparator comp_;

  void heapifyUp(size_t index);
  void heapifyDown(size_t index);
  size_t parent(size_t index) const;
  size_t child(size_t index, int k) const;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_(m), comp_(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return items_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return items_.size();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::parent(size_t index) const
{
  return (index - 1) / m_;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::child(size_t index, int k) const
{
  return m_ * index + k;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyUp(size_t index)
{
  if (index == 0) return;
  
  size_t p = parent(index);
  if (comp_(items_[index], items_[p])) {
    std::swap(items_[index], items_[p]);
    heapifyUp(p);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyDown(size_t index)
{
  if (child(index, 1) >= items_.size()) {
    return;
  }
  
  size_t bestChild = child(index, 1);
  for (int k = 2; k <= m_; k++) {
    size_t c = child(index, k);
    if (c < items_.size() && comp_(items_[c], items_[bestChild])) {
      bestChild = c;
    }
  }
  
  if (comp_(items_[bestChild], items_[index])) {
    std::swap(items_[bestChild], items_[index]);
    heapifyDown(bestChild);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  items_.push_back(item);
  heapifyUp(items_.size() - 1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }

  items_[0] = items_.back();
  items_.pop_back();
  if (!items_.empty()) {
    heapifyDown(0);
  }
}

#endif