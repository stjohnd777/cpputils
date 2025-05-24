#pragma once

#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>


namespace dsj
{
    struct TimerHandle
    {

        enum Status {
            INIT,
            RUNNING,
            SLEEPING,
            REQUEST_CANCEL,
            IS_CANCELED,
            COMPLETED,
            ERROR_STATE
            
        } ;
        
        long long executedCount = 0;
        long long executeLimit = 0;
        
        std::function<void()> f;
        int delay;
        Status state = INIT;
        std::thread* theThread;

        void join(){
            theThread->join();
        }
    };


    template < typename IN, typename OUT>
    struct TimerHandle2
    {
 
        enum Status {
            INIT,
            RUNNING,
            SLEEPING,
            REQUEST_CANCEL,
            IS_CANCELED,
            COMPLETED,
            ERROR_STATE
            
        } ;
        
        long long executedCount = 0;
        long long executeLimit = 0;
        
        
        std::function<OUT(IN)> f;
        int delay;
        Status state = INIT;
        std::thread* theThread;
        
        void join(){
            theThread->join();
        }
        
        void clearInbox(){
            mtxIN.lock();
            inBox.clear();
            mtxIN.unlock();
        }
        
        void clearOut(){
            mtxOUT.lock();
            outBox.clear();
            mtxOUT.unlock();
        }
        
        IN getIN() {
            return inBox[0];
        }
        
        OUT getOUT() {
            return outBox[0];
        }
        
        void pushOut(OUT out){
            mtxOUT.lock();
            outBox.push_back(out);
            mtxOUT.unlock();
        }
        
        void pushIn(IN in){
            mtxIN.lock();
            inBox.push_back(in);
            mtxIN.unlock();
        }
        
    private:
        
        std::mutex mtxIN;
        std::vector<IN> inBox;
        std::mutex mtxOUT;
        std::vector<OUT> outBox;
        
    };

    std::shared_ptr<TimerHandle>  SetTimeout(std::function<void()> f, int delay, bool isDetached = false);
    std::shared_ptr<TimerHandle>  SetInterval(std::function<void()> f, int delay, bool isDetached = false);


    template < typename IN, typename OUT>
    std::shared_ptr<TimerHandle2<IN,OUT>>
    SetInterval2(std::function<OUT(IN)> f, int delay, bool isDetached = false);

}
