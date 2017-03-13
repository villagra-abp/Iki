#include "EnviarMensaje.h"
#include "GameEntity.h"
//#include "misc/FrameCounter.h"
//#include "game/EntityManager.h"
//#include "Debug/DebugConsole.h"
/*
using std::set;

EnviarMensaje* EnviarMensaje::Instance()
{
  static EnviarMensaje instance;

  return &instance;
}

void EnviarMensaje::Envio(GameEntity* pReceiver, const Mensaje& telegram)
{
  if (!Receptor->HandleMessage(telegram))
  {
    //telegram could not be handled
    #ifdef SHOW_MESSAGING_INFO
    debug_con << "Message not handled" << "";
    #endif
  }
}

//---------------------------- DispatchMsg ---------------------------
//
//  given a message, a receiver, a sender and any time delay, this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
void EnviarMensaje::Envio(double       delay,
                                    int          sender,
                                    int          receiver,
                                    int          msg,
                                    void*        AdditionalInfo = NULL)
{

  //get a pointer to the receiver
  GameEntity* Receptor = EntityMgr->GetEntityFromID(receiver);

  //make sure the receiver is valid
  if (Receptor == NULL)
  {
    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nWarning! No Receiver with ID of " << receiver << " found" << "";
    #endif

    return;
  }

  //create the Mensaje
  Mensaje Mensaje(0, sender, receiver, msg, AdditionalInfo);

  //if there is no delay, route Mensaje immediately
  if (delay <= 0.0)
  {
    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nTelegram dispatched at time: " << TickCounter->GetCurrentFrame()
         << " by " << sender << " for " << receiver
         << ". Msg is " << msg << "";
    #endif

    //send the Mensaje to the recipient
    Envio(Receptor, Mensaje);
  }

  //else calculate the time when the Mensaje should be dispatched
  else
  {
    double CurrentTime = TickCounter->GetCurrentFrame();

    Mensaje.DispatchTime = CurrentTime + delay;

    //and put it in the queue
    PriorityQ.insert(Mensaje);

    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nDelayed Mensaje from " << sender << " recorded at time "
            << TickCounter->GetCurrentFrame() << " for " << receiver
            << ". Msg is " << msg << "";
    #endif
  }
}

//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void EnviarMensaje::EnvioMensajePendiente()
{
  //first get current time
  double CurrentTime = TickCounter->GetCurrentFrame();

  //now peek at the queue to see if any telegrams need dispatching.
  //remove all telegrams from the front of the queue that have gone
  //past their sell by date
  while( !PriorityQ.empty() &&
	     (PriorityQ.begin()->DispatchTime < CurrentTime) &&
         (PriorityQ.begin()->DispatchTime > 0) )
  {
    //read the Mensaje from the front of the queue
    const Mensaje& Mensaje = *PriorityQ.begin();

    //find the recipient
    GameEntity* Receptor = EntityMgr->GetEntityFromID(Mensaje.Receiver);

    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nQueued Mensaje ready for dispatch: Sent to "
         << Receptor->ID() << ". Msg is "<< Mensaje.Msg << "";
    #endif

    //send the Mensaje to the recipient
    Envio(Receptor, Mensaje);

	//remove it from the queue
    PriorityQ.erase(PriorityQ.begin());
  }
}

*/

