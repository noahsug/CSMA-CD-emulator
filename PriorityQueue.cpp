#include "PriorityQueue.h"

#include "Events.h"

PriorityQueue::~PriorityQueue() {
  List::iterator it;
  for (it = list_.begin(); it != list_.end(); ++it) {
    delete *it;
  }
}

void PriorityQueue::Insert(Event* obj) {
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

void PriorityQueue::Remove(unsigned long long id) {
  List::iterator it;
  for (it = list_.begin(); it != list_.end(); ++it) {
    if (id == (*it)->GetId()) {
      delete *it;
      list_.erase(it);
      return;
    }
  }
}

