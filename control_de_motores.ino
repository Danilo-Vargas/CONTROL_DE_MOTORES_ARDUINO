
// CONTROL DE MOTORES - Aldo Danilo Vargas Esquivel - 25/09/2021

// DECLARAMOS PINES

    // MOTORES

#define MOTOR_1_H 5
#define MOTOR_1_A 6
#define MOTOR_2_H 10
#define MOTOR_2_A 11

    // SENSORES

#define s1 A0
#define s2 A1

// INICIAR VARIABLES

    // CONTROL DE MOTORES

int c1 = 0;
int c2 = 0;

    // LECTURAS DE LOS SENSORES

int R1 = 0;
int R2 = 0;

    // VALORES PARA LAS CONDICIONES (CAMBIAR PARA CALIBRAR), EL RANGO ESTABLECIDO ENTRE min Y max,
                                                    // ES EL RANGO EN EL CUÁL LOS MOTORES ESTARÁN APAGADOS
int min_1 = 0; // LECTURA MINIMA DEL SENSOR 1
int min_2 = 0; // LECTURA MINIMA DEL SENSOR 2

int max_1 = 1023; // LECTURA MAXIMA DEL SENSOR 1
int max_2 = 1023; // LECTURA MAXIMA DEL SENSOR 2

int range_off_1[2] = {530, 550}; // RANGO EN EL CUAL EL MOTOR 1 DEBE ESTAR APAGADO, DEBE SER UN RANGO MEDIO DEL RANGO TOTAL MEDIDO DEL SENSOR 1
int range_off_2[2] = {530, 565}; // RANGO EN EL CUAL EL MOTOR 2 DEBE ESTAR APAGADO, DEBE SER UN RANGO MEDIO DEL RANGO TOTAL MEDIDO DEL SENSOR 2

    //*** PRIMER VALOR MINIMO, SEGUNDO VALOR MAXIMO
    
// INICIAR FUNCIONES

void readState(){
    R1 = analogRead(s1);
    R2 = analogRead(s2);

    Serial.print(R1);
    Serial.print(" - ");
    Serial.println(R2);

    delay(200);
}

void controlMotors(){

    readState();

    if( R1 < range_off_1[0]){
        
        c1 = map(R1, min_1,range_off_1[0], 255,0);

        analogWrite(MOTOR_1_A, 0);
        analogWrite(MOTOR_1_H, c1);

    } else if( R1 >= range_off_1[0] && R1 <= range_off_1[1] ){

        analogWrite(MOTOR_1_A, 0);
        analogWrite(MOTOR_1_H, 0);

    } else if( R1 > range_off_1[1] ){

        c1 = map(R1, range_off_1[1],max_1, 0,255);

        analogWrite(MOTOR_1_H, 0);
        analogWrite(MOTOR_1_A, c1);

    }

    if( R2 < range_off_2[0]){
        
        c2 = map(R2, min_2,range_off_2[0], 255,0);

        analogWrite(MOTOR_2_A, 0);
        analogWrite(MOTOR_2_H, c2);

    } else if( R2 >= range_off_2[0] && R2 <= range_off_2[1] ){

        analogWrite(MOTOR_2_A, 0);
        analogWrite(MOTOR_2_H, 0);

    } else if( R2 > range_off_2[1] ){

        c2 = map(R2, range_off_2[1],max_2, 0,255);

        analogWrite(MOTOR_2_H, 0);
        analogWrite(MOTOR_2_A, c2);

    }

}

void setup()
{
	pinMode(MOTOR_1_H, OUTPUT);
    pinMode(MOTOR_1_A, OUTPUT);
  
    pinMode(MOTOR_2_H, OUTPUT);
    pinMode(MOTOR_2_A, OUTPUT);
  
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);

    Serial.begin(9600);
    
}

void loop()
{
	controlMotors();
}
