/*-------------------------------------
controllers.h
-------------------------------------*/

extern void controllers_EnableInterruptsMaster();
extern void controllers_DisableInterruptsMaster();
extern void controllers_SetInterruptionVector();
extern void controllers_ConfigureControlRegisters();
extern void controllers_ConfigureInterrupts();

/* Handlers */
extern void controllers_KeyPadHandler();
extern void controllers_TimerHandler();