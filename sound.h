#define SAMPLERATE 16000
#define BARS 160
#define SIZE 500
//#define SDEBUG 

typedef struct
{
	char chunkID[4];
	int chunkSize;
	char format[4];
	char subchunkID[4];
	int subchunkSize;
	short audioFormat;
	short numChannels;
	int sampleRate;
	int byteRate;
	short blockAgain;
	short bitsPerSample;
	char subchunk2ID[4];
	int subchunk2Size;
}WAVheader;

WAVheader readwavhdr(FILE *);
void displayWAVhdr(WAVheader h);
void WAVdata(WAVheader, FILE *);
