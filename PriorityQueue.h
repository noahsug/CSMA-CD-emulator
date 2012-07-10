#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <list>

class Event;

class PriorityQueue {
 public:
  PriorityQueue() {}

  void Insert(Event* obj);
  Event* Remove();
  void Remove(Event* obj);

  private:
   typedef std::list<Event*> List;
   List list_;
};

#endif

