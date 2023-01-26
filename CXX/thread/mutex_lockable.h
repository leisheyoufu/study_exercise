#include <mutex>
#include "thread_annotations.h"

using namespace std;

class LOCKABLE Mutex {
public:
		Mutex() = default;
		~Mutex() = default;

		Mutex(const Mutex&) = delete;
		Mutex& operator=(const Mutex&) = delete;

   	void Lock() EXCLUSIVE_LOCK_FUNCTION(){
	 		mu_.lock();
	 	}

   	void Unlock() UNLOCK_FUNCTION(){
	 		mu_.unlock();
	 	}

private:
	 	mutex mu_;
};