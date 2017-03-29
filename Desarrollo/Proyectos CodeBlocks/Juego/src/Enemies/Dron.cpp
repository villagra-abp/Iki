#include "Enemies/Dron.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"


void Dron::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    EntityMgr->registrarEntity(this);
    Structs::TColor color = {0,255,0,0};
    tipo = 3;
    modelo->cambiarColor(color);
}