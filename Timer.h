// Author: Adrian A. Gerbaud H.
// Advanced timer class to control max fps.

class Timer
{
   
    public:

    Timer();

    //Clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Get time
    int get_ticks();

    //Status
    bool is_started();
    bool is_paused();


 private:
    
    int startTicks;
    int pausedTicks;
  
    // Status
    bool paused;
    bool started;

};
