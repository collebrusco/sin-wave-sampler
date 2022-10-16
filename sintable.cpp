#include <iostream>
#include <cmath>
using namespace std;

#define SAMPLE_FORM ((A * (sin(((2*3.14159265) * i) / samples) + 1)) + min)

uint32_t fround(float a){
	uint32_t res = a;
	if ((a - res) > 0.499){res++;}
	return res;
}

uint8_t *Sinusoid(uint32_t min, uint32_t max, uint32_t samples){
    if ((min < 0) || (max & 0xFFFFFF00)){cout << "ERROR: min or max input out of bounds! unsigned 8-bit ints only! crashing...\n";return NULL;}	
    float A = (((float)(max - min)) / 2.0f);
    uint8_t *table = new uint8_t[samples];
//    cout << "A = " << A << "\n";
    for(int i = 0; i < samples;i++){
	float curr = SAMPLE_FORM;
//	cout << "float version of entry " << i << ": " << curr << "\n";
        table[i] = fround(curr);
    }
    return table;
}

int main(){
    uint32_t min, max, samples;
    cout << "Enter min, max, and num samples in that order\nseparate w spaces, only unsigned 8 bit ints allowed\nso minimum min is 0, max max is 255\n";
    cin >> min >> max >> samples;
    uint8_t* table = Sinusoid(min,max,samples);
    string t = "const uint8_t SinTable[";
    t += to_string(samples);
    t += "]={";
    for (int i = 0; i < (samples - 1);i++){
        t += to_string(table[i]);
        t += ", ";
    }
    t += to_string(table[samples-1]);
    t += "};";

    cout << t << "\n\n";
    cout << "ROM Table printed above, copy/paste into C/C++ program as needed\n";
    delete table;

    return 0;
}