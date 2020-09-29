#ifndef AIOTHREAD_H
#define AIOTHREAD_H

#include <QThread>
#include <QObject>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/thread/thread_time.hpp>
#include <time.h>
#include <sys/time.h>

using namespace boost::interprocess;

typedef struct {
    int l_x;
    int l_y;
    int r_x;
    int r_y;
} eye_data_t;

Q_DECLARE_METATYPE(eye_data_t)

Q_DECLARE_METATYPE(timeval)

typedef allocator<eye_data_t, managed_shared_memory::segment_manager> alloc_eye_data_t;
typedef deque<eye_data_t, alloc_eye_data_t> eye_data_deque_t;
// typedef std::pair<eye_data_t, bool> eye_data_with_valid_t;

class AIOThread : public QThread
{
    Q_OBJECT
public:
    AIOThread();
    // eye_data_deque_t *getEyeDataDeque();
    // eye_data_t getLatest();
    // clock_t getUpdateTime();
signals:
    void dataUpdated(eye_data_t data, timeval);
    void dataLost();
protected:
    void run() override;
private:
    // Shared memory
    managed_shared_memory segment;
    const alloc_eye_data_t alloc_inst;
    // Stores eyes data
    eye_data_deque_t *pDeque;
    timeval *pUpdateTime;
    timeval lastUpdateTime;
    interprocess_mutex *pRWMutex;
};

#endif // AIOTHREAD_H
