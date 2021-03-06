
//Example 019 Mouse and Joystick

//This tutorial builds on example 04.Movement which showed how to
//handle keyboard events in Irrlicht.  Here we'll handle mouse events
//and joystick events, if you have a joystick connected and a device
//that supports joysticks.  These are currently Windows, Linux and SDL
//devices.


#ifdef _MSC_VER

// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include <irrKlang.h>
#include <Box2D/Box2D.h>
#include "driverChoice.h"
#include "include/Enemigo.h"
#include "include/Player.h"
#include "irrKlang/conio.h"


using namespace irr;
using namespace irrklang;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

//we'll store the latest state of the mouse and the first joystick, updating them as we receive events.

class MyEventReceiver : public IEventReceiver
{
private:
    bool KeyDown[KEY_KEY_CODES_COUNT];
public:

    MyEventReceiver()
    {
        for(int i=0; i<KEY_KEY_CODES_COUNT; i++)
        {
            KeyDown[i] = false;
        }
    }

    struct SMouseState
    {
        core::position2di Position;
        bool RightButtonDown;
        SMouseState() : RightButtonDown(false) { }
    } MouseState;

    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember the mouse state
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_RMOUSE_PRESSED_DOWN:
                MouseState.RightButtonDown = true;
                break;

            case EMIE_RMOUSE_LEFT_UP:
                MouseState.RightButtonDown = false;
                break;

            case EMIE_MOUSE_MOVED:
                MouseState.Position.X = event.MouseInput.X;
                MouseState.Position.Y = event.MouseInput.Y;
                break;

            default:
                // We won't use the wheel
                break;
            }
        }
        else if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
            KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }

    }

    virtual bool isKeyDown(EKEY_CODE keyCode) const
    {
        return KeyDown[keyCode];
    }

    virtual bool isKeyUp(EKEY_CODE keyCode) const
    {
        return !KeyDown[keyCode];
    }
    const SMouseState & GetMouseState(void) const
    {
        return MouseState;
    }


};


//The event receiver for keeping the pressed keys is ready, the actual responses
//will be made inside the render loop, right before drawing the scene. So lets
//just create an irr::IrrlichtDevice and the scene node we want to move. We also
//create some other additional scene nodes, to show that there are also some
//different possibilities to move and animate scene nodes.


int main()
{
    /// BOX 2D

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    /// IRR KLANG

    ISoundEngine* engine = createIrrKlangDevice();


	if (!engine)
		return 0; // error starting up the engine

	//printf("Driver: %s\n",engine->getDriverName());
	//printf("Volume: %f\n",engine->getSoundVolume());

	ISoundSource* pasos1 = engine->addSoundSourceFromFile("sonidos/pasosnormales.wav");
	ISoundSource* pasos2 = engine->addSoundSourceFromFile("sonidos/pasossigilosos.wav");
	ISoundSource* alarma = engine->addSoundSourceFromFile("sonidos/alarma_sintetizada2.wav");
	vec3df posicion(0,0,0);
	ISound* s1;
	ISound* s2;


	bool pasosP = false;
	bool pasos2P = false;
	bool cambiao = false;
    bool protaColliding = false;

	if (pasos1 == 0 || pasos2 == 0)
        	fprintf(stderr,"Can't load sounds!");

    pasos1->setDefaultVolume(2.0f);
    pasos2->setDefaultVolume(1.0f);


    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    // create device
    MyEventReceiver receiver;

    Enemigo *enemigo1 = new Enemigo;
    Enemigo *enemigo2 = new Enemigo;
    Player  *prota    = new Player;


    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1080, 720), 16, false, false, false, &receiver);
    IGUIEnvironment* guienv = device->getGUIEnvironment(); //Cargamos la GUI

    device->setWindowCaption(L"IKI" );
    //guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",rect<s32>(10,10,10,10), true );

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    //scene::IMeshSceneNode *prota = smgr->addCubeSceneNode(5);

    /// MUROS////////////
    scene::IMeshSceneNode *muro1 = smgr->addCubeSceneNode(10);
        muro1->setMaterialFlag(video::EMF_LIGHTING, false);
        muro1->setPosition(core::vector3df(0,0,0));
        smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),irr::video::SColor(0, 0, 0, 0));


    IMesh *mesh = smgr->getGeometryCreator()->createCubeMesh(vector3df(300.f, -5.f, 300.f));
     scene::IMeshSceneNode *suelo = smgr->addMeshSceneNode(mesh);

    if(suelo){
       suelo->setPosition(core::vector3df(0.0f, 0.0f, 0.0f));
       suelo->setRotation(core::vector3df(0,0,0));
       suelo->setMaterialFlag(EMF_LIGHTING, false);
       suelo->setMaterialTexture( 0, driver->getTexture("texturas/suelo.png") );
       //suelo->getMaterial(0).getTextureMatrix(0).setTextureTranslate(1,1);
       //suelo->getMaterial(0).getTextureMatrix(0).setTextureScale(1,1);
    }

    if(prota)
    {
        prota->inicializar(smgr,driver);
        //prota->setMaterialFlag(video::EMF_LIGHTING, false);
        //prota->setPosition(core::vector3df(0,0,0));
    }
    if(enemigo1)
        enemigo1->inicialiazar(0, smgr, core::vector3df(35,0,35));
    if(enemigo2)
        enemigo2->inicialiazar(1, smgr, core::vector3df(-35,0,35));

    //core::vector3df posicionInicial (35,0,35);
    //enemigo1.setPunto((prota->getPosition())-(enemigo->getPosition()));

    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    //we'll use framerate independent movement.
    u32 then = device->getTimer()->getTime();
    f32 MOVEMENT_SPEED = 25.f;
    const f32 MOVEMENT_SPEED_ENEMY = 15.f;
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition = core::vector3df(40,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());

    //cambio de color de mallas
    smgr->getMeshManipulator()->setVertexColors(enemigo1->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));
    smgr->getMeshManipulator()->setVertexColors(enemigo2->getModelo()->getMesh(),irr::video::SColor(0, 255, 255, 0));

    while(device->run())
    {
        if(receiver.isKeyDown(KEY_LSHIFT))
            MOVEMENT_SPEED = 15.f;
        else
            MOVEMENT_SPEED = 25.f;


        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        core::vector3df cameraPos = camera->getPosition();
        core::vector3df cameraTar = camera->getTarget();

        //core::vector3df cuboProta = prota->getPosition();
        //core::vector3df cuboEnemigo = enemy->getPosition();
        core::vector3df direccionProta (prota->getCuboProta() - enemigo1->getCuboEnemigo());



        //core::vector3df direccionProta2 (cuboProta-cameraPos);


        /// COLISIONES ///
        if(prota->getModelo()->getTransformedBoundingBox().intersectsWithBox(muro1->getTransformedBoundingBox())){
            //std::cout<< "si" <<std::endl;
            protaColliding = true;
        }
        else{
            //std::cout<< "no" <<std::endl;
            protaColliding = false;
        }


        /// ////////////////////

        const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

        if(receiver.isKeyDown(KEY_ESCAPE))
        {
            device->closeDevice();
            return 0;
        }
        else if(receiver.isKeyDown(KEY_RIGHT))
        {
            cameraPos.X+=0.1;
            cameraTar.X+=0.1;
        }
        else if (receiver.isKeyDown(KEY_LEFT))
        {
            cameraPos.X-=0.1;
            cameraTar.X-=0.1;
        }
        else if(receiver.isKeyDown(KEY_UP))
        {
            cameraPos.Z+=0.1;
            cameraTar.Z+=0.1;
        }
        else if (receiver.isKeyDown(KEY_DOWN))
        {
            cameraPos.Z-=0.1;
            cameraTar.Z-=0.1;
        }
        if(enemigo2->getEstado() == 2){
            if(cambiao == false){
                smgr->getMeshManipulator()->setVertexColors(enemigo2->getModelo()->getMesh(),irr::video::SColor(255, 0, 255, 0));
                s2 = engine->play3D(alarma,posicion,false,false,true);
                cambiao = true;
            }
            else if(s2->isFinished()){
                enemigo2->getModelo()->setPosition(core::vector3df(-1000,0,0));
            }
        }


        if(receiver.GetMouseState().RightButtonDown)
        {
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                      receiver.GetMouseState().Position, camera);

        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - prota->getCuboProta());
            const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

            int protaX = mousePosition.X;
            int protaZ = mousePosition.Z;


            if (!protaColliding){
            /// SI NO COLISIONA SE MOVERA EN LINEA RECTA HASTA QUE COLISIONE


                if(toMousePosition.getLength() <= availableMovement){
                    prota->setCuboProta(mousePosition);
                    if(pasosP==true || pasos2P==true){
                        s1->stop();
                        pasosP = false;
                        pasos2P = false;
					}
                    //cuboProta = mousePosition; // Jump to the final position
                }else{
                    prota->setCuboProta(prota->getCuboProta() + toMousePosition.normalize() * availableMovement);
                    if(pasosP==false && !receiver.isKeyDown(KEY_LSHIFT)){
                        if(engine->isCurrentlyPlaying(pasos2))
                            s1->stop();

                            s1 = engine->play3D(pasos1,posicion,true,false,true);

                        pasosP = true;
                        pasos2P = false;

                    }else if (pasos2P==false && receiver.isKeyDown(KEY_LSHIFT)){
                        if(engine->isCurrentlyPlaying(pasos1))
                            s1->stop();

                            s1 = engine->play3D(pasos2,posicion,true,false,true);
                        pasos2P = true;
                        pasosP = false;

                    }
                    //cuboProta += toMousePosition.normalize() * availableMovement; // Move towards i
                    //Para que la camara siga al prota
                    //cameraPos += toMousePosition.normalize() *availableMovement;
                    //cameraTar += toMousePosition.normalize() *availableMovement;

                }
            }else{
            /// COLISIONA Y PRIORIZA UNA DIRECCION

                core::vector3df redireccion;
                int pX =1, pZ = 1;

                if (protaX < 0){ protaX*=-1; pX = -1; }
                if (protaZ < 0){ protaZ*=-1; pZ = -1; }

                if (protaX > protaZ)
                    redireccion.set(0,0,pZ);
                else
                    redireccion.set(pX,0,0);

                prota->setCuboProta(prota->getCuboProta() + redireccion * availableMovement);
                //cuboProta += redireccion * availableMovement;

            }

        //std::cout<< "Prota X = " << protaX << "__ Prota Z = " << protaZ <<std::endl;

        }

        enemigo1->update(direccionProta, prota->getCuboProta(), frameDeltaTime);
        enemigo2->update(direccionProta, prota->getCuboProta(), frameDeltaTime);

        prota->getModelo()->setPosition(prota->getCuboProta());
        enemigo1->getModelo()->setPosition(enemigo1->getCuboEnemigo());
        if(cambiao == false)
            enemigo2->getModelo()->setPosition(enemigo2->getCuboEnemigo());
        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);

        driver->beginScene(true, true, video::SColor(255,113,113,133));
        smgr->drawAll(); // draw the 3d scene
        driver->endScene();
    }


   // In the end, delete the Irrlicht device.
    device->drop();
    engine->drop();

    return 0;
}
