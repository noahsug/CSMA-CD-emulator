#include <list>

template<class T>
class PriorityQueue {
 public:
  PriorityQueue() {}

  void Insert(const T& obj);
  T Remove();

  private:
   typedef std::list<T> List;
   List list_;
};

template <class T>
void PriorityQueue<T>::Insert(const T& obj) {
  typename List::iterator it;
  for (it = list_.begin(); it != list_.end(); ++it) {
    if (obj < *it) {
      list_.insert(it, obj);
      return;
    }
  }
  list_.push_back(obj);
}

template <class T>
T PriorityQueue<T>::Remove() {
  T obj = list_.front();
  list_.pop_front();
  return obj;
}

