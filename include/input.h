/*-------------------------------------
input.h
-------------------------------------*/

//registros del teclado
#define TECLAS_DAT	(*(vu16*)0x4000130) //registro de datos
#define TECLAS_CNT	(*(vu16*)0x4000132) //registro de control

enum KEYS {
    A         = 0,
    B		  = 1,
    SELECT	  = 2,
    START	  = 3,
    DERECHA	  = 4,
    IZQUIERDA = 5,
    ARRIBA    = 6,
    ABAJO     = 7,
    R         = 8,
    L         = 9
};

extern int input_KeyDetected();
extern int input_KeyPressed();
extern void input_ConfigureKeypad(int Conf_Tec);
extern void input_EnableKeyPadInt();
extern void input_DisableKeyPadInt();
extern void input_KeyPadHandler();


