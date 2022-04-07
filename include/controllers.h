/*-------------------------------------
controllers.h
-------------------------------------*/

void controllers_EnableInterruptsMaster();
void controllers_DisableInterruptsMaster();

void controllers_ConfigureTimer();
void controllers_ConfigureInput();
void controllers_EnableKeyPadInt();
void controllers_DisableKeyPadInt();

/* Handlers */
extern void controllers_KeyPadHandler();
extern void controllers_TimerHandler();

/* Init Setup */
void controllers_SetInterruptionVector();
extern void controllers_InitSetup();