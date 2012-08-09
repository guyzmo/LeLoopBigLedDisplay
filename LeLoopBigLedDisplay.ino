/*
this code is WTFPL, please reuse it, improve it and share it as much as you like and pay me a beer !
(c)2011 guyzmo at leloop dot org
                            _
pixel is changing at each _/

if NDATA == true and NCP == true
    if DATA == true
        at each CP = !CP next pixel is set to on
    if DATA == false
        at each CP = !CP next pixel is set to off


CD74HC4094E

*/


#define NB_DISP 9
#define NB_LINES 8
#define NB_COLS 96

#define NCP   11 // 5. 2Z  / Clock
#define CP    10 // 6. 2Y / 
#define NDATA 13 // 3. 1Z  / Data
#define DATA  12 // 2. 1Y /

//#define NCP   10 // 5. 2Z  / Clock
//#define CP    11 // 6. 2Y / 
//#define NDATA 12 // 3. 1Z  / Data
//#define DATA  13 // 2. 1Y /

//#define NCP   13 // 5. 2Z  / Clock
//#define CP    12 // 6. 2Y / 
//#define NDATA 11 // 3. 1Z  / Data
//#define DATA  10 // 2. 1Y /

//#define NCP   13 // 5. 2Z  / Clock
//#define CP    12 // 6. 2Y / 
//#define NDATA 10 // 3. 1Z  / Data
//#define DATA  11 // 2. 1Y /

//#define NCP   12 // 5. 2Z  / Clock
//#define CP    13 // 6. 2Y / 
//#define NDATA 11 // 3. 1Z  / Data
//#define DATA  10 // 2. 1Y /

//#define NCP   12 // 5. 2Z  / Clock
//#define CP    13 // 6. 2Y / 
//#define NDATA 10 // 3. 1Z  / Data
//#define DATA  11 // 2. 1Y /

#define DATA_DEFAULT HIGH
#define CP_DEFAULT   HIGH
#define NDATA_DEFAULT HIGH
#define NCP_DEFAULT   HIGH

const uint8_t Fond5x7_nbchar = 96;
const uint8_t Font5x7_nbcols = 5;
const uint8_t Font5x7_nblines = 7;
const uint8_t Font5x7[96][5] = {                                            
    0x00, 0x00, 0x00, 0x00, 0x00,// (space) 32
    0x00, 0x00, 0x5F, 0x00, 0x00,// !       33
    0x00, 0x07, 0x00, 0x07, 0x00,// "       34
    0x14, 0x7F, 0x14, 0x7F, 0x14,// #       35
    0x24, 0x2A, 0x7F, 0x2A, 0x12,// $       36
    0x23, 0x13, 0x08, 0x64, 0x62,// %       37
    0x36, 0x49, 0x55, 0x22, 0x50,// &       38
    0x00, 0x05, 0x03, 0x00, 0x00,// '       39
    0x00, 0x1C, 0x22, 0x41, 0x00,// (       40
    0x00, 0x41, 0x22, 0x1C, 0x00,// )       41
    0x08, 0x2A, 0x1C, 0x2A, 0x08,// *       42
    0x08, 0x08, 0x3E, 0x08, 0x08,// +       43
    0x00, 0x50, 0x30, 0x00, 0x00,// ,       44
    0x08, 0x08, 0x08, 0x08, 0x08,// -       45
    0x00, 0x60, 0x60, 0x00, 0x00,// .       46
    0x20, 0x10, 0x08, 0x04, 0x02,// /       47
    0x3E, 0x51, 0x49, 0x45, 0x3E,// 0       48
    0x00, 0x42, 0x7F, 0x40, 0x00,// 1       49
    0x42, 0x61, 0x51, 0x49, 0x46,// 2       50
    0x21, 0x41, 0x45, 0x4B, 0x31,// 3       51
    0x18, 0x14, 0x12, 0x7F, 0x10,// 4       52
    0x27, 0x45, 0x45, 0x45, 0x39,// 5       53
    0x3C, 0x4A, 0x49, 0x49, 0x30,// 6       54
    0x01, 0x71, 0x09, 0x05, 0x03,// 7       55
    0x36, 0x49, 0x49, 0x49, 0x36,// 8       56
    0x06, 0x49, 0x49, 0x29, 0x1E,// 9       57
    0x00, 0x36, 0x36, 0x00, 0x00,// :       58
    0x00, 0x56, 0x36, 0x00, 0x00,// ;       59
    0x00, 0x08, 0x14, 0x22, 0x41,// <       60
    0x14, 0x14, 0x14, 0x14, 0x14,// =       61
    0x41, 0x22, 0x14, 0x08, 0x00,// >       62
    0x02, 0x01, 0x51, 0x09, 0x06,// ?       63
    0x32, 0x49, 0x79, 0x41, 0x3E,// @       64
    0x7E, 0x11, 0x11, 0x11, 0x7E,// A       65
    0x7F, 0x49, 0x49, 0x49, 0x36,// B       66
    0x3E, 0x41, 0x41, 0x41, 0x22,// C       67
    0x7F, 0x41, 0x41, 0x22, 0x1C,// D       68
    0x7F, 0x49, 0x49, 0x49, 0x41,// E       69
    0x7F, 0x09, 0x09, 0x01, 0x01,// F       70
    0x3E, 0x41, 0x41, 0x51, 0x32,// G       71
    0x7F, 0x08, 0x08, 0x08, 0x7F,// H       72
    0x00, 0x41, 0x7F, 0x41, 0x00,// I       73
    0x20, 0x40, 0x41, 0x3F, 0x01,// J       74
    0x7F, 0x08, 0x14, 0x22, 0x41,// K       75
    0x7F, 0x40, 0x40, 0x40, 0x40,// L       76
    0x7F, 0x02, 0x04, 0x02, 0x7F,// M       77
    0x7F, 0x04, 0x08, 0x10, 0x7F,// N       78
    0x3E, 0x41, 0x41, 0x41, 0x3E,// O       79
    0x7F, 0x09, 0x09, 0x09, 0x06,// P       80
    0x3E, 0x41, 0x51, 0x21, 0x5E,// Q       81
    0x7F, 0x09, 0x19, 0x29, 0x46,// R       82
    0x46, 0x49, 0x49, 0x49, 0x31,// S       83
    0x01, 0x01, 0x7F, 0x01, 0x01,// T       84
    0x3F, 0x40, 0x40, 0x40, 0x3F,// U       85
    0x1F, 0x20, 0x40, 0x20, 0x1F,// V       86
    0x7F, 0x20, 0x18, 0x20, 0x7F,// W       87
    0x63, 0x14, 0x08, 0x14, 0x63,// X       88
    0x03, 0x04, 0x78, 0x04, 0x03,// Y       89
    0x61, 0x51, 0x49, 0x45, 0x43,// Z       90
    0x00, 0x00, 0x7F, 0x41, 0x41,// [       91
    0x02, 0x04, 0x08, 0x10, 0x20,// "\"     92
    0x41, 0x41, 0x7F, 0x00, 0x00,// ]       93
    0x04, 0x02, 0x01, 0x02, 0x04,// ^       94
    0x40, 0x40, 0x40, 0x40, 0x40,// _       95
    0x00, 0x01, 0x02, 0x04, 0x00,// `       96
    0x20, 0x54, 0x54, 0x54, 0x78,// a       97
    0x7F, 0x48, 0x44, 0x44, 0x38,// b       98
    0x38, 0x44, 0x44, 0x44, 0x20,// c       99
    0x38, 0x44, 0x44, 0x48, 0x7F,// d       100
    0x38, 0x54, 0x54, 0x54, 0x18,// e       101
    0x08, 0x7E, 0x09, 0x01, 0x02,// f       102
    0x08, 0x14, 0x54, 0x54, 0x3C,// g       103
    0x7F, 0x08, 0x04, 0x04, 0x78,// h       104
    0x00, 0x44, 0x7D, 0x40, 0x00,// i       105
    0x20, 0x40, 0x44, 0x3D, 0x00,// j       106
    0x00, 0x7F, 0x10, 0x28, 0x44,// k       107
    0x00, 0x41, 0x7F, 0x40, 0x00,// l       108
    0x7C, 0x04, 0x18, 0x04, 0x78,// m       109
    0x7C, 0x08, 0x04, 0x04, 0x78,// n       110
    0x38, 0x44, 0x44, 0x44, 0x38,// o       111
    0x7C, 0x14, 0x14, 0x14, 0x08,// p       112
    0x08, 0x14, 0x14, 0x18, 0x7C,// q       113
    0x7C, 0x08, 0x04, 0x04, 0x08,// r       114
    0x48, 0x54, 0x54, 0x54, 0x20,// s       115
    0x04, 0x3F, 0x44, 0x40, 0x20,// t       116
    0x3C, 0x40, 0x40, 0x20, 0x7C,// u       117
    0x1C, 0x20, 0x40, 0x20, 0x1C,// v       118
    0x3C, 0x40, 0x30, 0x40, 0x3C,// w       119
    0x44, 0x28, 0x10, 0x28, 0x44,// x       120
    0x0C, 0x50, 0x50, 0x50, 0x3C,// y       121
    0x44, 0x64, 0x54, 0x4C, 0x44,// z       122
    0x00, 0x08, 0x36, 0x41, 0x00,// {       123
    0x00, 0x00, 0x7F, 0x00, 0x00,// |       124
    0x00, 0x41, 0x36, 0x08, 0x00,// }       125
    // EXTRA CHARS
    0x08, 0x08, 0x2A, 0x1C, 0x08,// ->      
    0x08, 0x1C, 0x2A, 0x08, 0x08 // <-      
};

class DotMatrixDisplay {
    uint8_t cp, ncp, data, ndata;

    public:
        void setup() {
            //Serial.println("dotmatrixdisplay.setup");
            cp = CP_DEFAULT;
            data = DATA_DEFAULT;
            ncp = NCP_DEFAULT;
            ndata = NDATA_DEFAULT;

            // set negated outputs to always high
            pinMode(NCP, OUTPUT);
            pinMode(NDATA, OUTPUT);
            digitalWrite(NCP, ncp);
            digitalWrite(NDATA, ndata);

            // set outputs to default
            pinMode(CP, OUTPUT);
            pinMode(DATA, OUTPUT);
            digitalWrite(CP, cp);
            digitalWrite(DATA, data);
        }

        void step() {
            if (cp == HIGH) cp = LOW; else cp = HIGH;
            digitalWrite(NCP,  cp);
        }

        void setOn() {
            //Serial.println("dotmatrix.set_on");
            //Serial.print(1);
            digitalWrite(NDATA, HIGH);
        }

        void setOff() {
            //Serial.println("dotmatrix.set_off");
            //Serial.print(0);
            digitalWrite(NDATA, LOW);
        }

        void clear() {
            //Serial.println("dotmatrix.clear");
            digitalWrite(NDATA, LOW);
            for (int i=0;i<NB_COLS*NB_LINES*NB_DISP;++i) {
                step();
            }
        }

        void allOn() {
            //Serial.println("dotmatrix.all_on");
            digitalWrite(NDATA, HIGH);
            for (int i=0;i<NB_COLS*NB_LINES*NB_DISP;++i) {
                step();
            }
        }

        void writeByte(uint8_t c) {
            //Serial.println("write_byte");
            if ((1&(c >> 6)) == 1) setOn(); else setOff(); step();
            if ((1&(c >> 5)) == 1) setOn(); else setOff(); step();
            if ((1&(c >> 4)) == 1) setOn(); else setOff(); step();
            if ((1&(c >> 3)) == 1) setOn(); else setOff(); step();
            if ((1&(c >> 2)) == 1) setOn(); else setOff(); step();
            if ((1&(c >> 1)) == 1) setOn(); else setOff(); step();
            if ((1&(c >> 0)) == 1) setOn(); else setOff(); step();
            //Serial.print(" ");
            setOff();step(); // invisible bit
            //Serial.println();
            delayMicroseconds(200);
        }

} dotmatrix;

int set_buffer(uint8_t buffer[NB_DISP][NB_COLS], int* idx, int value) {
    buffer[(*idx)/(NB_COLS)][(*idx)%NB_COLS] = value;
    ++(*idx); 
    if (*idx > NB_COLS*NB_DISP) 
        return 0;
    return 1;
}

/** Function that generates a dotmatrix buffer from a text input
 * @param buffer is the framebuffer where to output the result
 * @param text is the text to put to the output
 * @param color is the color in which the result shall be (1 for red, 2 for green or 3 for orange)
 * @param left_pad and top_pad are empty pixels paddings to align the text
 * @return -1 if buffer is full, 
 * @return the size of the buffer that has been written
 */
int generate_text(uint8_t buffer[NB_DISP][NB_COLS], char* text, int left_pad, int top_pad) {
    //Serial.println("generate text");
    int idx = 0;
    // for each character of the text
    for (int8_t t_idx=0;t_idx<=strlen(text)-1;++t_idx) {
        if (text[t_idx] == '\n')
            idx = idx+(NB_COLS-(idx%NB_COLS));
        else {
            for (int c=0;c<=4;++c) {
                if (!set_buffer(buffer, &idx, (uint8_t)((Font5x7[text[t_idx]-32][c])))) return -1;
            }
            // add one column between chars
            if (!set_buffer(buffer, &idx, 0)) return -1;
        }
    }
    return 1;
}

class Buffered_DotMatrix {
    uint8_t frameBuffer[NB_DISP][NB_COLS];

    public:
        void update() {
            //Serial.println("update");
            for (int i=NB_DISP;i>=0;--i)
                for (int j=0;j<NB_COLS;++j)
                    dotmatrix.writeByte( frameBuffer[i][j]);
        }

        int store_text(char* text, int left_pad, int top_pad) {
            int ret;
            //Serial.println("store_text");
            clear();
            ret = generate_text(frameBuffer, text, left_pad, top_pad);
            return ret;
        }

        void clear() {
            //Serial.println("bufdotmat.clear");
            // set all framebuffer pixels to 0
            for (int i=0;i<NB_DISP;++i)
                for (int j=0;j<NB_COLS;++j)
                        frameBuffer[i][j] = 0;
        }

        void print_buffer() {
            for (int j=0;j<NB_COLS;++j) {
                for (int i=NB_DISP;i>=0;--i) {
                    if ((1&(frameBuffer[i][j] >> 6)) == 1) Serial.print(1); else Serial.print(' ');
                    if ((1&(frameBuffer[i][j] >> 5)) == 1) Serial.print(1); else Serial.print(' ');
                    if ((1&(frameBuffer[i][j] >> 4)) == 1) Serial.print(1); else Serial.print(' ');
                    if ((1&(frameBuffer[i][j] >> 3)) == 1) Serial.print(1); else Serial.print(' ');
                    if ((1&(frameBuffer[i][j] >> 2)) == 1) Serial.print(1); else Serial.print(' ');
                    if ((1&(frameBuffer[i][j] >> 1)) == 1) Serial.print(1); else Serial.print(' ');
                    if ((1&(frameBuffer[i][j] >> 0)) == 1) Serial.print(1); else Serial.print(' ');
                    Serial.print(" 0 | ");
                }
                Serial.println();
            }
        }

} bufdotmat;

#define BUFMAX 16*9
class SerialListener {
    int idx;
    bool textMode;
    char textBuffer[BUFMAX+1];

    public:
        void setup() {
            textMode=true;
            clear();
        }

        void clear() {
            for (int i=0;i<BUFMAX;++i) textBuffer[i] = ' ';
            textBuffer[0]='\0';
            idx=0;
        }

        void getControlChar(char c) {
            switch (c) {
                case '0':
                    textMode = !textMode;
                    Serial.println("binary mode");
                    break;
                case '1':
                    dotmatrix.setOff();
                    dotmatrix.step();
                    ++idx;
                    break;
                case '2':
                    dotmatrix.setOn();
                    dotmatrix.step();
                    ++idx;
                    break;
                case '3':
                    dotmatrix.clear();
                    bufdotmat.clear();
                    clear();
                    idx = 0;
                    break;
                case '4':
                    dotmatrix.allOn();
                    idx = 0;
                    break;
                case '5':
                    bufdotmat.store_text("\nHe who makes a\nbeast of himselfgets rid of the pain of being a\nman.\n\nDr Johnson", 0, 0);
                    bufdotmat.update();
                    idx = 0;
                    break;
                case '6':
                    bufdotmat.print_buffer();
                    break;
            }
        }

        void appendChar(char c) {
            // append a char to the buffer and update it
            int i = strlen(textBuffer);
            if (i == BUFMAX) {
                int j = 0;
                textBuffer[BUFMAX] = c;
                while (textBuffer[j] != '\0' and j < BUFMAX) {
                    textBuffer[j] = textBuffer[j+1];
                    ++j;
                }
                textBuffer[BUFMAX] = '\0';
            } else {
                textBuffer[i] = c;
                textBuffer[i+1] = '\0';
            }
        }

        boolean getChar() {
            if (! Serial.available())
                return false;
            char c = Serial.read();
            if (c == 27) {
                while (! Serial.available());
                getControlChar(Serial.read());
            } else if (!textMode)
                if (c == 32 || c == '0') { 
                    dotmatrix.setOff();
                    dotmatrix.step();
                } else {        
                    dotmatrix.setOn();
                    dotmatrix.step();
                }
            else if (c == '\r' || c == '\n') {
                int len = strlen(textBuffer);
                for (int i = 0; i<16-(len%16); ++i) appendChar(' ');
            } else if (c > 31 && c < 128) {
                appendChar(c);
                //Serial.print("DISP: ");
                Serial.println(textBuffer);
                bufdotmat.store_text(textBuffer,0,0);
                bufdotmat.update();
            }
            return true;
        }

} serial;

void setup() {
    Serial.begin(9600);
    Serial.println("STARTED");
    serial.setup();
    //Serial.println("setup");
    bufdotmat.clear();
    dotmatrix.setup();
    delay(1000);
    bufdotmat.store_text("\nHe who makes a\nbeast of himselfgets rid of the pain of being a\nman.\n\nDr Johnson", 0, 0);
    bufdotmat.update();
}

//bool started=LOW;
void loop() {
    serial.getChar();
}
