#ifndef GAME_H
#define GAME_H

#include "Structs.h"
#include "Fachada/AnimatedMesh.h"
#include "Fachada/SceneNode.h"
#include "MyEventReceiver.h"
#include "Map.h"
#include "Mensaje.h"
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <map>



#include <Box2D/Box2D.h>

class GameEntity
{
    public:
        GameEntity();
        ~GameEntity();

        //Getters
        virtual Structs::TPosicion getPosition() { return posicion; };
        virtual float              getVida()     { return vida;     };
        virtual float              getRadio()    { return radio;    };
        virtual bool               isPlayer()    { return false;    };
        virtual int                ID()          { return id;       };

        virtual b2Body*            getBody(){return body;};
        virtual void               setBody(b2BodyDef bodyDef);
        virtual void               setMesh(AnimatedMesh* m){ aniMesh = m;};
        virtual bool               HandleMessage(const Mensaje& msg)=0;


    protected:

        AnimatedMesh *aniMesh;
        SceneNode *modelo;
        b2Body *body;

        int id,nextID=0;
        float vida;
        Structs::TPosicion posicion;
        float radio;

};

#endif // GAME_H
