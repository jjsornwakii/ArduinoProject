#define LED_S_R 5
#define LED_S_Y 6
#define LED_S_G 7
#define SOUTH_BUTTON_PIN 2
#define LED_W_R 8
#define LED_W_Y 9
#define LED_W_G 10
#define WEST_BUTTON_PIN 3
#define LED_H_R 11
#define LED_H_G 12
#define PATH_BUTTON_PIN 4
#define goS 0
#define waitStW 1
#define waitStH 2
#define goW 3
#define waitWtS 4
#define waitWtH 5
#define goH 6
#define waitHF1 7
#define waitHN1 8
#define waitHF2 9
#define waitHN2 10
#define waitHF3 11
#define waitHN3 12
#define waitHF1W 13
#define waitHN1W 14
#define waitHF2W 15
#define waitHN2W 16
#define waitHF3W 17
#define waitHN3W 18
struct State
{
 unsigned long ST_Out; // 8-bit pattern to street output
 unsigned long Time; // delay in ms units
 unsigned long Next[8];
}; // next state for inputs
typedef const struct State SType;
SType FSM[19] = {
 {B00110010, 1500, {goS, goS, waitStW, waitStW, waitStH, waitStH, waitStW, waitStW}}, //south on
 {B01010010, 300, {goW, goW, goW, goW, goW, goW, goW, goW}}, // wait south to w
 {B01010010, 300, {goH, goH, goH, goH, goH, goH, goH, goH}}, // wait south to h
 {B10000110, 1500, {goW, waitWtS, goW, waitWtS, waitWtH, waitWtS, waitWtH, waitWtH}}, // west on
 {B10001010, 300, {goS, goS, goS, goS, goS, goS, goS, goS}}, // wait west to s
 {B10001010, 300, {goH, goH, goH, goH, goH, goH, goH, goH}}, // wait west to h
 {B10010001, 1500, {goH, waitHF1, waitHF1W, waitHF1, goH, waitHF1, waitHF1W, waitHF1}}, // path on
 {B10010000, 400, {waitHN1, waitHN1, waitHN1, waitHN1, waitHN1, waitHN1, waitHN1, waitHN1}}, //wait path 1 off to S
 {B10010001, 400, {waitHF2, waitHF2, waitHF2, waitHF2, waitHF2, waitHF2, waitHF2, waitHF2}}, //wait path 1 on to S
 {B10010000, 400, {waitHN2, waitHN2, waitHN2, waitHN2, waitHN2, waitHN2, waitHN2, waitHN2}}, //wait path 2 off to S
 {B10010001, 400, {waitHF3, waitHF3, waitHF3, waitHF3, waitHF3, waitHF3, waitHF3, waitHF3}}, //wait path 2 on to S
 {B10010000, 400, {waitHN3, waitHN3, waitHN3, waitHN3, waitHN3, waitHN3, waitHN3, waitHN3}}, //wait path 3 off to S
 {B01010001, 400, {goS, goS, goS, goS, goS, goS, goS, goS}}, //wait path 3 off to S
 {B10010000, 400, {waitHN1W, waitHN1W, waitHN1W, waitHN1W, waitHN1W, waitHN1W, waitHN1W, waitHN1W}}, //wait path 1 off to W
 {B10010001, 400, {waitHF2W, waitHF2W, waitHF2W, waitHF2W, waitHF2W, waitHF2W, waitHF2W, waitHF2W}}, //wait path 1 on to W
 {B10010000, 400, {waitHN2W, waitHN2W, waitHN2W, waitHN2W, waitHN2W, waitHN2W, waitHN2W, waitHN2W}}, //wait path 2 off to W
 {B10010001, 400, {waitHF3W, waitHF3W, waitHF3W, waitHF3W, waitHF3W, waitHF3W, waitHF3W, waitHF3W}}, //wait path 2 on to W
 {B10010000, 400, {waitHN3W, waitHN3W, waitHN3W, waitHN3W, waitHN3W, waitHN3W, waitHN3W, waitHN3W}}, //wait path 3 off to W
 {B10001001, 400, {goW, goW, goW, goW, goW, goW, goW, goW}}, //wait path 3 off to W
};
unsigned long S = 0; // index to the current state
void setup()
{
 pinMode(LED_S_R, OUTPUT);
 pinMode(LED_S_Y, OUTPUT);
 pinMode(LED_S_G, OUTPUT);
 pinMode(SOUTH_BUTTON_PIN, INPUT);
 pinMode(LED_W_R, OUTPUT);
 pinMode(LED_W_Y, OUTPUT);
 pinMode(LED_W_G, OUTPUT);
 pinMode(WEST_BUTTON_PIN, INPUT);
 pinMode(LED_H_R, OUTPUT);
 pinMode(LED_H_G, OUTPUT);
 pinMode(PATH_BUTTON_PIN, INPUT);
}
int input, input1, input2, input3;
void loop()
{
 digitalWrite(LED_S_R, FSM[S].ST_Out & B10000000);
 digitalWrite(LED_S_Y, FSM[S].ST_Out & B01000000);
 digitalWrite(LED_S_G, FSM[S].ST_Out & B00100000);
 digitalWrite(LED_W_R, FSM[S].ST_Out & B00010000);
 digitalWrite(LED_W_Y, FSM[S].ST_Out & B00001000);
 digitalWrite(LED_W_G, FSM[S].ST_Out & B00000100);
 digitalWrite(LED_H_R, FSM[S].ST_Out & B00000010);
 digitalWrite(LED_H_G, FSM[S].ST_Out & B00000001);
 delay(FSM[S].Time);
 input1 = digitalRead(SOUTH_BUTTON_PIN);
 input2 = digitalRead(WEST_BUTTON_PIN);
 input3 = digitalRead(PATH_BUTTON_PIN);
 input = input3 * 4 + input2 * 2 + input1;
 S = FSM[S].Next[input];
}
