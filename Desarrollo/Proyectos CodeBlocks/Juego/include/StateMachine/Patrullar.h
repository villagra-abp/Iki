#ifndef PATRULLAR
#define PATRULLAR

#include "StateMachine/State.h"


class Enemy;
class Mensaje;

//template <class entity_type>
class Patrullar : public State<Enemy>
{
public:
    static Patrullar* Instance();
    void Enter(Enemy* enemigo);
    void Execute(Enemy* enemigo);
    void Exit(Enemy* enemigo);
    bool OnMessage(Enemy*, const Mensaje&);

private:
    Patrullar(){};
    //copy ctor and assignment should be private
    Patrullar(const Patrullar&);
    Patrullar& operator=(const Patrullar&);


};

#endif // PATRULLAR
