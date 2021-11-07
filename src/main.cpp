#include <Arduino.h>

//toDO
/*
heartReate 
 avg
target heart rate 
diff to target heart rate 
*/
//int myInts[6];
//int myPins[] = {2, 4, 8, 3, 6};
//int mySensVals[6] = {2, 4, -8, 3, 2};
//char message[6] = "hello";

typedef struct
{
  int currentValue;
  int lastFiveValues[5] = {0, 0, 0, 0, 0};
  int avgLast5Seconds;

} heartrate_type;

heartrate_type heartrate; //= {1, {0, 0, 0, 0}, 1}

int targetHeartrate = 140;

int averageHeartrate(heartrate_type heartrate);
int readHeartrate();

void setup()
{
  //HeartRate heartRate;
  // put your setup code here, to run once:
  heartrate.currentValue = 0;
  for (byte i = 0; i < (sizeof(heartrate.lastFiveValues) / sizeof(heartrate.lastFiveValues[0])); i++)
  {
    heartrate.lastFiveValues[i] = 0;
  }
  heartrate.avgLast5Seconds = 0;
}

void loop()
{

  for (byte i = 0; i < ((sizeof(heartrate.lastFiveValues) / sizeof(heartrate.lastFiveValues[0])) - 1); i++)
  {
    heartrate.lastFiveValues[i + 1] = heartrate.lastFiveValues[i];
  }
  heartrate.lastFiveValues[0] = readHeartrate();

  heartrate.avgLast5Seconds = averageHeartrate((heartrate_type)heartrate);

  int diffTargetHearrateAndHeartrateAvgLast5Seconds = targetHeartrate - heartrate.avgLast5Seconds;

  Serial.println("Currenthearrate");
  Serial.println(heartrate.lastFiveValues[0]);
  Serial.println("targetHeartrate");
  Serial.println(targetHeartrate);

  Serial.println("difference  of TargetHearrate and HeartrateAvgLast5Seconds");
  Serial.println(diffTargetHearrateAndHeartrateAvgLast5Seconds);

  if (diffTargetHearrateAndHeartrateAvgLast5Seconds > 10)
  {
    Serial.println("Faster");
  }

  if (diffTargetHearrateAndHeartrateAvgLast5Seconds > -10)
  {
    Serial.println("Slower");
  }
  sleep(1);
}

int averageHeartrate(heartrate_type heartrate)
{
  int avg = 0;
  int sum = 0;
  // this for loop works correctly with an array of any type or size #byte 0-255
  int arrayCount = (sizeof(heartrate.lastFiveValues) / sizeof(heartrate.lastFiveValues[0]));

  for (byte i = 0; i < arrayCount; i++)
    sum += heartrate.lastFiveValues[i];

  avg = int(sum / arrayCount);

  return avg;
}

int readHeartrate()
{
  int heartrate = random(100, 140);
  return heartrate;
}