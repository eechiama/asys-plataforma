/* CONSTANTES */
/**************/

// PARA EL SETUP DEL PUERTO SERIE
const long BAUD_RATE = 115200;

// PARA EL SETUP DEL TIMER
const int PERIOD_DEFAULT = 400;   // para fs = 2500Hz

// PARA LA VARIABLE: estado_rx
const int ESPERANDO_TRAMA = 0;
const int RECIBIENDO_TRAMA = 1;

// PARA EL BUFFER DE TRAMA RECIBIDA
const int MAX_TRAMA_RX = 8;

// PARA LA VARIABLE: estado_medidor
const int MEDIDOR_RESET = 0;
const int MEDIDOR_INACTIVO = 1;
const int MEDIDOR_ACTIVO = 2;

// PARA LA VARIABLE: command
const int NO_COMMAND = 10;
const int START_ADC = 11;
const int STOP_ADC = 12;
const int SEND_TEST_SIGNAL_1 = 13;
const int SEND_TEST_SIGNAL_2 = 14;
const int SEND_TEST_SIGNAL_3 = 15;
const int CONFIG_SR = 16;

// Constantes para indicar la tx status de la señal de prueba
const int TX_DOING = 0;
const int TX_DONE = 1;

// PR_ADC.h
const int SIZE = 1;
const int VECTORES_LLENOS = 1;
const int ENLISTANDO = 2;






/* PROTOTIPOS DE FUNCIONES */
/***************************/

void Controlador(void);
void RX_Mensajes(void);
void leer_comandos( const char msg_rx[] );
uint8_t tx_Test_Signal_1( void );
uint8_t tx_Test_Signal_2( void );
uint8_t tx_Test_Signal_3( void );

void Start_Sampling(void);
void Stop_Sampling(void);
void ADC_Convert_Start(void);

void TimerCallback(void);

void ResetBuffer( void );
uint8_t GetBufferStatus( void );
void Enlistar( void );
uint16_t Mediana_de_Buffer( void );
void bubble(volatile uint16_t *vector, int sizze);

void Preparar_y_Enviar( void );
void EnviarMuestra( uint16_t MuestraEfectiva );
