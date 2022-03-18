#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

typedef unsigned char uchar, uint8;
typedef signed char schar, int8;
typedef unsigned short ushort, uint16;
typedef short int16;
typedef unsigned int uint;
typedef unsigned long ulong;
#if UINT_MAX >= 0xFFFFFFFF
typedef int int32;
typedef unsigned int uint32;
#else
typedef long int32;
typedef unsigned long uint32;
#endif
typedef long long int64;
typedef unsigned long long uint64;

typedef struct
{
  double x, y;
} tComplex;

tComplex complexAdd(const tComplex* a, const tComplex* b)
{
  tComplex c;
  c.x = a->x + b->x;
  c.y = a->y + b->y;
  return c;
}

tComplex complexMul(const tComplex* a, const tComplex* b)
{
  tComplex c;
  c.x = a->x * b->x - a->y * b->y;
  c.y = a->x * b->y + a->y * b->x;
  return c;
}

void dft(tComplex out[], const tComplex in[], size_t n, int direction)
{
  size_t k, i;
  for (k = 0; k < n; k++)
  {
    tComplex r = { 0, 0 }, e;
    for (i = 0; i < n; i++)
    {
      e.x = cos(-2 * direction * M_PI / n * ((double)k - n / 2) * ((double)i - n / 2));
      e.y = sin(-2 * direction * M_PI / n * ((double)k - n / 2) * ((double)i - n / 2));
      e = complexMul(&e, &in[i]);
      r = complexAdd(&r, &e);
    }
    out[k] = r;
  }
}

#define FILTER_LENGTH 64

typedef struct tTx
{
  enum
  {
    stSendingOnes,
    stSendingData
  } State;

  uint SampleRate;
  uint OnesFreq;
  uint ZeroesFreq;
  uint BitRate;

  uint32 SampleCnt;
  uint BitSampleCnt;
  uint Data;
  uint DataLeft;

  double Phase;
  double PhaseIncrement;

  uint (*pTxGetDataCallBack)(struct tTx*, uint8*);
} tTx;

void TxInit(tTx* pTx,
            uint SampleRate,
            uint (*pTxGetDataCallBack)(tTx*, uint8*))
{
  memset(pTx, 0, sizeof(*pTx));
  pTx->State = stSendingOnes;
  pTx->SampleRate = SampleRate;
  pTx->OnesFreq = 1300;
  pTx->ZeroesFreq = 2100;
  pTx->BitRate = 1200;
  pTx->pTxGetDataCallBack = pTxGetDataCallBack;

  pTx->SampleCnt = 0;
  pTx->BitSampleCnt = pTx->SampleRate;
  pTx->Data = 0;
  pTx->DataLeft = 0;
  pTx->Phase = 0.0;
  pTx->PhaseIncrement = 2 * M_PI * pTx->OnesFreq / pTx->SampleRate;
}

int16 TxGetSample(tTx* pTx)
{
  int16 sample;

  if (pTx->State == stSendingOnes &&
      pTx->SampleCnt >= pTx->SampleRate)
  {
    // Sent 1 second worth of 1's, can now send data
    pTx->State = stSendingData;
  }

  if (pTx->State == stSendingData &&
      pTx->BitSampleCnt >= pTx->SampleRate)
  {
    // Another data bit can now be sent
    uint8 d;

    pTx->BitSampleCnt -= pTx->SampleRate;

    if (!pTx->DataLeft)
    {
      // Get the next data byte (if any)
      if (pTx->pTxGetDataCallBack(pTx, &d) != 0)
      {
        pTx->Data = d & 0xFF;
        pTx->Data |= 1 << 8; // insert the stop bit
        pTx->Data <<= 1; // insert the start bit
        pTx->DataLeft = 10;
      }
      else
      {
        pTx->Data = 0x3FF; // no data, send 10 1's
        pTx->DataLeft = 10;
      }
    }

    // Extract the next data bit to send
    d = pTx->Data & 1;
    pTx->Data >>= 1;
    pTx->DataLeft--;

    // Choose the appropriate frequency for 0 and 1
    if (d)
    {
      pTx->PhaseIncrement = 2 * M_PI * pTx->OnesFreq / pTx->SampleRate;
    }
    else
    {
      pTx->PhaseIncrement = 2 * M_PI * pTx->ZeroesFreq / pTx->SampleRate;
    }
  }

  // Generate the next sample, advance the generator's phase
  sample = (int16)(16000 * cos(pTx->Phase));
  pTx->Phase += pTx->PhaseIncrement;
  if (pTx->Phase >= 2 * M_PI)
  {
    pTx->Phase -= 2 * M_PI;
  }

  if (pTx->State == stSendingData)
  {
    pTx->BitSampleCnt += pTx->BitRate;
  }

  pTx->SampleCnt++;

  return sample;
}

typedef struct tRx
{
  enum
  {
    stCarrierLost,
    stCarrierDetected,
    stReceivingData
  } State;

  uint SampleRate;
  uint OnesFreq;
  uint ZeroesFreq;
  uint MidFreq;
  uint BitRate;

  uint32 SampleCnt;
  uint BitSampleCnt;
  uint Data;

  double Phase;
  double PhaseIncrement;

  tComplex Filter[FILTER_LENGTH];
  double Delay[FILTER_LENGTH];

  double LastAngle;
  int LastDelta;
  int32 Deltas;

  int32 CarrierAngle;
  int32 CarrierCnt;

  double LongAvgPower;
  double ShortAvgPower;

  void (*pRxGetDataCallBack)(struct tRx*, uint8);
} tRx;

void RxInit(tRx* pRx,
            uint SampleRate,
            void (*pRxGetDataCallBack)(struct tRx*, uint8))
{
  tComplex tmp[FILTER_LENGTH];
  uint i;

  memset(pRx, 0, sizeof(*pRx));
  pRx->State = stCarrierLost;
  pRx->SampleRate = SampleRate;
  pRx->OnesFreq = 1300;
  pRx->ZeroesFreq = 2100;
  pRx->MidFreq = (pRx->OnesFreq + pRx->ZeroesFreq) / 2;
  pRx->BitRate = 1200;
  pRx->pRxGetDataCallBack = pRxGetDataCallBack;

  pRx->SampleCnt = 0;
  pRx->BitSampleCnt = 0;
  pRx->Data = 0x3FF;
  pRx->Phase = 0.0;
  pRx->PhaseIncrement = 2 * M_PI * pRx->MidFreq / pRx->SampleRate;
  pRx->LastAngle = 0.0;
  pRx->LastDelta = 0;
  pRx->Deltas = 0;
  pRx->CarrierAngle = 0;
  pRx->CarrierCnt = 0;
  pRx->LongAvgPower = 0.0;
  pRx->ShortAvgPower = 0.0;

  for (i = 0; i < FILTER_LENGTH; i++)
  {
    pRx->Delay[i] = 0.0;
  }

  for (i = 0; i < FILTER_LENGTH; i++)
  {
    if (i == 0) // w < 0 (min w)
    {
      pRx->Filter[i].x = 0;
      pRx->Filter[i].y = 0;
    }
    else if (i < FILTER_LENGTH / 2) // w < 0
    {
      pRx->Filter[i].x = 0;
      pRx->Filter[i].y = 0;
    }
    else if (i == FILTER_LENGTH / 2) // w = 0
    {
      pRx->Filter[i].x = 0;
      pRx->Filter[i].y = 0;
    }
    else if (i > FILTER_LENGTH / 2) // w > 0
    {
      pRx->Filter[i].x = 0;
      pRx->Filter[i].y = -1;

      // Extra filter to combat channel noise
      if (i - FILTER_LENGTH / 2 < 875UL * FILTER_LENGTH / pRx->SampleRate ||
          i - FILTER_LENGTH / 2 > (2350UL * FILTER_LENGTH + pRx->SampleRate - 1) / pRx->SampleRate)
      {
        pRx->Filter[i].y = 0;
      }
    }
  }

  memcpy(tmp, pRx->Filter, sizeof(tmp));
  dft(pRx->Filter, tmp, FILTER_LENGTH, -1);
}

#define RX_VERBOSE 0
void RxGetSample(tRx* pRx, int16 Sample)
{
  tComplex s = { 0.0, 0.0 }, ss;
  double angle;
  uint i;
  int delta;
  double pwr;

  // Insert the sample into the delay line
  memmove(&pRx->Delay[0], &pRx->Delay[1], sizeof(pRx->Delay) - sizeof(pRx->Delay[0]));
  pRx->Delay[FILTER_LENGTH - 1] = Sample;

  // Get the next analytic signal sample by applying Hilbert transform/filter
  for (i = 0; i < FILTER_LENGTH; i++)
  {
    s.x += pRx->Delay[i] * pRx->Filter[FILTER_LENGTH - 1 - i].x;
    s.y += pRx->Delay[i] * pRx->Filter[FILTER_LENGTH - 1 - i].y;
  }

  // Frequency shift by MidFreq down
  ss.x = cos(-pRx->Phase);
  ss.y = sin(-pRx->Phase);
  s = complexMul(&s, &ss);
  pRx->Phase += pRx->PhaseIncrement;
  if (pRx->Phase >= 2 * M_PI)
  {
    pRx->Phase -= 2 * M_PI;
  }

  // Calculate signal power
  pwr = (s.x * s.x + s.y * s.y) / 32768 / 32768;
  pRx->LongAvgPower *= 1 - pRx->BitRate / (pRx->SampleRate * 8.0 * 8);
  pRx->LongAvgPower += pwr;
  pRx->ShortAvgPower *= 1 - pRx->BitRate / (pRx->SampleRate * 8.0);
  pRx->ShortAvgPower += pwr;

#if 0
  printf("LongAvgPower:%f ShortAvgPower:%f\n", pRx->LongAvgPower, pRx->ShortAvgPower);
#endif

  // Disconnect if the signal power changes abruptly.
  if (pRx->State != stCarrierLost &&
      pRx->LongAvgPower > pRx->ShortAvgPower * 8 * 8)
  {
    // N.B. The receiver may have received a few extra (garbage) bytes
    // while demodulating the abruptly changed signal.
    // Prefixing data with its size or using a more advanced protocol
    // may be a good solution to this little problem.
    pRx->State = stCarrierLost;
    pRx->BitSampleCnt = 0;
    pRx->Data = 0x3FF;
    pRx->Phase = 0.0;
    pRx->LastAngle = 0.0;
    pRx->LastDelta = 0;
    pRx->Deltas = 0;
    pRx->CarrierAngle = 0;
    pRx->CarrierCnt = 0;
  }

  // Get the phase angle from the analytic signal sample
  angle = (fpclassify(s.x) == FP_ZERO && fpclassify(s.y) == FP_ZERO) ?
    0.0 : 180 / M_PI * atan2(s.y, s.x);
  // Calculate the phase angle change and force it to the -PI to +PI range
  delta = (int)(360.5 + angle - pRx->LastAngle) % 360;
  if (delta > 180) delta -= 360;

  if (pRx->State == stCarrierLost)
  {
    // Accumulate the phase angle change to see if we're receiving 1's
    pRx->CarrierAngle += delta;
    pRx->CarrierCnt++;

    // Check whether or not the phase corresponds to 1's
    if (delta < 0)
    {
      if (pRx->CarrierCnt >= pRx->SampleRate / pRx->OnesFreq * 8)
      {
        double ph = (double)pRx->CarrierAngle / pRx->CarrierCnt;
#if RX_VERBOSE
        printf("ca:%5ld, cc:%4ld, ca/cc:%4ld\n",
               (long)pRx->CarrierAngle,
               (long)pRx->CarrierCnt,
               (long)(pRx->CarrierAngle / pRx->CarrierCnt));
#endif
        // Frequency tolerance is +/-16 Hz per the V.23 spec
        if (ph < (pRx->OnesFreq - 17.0 - pRx->MidFreq) * 360.0 / pRx->SampleRate ||
            ph > (pRx->OnesFreq + 17.0 - pRx->MidFreq) * 360.0 / pRx->SampleRate)
        {
          goto BadCarrier;
        }
      }
    }
    else
    {
BadCarrier:
      // Phase doesn't correspond to 1's
      pRx->CarrierAngle = 0.0;
      pRx->CarrierCnt = 0;
    }

    if (pRx->CarrierCnt >= pRx->SampleRate / 2 + pRx->SampleRate / 4)
    {
      // 0.75 seconds worth of 1's have been detected, ready to receive data

      // Adjust MidFreq to compensate for the DAC and ADC sample rate difference
      double f1 = (double)pRx->CarrierAngle / pRx->CarrierCnt / 360 * pRx->SampleRate + pRx->MidFreq;
      pRx->MidFreq = (uint)(pRx->MidFreq * f1 / pRx->OnesFreq);
      pRx->PhaseIncrement = 2 * M_PI * pRx->MidFreq / pRx->SampleRate;
#if RX_VERBOSE
      printf("f1:%u, new MidFreq:%u\n", (uint)f1, pRx->MidFreq);
#endif
      pRx->State = stCarrierDetected;
    }
  }
  else
  {
    // Detect frequency changes (transitions between 0's and 1's)
    int freqChange = ((int32)pRx->LastDelta * delta < 0 || pRx->LastDelta && !delta);
    int reAddDelta = 0;

#if RX_VERBOSE
    printf("%6lu: delta:%4d freqChange:%d BitSampleCnt:%u\n",
           (ulong)pRx->SampleCnt,
           delta,
           freqChange,
           pRx->BitSampleCnt);
#endif

    // Synchronize with 1<->0 transitions
    if (freqChange)
    {
      if (pRx->BitSampleCnt >= pRx->SampleRate / 2)
      {
        pRx->BitSampleCnt = pRx->SampleRate;
        pRx->Deltas -= delta;
        reAddDelta = 1;
      }
      else
      {
        pRx->BitSampleCnt = 0;
        pRx->Deltas = 0;
      }
    }

    // Accumulate analytic signal phase angle changes
    // (positive for 0, negative for 1)
    pRx->Deltas += delta;

    if (pRx->BitSampleCnt >= pRx->SampleRate)
    {
      // Another data bit has accumulated
      pRx->BitSampleCnt -= pRx->SampleRate;

#if RX_VERBOSE
      printf("bit: %u\n", pRx->Deltas < 0);
#endif

      pRx->Data >>= 1;
      pRx->Data |= (pRx->Deltas < 0) << 9;
      pRx->Deltas = delta * reAddDelta;

      if ((pRx->Data & 0x201) == 0x200)
      {
        // Start and stop bits have been detected
        if (pRx->State == stCarrierDetected)
        {
          pRx->State = stReceivingData;
        }
        pRx->Data = (pRx->Data >> 1) & 0xFF;
        pRx->pRxGetDataCallBack(pRx, (uint8)pRx->Data);

#if RX_VERBOSE
        printf("byte: 0x%02X ('%c')\n",
               pRx->Data,
               (pRx->Data >= 0x20 && pRx->Data <= 0x7F) ? pRx->Data : '?');
#endif

        pRx->Data = 0x3FF;
      }
    }

    pRx->BitSampleCnt += pRx->BitRate;
  }

  pRx->LastAngle = angle;
  pRx->LastDelta = delta;
  pRx->SampleCnt++;
}

typedef struct
{
  tTx Tx;
  FILE* DataFile;
  int CountDown;
} tTxTest;

uint TxGetDataCallBack(tTx* pTx, uint8* pTxData)
{
  tTxTest* pTxTest = (tTxTest*)pTx;
  uchar c;

  if (pTxTest->CountDown)
  {
    pTxTest->CountDown--;
    return 0;
  }

  if (fread(&c, 1, 1, pTxTest->DataFile) != 1)
  {
    pTxTest->CountDown = 20;
    return 0;
  }

  *pTxData = c;
  return 1;
}

int testTx(uint SampleRate,
           double NoiseLevel,
           const char* DataFileName,
           const char* AudioFileName)
{
  FILE *fData = NULL, *fAudio = NULL;
  int err = EXIT_FAILURE;
  tTxTest txTest;

  if ((fData = fopen(DataFileName, "rb")) == NULL)
  {
    printf("Can't open file \"%s\"\n", DataFileName);
    goto Exit;
  }

  if ((fAudio = fopen(AudioFileName, "wb")) == NULL)
  {
    printf("Can't create file \"%s\"\n", AudioFileName);
    goto Exit;
  }

  txTest.DataFile = fData;
  txTest.CountDown = 0;

  TxInit(&txTest.Tx,
         SampleRate,
         &TxGetDataCallBack);

  do
  {
    int16 sample = TxGetSample(&txTest.Tx);
    if (txTest.CountDown > 1 && txTest.CountDown <= 10)
    {
#if 0 // Enable this code to test disconnecting.
      // Finish with silence.
      sample = 0;
#endif
    }
    sample += (rand() - (int)RAND_MAX / 2) * NoiseLevel * 16000 / (RAND_MAX / 2);
    fwrite(&sample, 1, sizeof(sample), fAudio);
  } while (txTest.CountDown != 1); // Drain all data-containing samples

  err = EXIT_SUCCESS;

Exit:

  if (fData != NULL) fclose(fData);
  if (fAudio != NULL) fclose(fAudio);

  return err;
}

typedef struct
{
  tRx Rx;
  FILE* DataFile;
} tRxTest;

void RxGetDataCallBack(tRx* pRx, uint8 RxData)
{
  tRxTest* pRxTest = (tRxTest*)pRx;
  uchar c = RxData;
  fwrite(&c, 1, 1, pRxTest->DataFile);
}

int testRx(uint SampleRate,
           const char* AudioFileName,
           const char* DataFileName)
{
  uint lastState;
  FILE *fAudio = NULL, *fData = NULL;
  int err = EXIT_FAILURE;
  tRxTest rxTest;

  if ((fAudio = fopen(AudioFileName, "rb")) == NULL)
  {
    printf("Can't open file \"%s\"\n", AudioFileName);
    goto Exit;
  }

  if ((fData = fopen(DataFileName, "wb")) == NULL)
  {
    printf("Can't create file \"%s\"\n", DataFileName);
    goto Exit;
  }

  rxTest.DataFile = fData;

  RxInit(&rxTest.Rx,
         SampleRate,
         &RxGetDataCallBack);

  for (;;)
  {
    int16 sample;

    if (fread(&sample, 1, sizeof(sample), fAudio) != sizeof(sample))
    {
      if (rxTest.Rx.State != stCarrierLost) goto NoCarrier;
      break;
    }

    lastState = rxTest.Rx.State;
    RxGetSample(&rxTest.Rx, sample);

    if (rxTest.Rx.State != lastState && rxTest.Rx.State == stCarrierDetected)
    {
      printf("\nCONNECT %u\n\n", rxTest.Rx.BitRate);
    }

    if (rxTest.Rx.State != lastState && rxTest.Rx.State == stCarrierLost)
    {
NoCarrier:
      printf("\n\nNO CARRIER\n");
      break;
    }
  }

  err = EXIT_SUCCESS;

Exit:

  if (fAudio != NULL) fclose(fAudio);
  if (fData != NULL) fclose(fData);

  return err;
}

int main(int argc, char* argv[])
{
  uint sampleRate;
  double noiseLevel;

  if (argc < 2 ||
      !strcasecmp(argv[1], "-help") ||
      !strcasecmp(argv[1], "/help") ||
      !strcasecmp(argv[1], "-?") ||
      !strcasecmp(argv[1], "/?"))
  {
Usage:
    printf("Usage:\n\n"
           "  %s tx <sample rate> <noise level> <data input file> <PCM output file>\n"
           "  %s rx <sample rate> <PCM input file> <data output file>\n",
           argv[0],
           argv[0]);
    return 0;
  }

  if (!strcasecmp(argv[1], "tx") &&
      argc == 6 &&
      sscanf(argv[2], "%u", &sampleRate) == 1 &&
      sscanf(argv[3], "%lf", &noiseLevel) == 1)
  {
    return testTx(sampleRate, noiseLevel, argv[4], argv[5]);
  }
  else if (!strcasecmp(argv[1], "rx") &&
           argc == 5 &&
           sscanf(argv[2], "%u", &sampleRate) == 1)
  {
    return testRx(sampleRate, argv[3], argv[4]);
  }
  else
  {
    goto Usage;
  }
}

