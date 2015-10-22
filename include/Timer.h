#ifndef TIMER_H
#define TIMER_H

class Timer{
    public:
        Timer(int Delay, bool TrueTime = false);
        bool IsTime();
        void Pause();
        void Resume();

        static void InitializeTime();
        static void PauseGame();
        static void UnpauseGame();
        static void Update();
        static void SetGameSpeed(float NewSpeed);   //1 is normal 2 is twice as fast .5 is twice as slow
        static int GetTicks();

    protected:
        int Time;
        int DeltaTime;
        bool TrueTime;
        bool LocalPause;
        static bool Paused;
        static int AssumedGameTime;
        static float UsedGameTime;
        static float GameSpeed;
};

#endif // TIMER_H
