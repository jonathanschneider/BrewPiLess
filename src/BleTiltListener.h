#ifndef BleTiltListener_H
#define BleTiltListener_H
#include <Arduino.h>
#include <functional>

#include "Config.h"
#if SupportTiltHydrometer

#include "BleListener.h"


typedef enum _TiltColor{
    TiltColorRed=0,
    TiltColorGreen,
    TiltColorBlack,
    TiltColorPurple,
    TiltColorOrange,
    TiltColorBlue,
    TiltColorYellow,
    TiltColorPink,
    MaxTiltNumber,
    TiltColorInvalid
} TiltColor;

class TiltHydrometerInfo: public BleHydrometerDevice {
public:
    TiltHydrometerInfo(){}
    BleHydrometerDevice* duplicate(void){
        TiltHydrometerInfo* info= new TiltHydrometerInfo();

        info->gravity = this->gravity;
        info->temperature = this->temperature;
        info->rssi = this->rssi;
        info->color = this->color;
        return info;
    }
    uint16_t gravity;
    uint16_t temperature;
    int rssi;
    TiltColor color;
};


typedef std::function<void(TiltHydrometerInfo*)> TiltDataHandler;


class TiltListener:public BleDeviceListener {
public:
    TiltListener():_dataAvailableHandler(NULL),_targetColor(TiltColorInvalid){}

    void listen(TiltColor color,TiltDataHandler onData);
    // callbacks
    bool identifyDevice(NimBLEAdvertisedDevice*);
protected:
    TiltDataHandler _dataAvailableHandler;
    TiltHydrometerInfo _tiltInfo;
    TiltColor _targetColor;
};

class TiltScanner:public BleDeviceScanner {
public:
    TiltScanner(){}
    // callbacks
    BleHydrometerDevice* getDevice(NimBLEAdvertisedDevice*);
protected:
    TiltHydrometerInfo _tiltInfo;
};

extern TiltListener tiltListener;

#endif

#endif