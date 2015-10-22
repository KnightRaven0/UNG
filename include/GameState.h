#ifndef GAMESTATE_H
#define GAMESTATE_H

class MasterControl;

class GameState{
    public:
        virtual ~GameState(){}
        virtual void Update(MasterControl* Control) = 0;
        virtual void Pause(){}
        virtual void Resume(){}
};

#endif // GAMESTATE_H
