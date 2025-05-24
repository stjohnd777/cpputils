//
//  easy_timer.cpp
//  EasyCppUtils
//
//  Created by Daniel St. John on 4/13/21.
//

//#include <stdio.h>

#include  <memory>
#include "../header/easy_timer.h"

namespace dsj
{

    std::shared_ptr<TimerHandle>  SetTimeout(std::function<void()> f, int delay, bool isDetached) {
        
        std::shared_ptr<TimerHandle> handle = std::make_shared<TimerHandle>();
        handle -> f = f;
        handle -> delay = delay;
        
        handle->state = TimerHandle::INIT;
        
        auto  wrapper = [&] () -> void {
            
            try {
                if (handle->state == TimerHandle::IS_CANCELED) {
                    delete handle->theThread;
                    return ;
                };
                
                std::this_thread::sleep_for(std::chrono::milliseconds(handle->delay));
                
                if (handle->state == TimerHandle::IS_CANCELED)  {
                    return ;
                }
                
                handle->f();
                
                handle->state = TimerHandle::COMPLETED;
                
            }catch ( std::system_error e){
                
                handle->state = TimerHandle::ERROR_STATE;
            }
            
            
        };
        
        
        handle->theThread  = new std::thread( wrapper);
        
        if (isDetached) {
            handle->theThread ->detach();
        }
        
        return handle;
    }


    std::shared_ptr<TimerHandle>  SetInterval(std::function<void()> f,int delay ,bool isDetached  ) {

        std::shared_ptr<TimerHandle> handle = std::make_shared<TimerHandle>();
        handle -> f = f;
        handle -> delay = delay;

    
        bool isRunning = true;
        auto wrapper = [&]() -> void {
            
            while (isRunning) {
                
                if ( handle->state == TimerHandle::REQUEST_CANCEL || handle->state == TimerHandle::IS_CANCELED  ) {
                    handle->state = TimerHandle::IS_CANCELED;
                    isRunning = false;
                    return;
                }

                if ( handle->executeLimit > 0 && handle->executedCount >= handle->executeLimit ) {
                    handle->state = TimerHandle::COMPLETED;
                    isRunning = false;
                    return;
                }

                handle->state = TimerHandle::SLEEPING;

                std::this_thread::sleep_for(std::chrono::milliseconds(handle->delay));

                if (handle->state == TimerHandle::REQUEST_CANCEL) {
                    handle->state = TimerHandle::IS_CANCELED;
                    isRunning = false;
                    return;
                }
                handle->state = TimerHandle::RUNNING;
                
                handle->f();
                
                handle->executedCount=  handle->executedCount + 1;
            }
        };

        handle->theThread = new std::thread( wrapper );
        
        if ( isDetached == true) {
            handle->theThread->detach();
        }
        
        return handle;
    }


template < typename IN, typename OUT>
std::shared_ptr<TimerHandle2<IN,OUT>>  SetInterval2(std::function<OUT(IN)> f,int delay ,bool isDetached  ) {

    std::shared_ptr<TimerHandle2<IN,OUT>> handle = std::make_shared< TimerHandle2<IN,OUT> >();
    handle -> f = f;
    handle -> delay = delay;


    bool isRunning = true;
    auto wrapper = [&]() -> void {
        
        while (isRunning) {
            
            if ( handle->state == TimerHandle::REQUEST_CANCEL || handle->state == TimerHandle::IS_CANCELED  ) {
                handle->state = TimerHandle::IS_CANCELED;
                isRunning = false;
                return;
            }

            if ( handle->executeLimit > 0 && handle->executedCount >= handle->executeLimit ) {
                handle->state = TimerHandle::COMPLETED;
                isRunning = false;
                return;
            }

            handle->state = TimerHandle::SLEEPING;

            std::this_thread::sleep_for(std::chrono::milliseconds(handle->delay));

            if (handle->state == TimerHandle::REQUEST_CANCEL) {
                handle->state = TimerHandle::IS_CANCELED;
                isRunning = false;
                return;
            }
            handle->state = TimerHandle::RUNNING;
            
            OUT o = handle->f(handle->getIN());
            handle-> pushOut(o);
            handle->executedCount=  handle->executedCount + 1;
        }
    };

    handle->theThread = new std::thread( wrapper );
    
    if (isDetached) {
        handle->theThread->detach();
    }
    
    return handle;
}
}
