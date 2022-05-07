/*-------------------------------------
perifericos.h
-------------------------------------*/

extern int TeclaDetectada();
extern int TeclaPulsada();
extern void ConfigurarTeclado(int Conf_Tec);
extern void ConfigurarTemporizador(int Latch, int Conf_Tempo);
extern void HabilitarIntTeclado();
extern void InhibirIntTeclado();
extern void HabilitarIntTempo();
extern void InhibirIntTempo();
extern void PonerEnMarchaTempo();
extern void PararTempo();

