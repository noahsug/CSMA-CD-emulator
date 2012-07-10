#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <list>

class PriorityQueue {
 public:
  PriorityQueue() {}

  void Insert(const Event*& obj);
  Event* Remove();
  void Remove(const Event*& obj);

  private:
   typedef std::list<Event*> List;
   List list_;
};

void PriorityQueue::Insert(const Event*& obj) {
  List::iterator it;
  for (it = list_.begin(); it != list_.end(); ++it) {
    if (*obj < **it) {
      list_.insert(it, obj);
      return;
    }
  }
  list_.push_back(obj);
}

Event* PriorityQueue::Remove() {
  Event* obj = list_.front();

  if (list_.size() > 0) {
    list_.pop_front();
  }

  return obj;
}

void PriorityQueue::Remove(const Event*& obj) {
  List::iterator it;
  for (it = list_.begin(); it != list_.end(); ++it) {
    if (obj == *it) {
      list_.erase(it);
      return;
    }
  }
}

#endif

