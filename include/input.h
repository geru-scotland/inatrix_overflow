/*-------------------------------------
input.h
-------------------------------------*/
#ifndef INPUT_H
#define INPUT_H
//registros del teclado
#define TECLAS_DAT	(*(vu16*)0x4000130) //registro de datos
#define TECLAS_CNT	(*(vu16*)0x4000132) //registro de control

enum KEYS {
    INPUT_KEY_A       = 0,
    INPUT_KEY_B		  = 1,
    INPUT_KEY_SELECT  = 2,
    INPUT_KEY_START	  = 3,
    INPUT_KEY_RIGHT	  = 4,
    INPUT_KEY_LEFT    = 5,
    INPUT_KEY_UP      = 6,
    INPUT_KEY_DOWN    = 7,
    INPUT_KEY_R       = 8,
    INPUT_KEY_L       = 9
};

typedef struct {
    bool isPressed;
    int key;
} KeyData;

extern KeyData keyData;

// TODO: Poner extern solo las que realmente vayan a ser linkadas
// En otros archivos, no en el c

extern void input_ConfigureInput(int mask);
extern void input_UpdateKeyData();
extern int input_KeyDetected();
extern int input_KeyPressed();
#endif // INPUT_H
