/*-------------------------------------
controllers.h
-------------------------------------*/

void controllers_EnableInterruptsMaster();
void controllers_DisableInterruptsMaster();
void controllers_SetInterruptionVector();

void controllers_ConfigureInput();
void controllers_EnableKeyPadInt();
void controllers_DisableKeyPadInt();

extern void controllers_InitSetup();

/* Handlers */
extern void controllers_KeyPadHandler();
extern void controllers_TimerHandler();