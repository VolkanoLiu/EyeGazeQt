#include "aiothread.h"
#include <iostream>
#include <QMetaType>

AIOThread::AIOThread()
    : segment(open_only, "EyeGaze"),
      alloc_inst(segment.get_segment_manager())
{
    pDeque = segment.find<eye_data_deque_t>("eye_data").first;
    pUpdateTime = segment.find<timeval>("update time").first;
    pRWMutex = segment.find<interprocess_mutex>("rw mutex").first;
    timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);
    lastUpdateTime = tv;
    qRegisterMetaType<eye_data_t>("EyeData");
    qRegisterMetaType<timeval>("time_t");
}

bool compareTimeLater(timeval new_time, timeval old_time) {
    if(new_time.tv_sec > old_time.tv_sec) return true;
    if(new_time.tv_sec == old_time.tv_sec && new_time.tv_usec > old_time.tv_usec) return true;
    return false;
}

void AIOThread::run()
{
    while (1) {
        while(!pRWMutex->timed_lock(boost::get_system_time() + boost::posix_time::seconds(1))){
            std::cout << "resource still unreachable after 1 seconds, retrying..." << std::endl;
            emit dataLost();
        }
        if(pDeque->empty()) {
            std::cout << "data deque is emply" << std::endl;
            emit dataLost();
            continue;
        }
        if(compareTimeLater(*pUpdateTime, lastUpdateTime)) {
            lastUpdateTime = *pUpdateTime;
            eye_data_t data = pDeque->back();
            data.l_y = 1440 - data.l_y;
            data.r_y = 1440 - data.r_y;
            emit dataUpdated(data, lastUpdateTime);
        }
        pRWMutex->unlock();
        msleep(20);
    }
}
