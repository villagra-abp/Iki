#include "Trigger_Ruido.h"
#include "Fachada/GraphicsFacade.h"
#include "Player.h"
#include "Enemy.h"
<<<<<<< HEAD
#include "EntityManager.h"
=======

#include "Escuchar.h"
#include "Patrullar.h"
>>>>>>> refs/remotes/origin/master

#include <iostream>

Trigger_Ruido::Trigger_Ruido()
{
    //ctor
    SetInactive();
}

Trigger_Ruido::~Trigger_Ruido()
{
    //dtor
}

void Trigger_Ruido::Try(GameEntity* ent)
{
    if (isActive() && !ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        //show interrogante

        if (speed == 1){
            // se mueve lento y me detectan
        }else{
            Enemy* enemigo = static_cast<Enemy*>(ent);
            if (enemigo->GetFSM()->CurrentState() == Patrullar::Instance()){
                enemigo->GetFSM()->ChangeState(Escuchar::Instance());
            }
            //else
        }
    }
}

void Trigger_Ruido::Update()
{
    GameEntity* ent = EntityMgr->getEntityByID(0);
    posicion = ent->getPosition();
    speed = static_cast<Player*>(ent)->getSpeed();
}
