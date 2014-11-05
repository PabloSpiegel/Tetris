//Modified from http://www.cplusplus.com/forum/unices/25213/
#ifndef TIMER_H
#define TIMER_H
#include <sys/time.h>

class Timer
{
    public:
        Timer(unsigned int Delay=0);
        bool Probe();
        bool Probe(timeval& SomeTime); //could be useful if there're 1000 timers in row
        void Start() { isActive=true;}
        void Stop() { isActive=false;}
        bool IsActive() { return isActive; }
        void SetDelay(unsigned int Delay) { itsDelay=Delay; }
        const unsigned int &GetDelay(){
            return itsDelay;
        }
    protected:
    private:
        unsigned int itsDelay;
        bool isActive;
        timeval itsStart;
};

#endif // TIMER_H 