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
  std::vector<T> data_;
  int m_;
  PComparator comp_;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m), comp_(c) {}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  // add item to the back
  data_.push_back(item);

  size_t idx = data_.size() - 1;
  while (idx > 0) {
    size_t parent = (idx - 1) / m_;

    // if correct ordering
    if (!comp_(data_[idx], data_[parent])) {
      break;
    }

    // if not, swap
    std::swap(data_[idx], data_[parent]);
    idx = parent;
  }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return data_.size();
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
    throw std::underflow_error("empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_.front();
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
    throw std::underflow_error("empty heap");
  }

  data_.front() = data_.back();
  data_.pop_back();

  size_t idx = 0;

  while (idx < data_.size()) {
    // assume self is best for now
    size_t best = idx;

    // find the "best" child
    for (int i=1; i<=m_; i++) {
      size_t child = m_ * idx + i;

      // check if child exists
      if (child >= data_.size()) {
        break;
      }

      // get "best" child
      if (comp_(data_[child], data_[best])) {
        best = child;
      }
    }

    // stop if heap property is satisfied
    // if curr node is the best
    if (best == idx) {
      break;
    }

    // swap best with node
    std::swap(data_[idx], data_[best]);
    idx = best;
  }
}

#endif