#include "WidgetAircondition.h"


WidgetAircondition::WidgetAircondition(uint8_t ucItem)
{
    _Item = ucItem;
    memset(pCmdSwitchTopic,0,sizeof(pCmdSwitchTopic));
    memset(pDataStatusTopic,0,sizeof(pDataStatusTopic));
    sprintf(pCmdSwitchTopic,"channel/aircondition_%d/cmd/mode",_Item);
    sprintf(pDataStatusTopic,"channel/aircondition_%d/data/status",_Item);
}

WidgetAircondition::~WidgetAircondition()
{
}

void WidgetAircondition::begin(void (*UserCallBack)(void))
{
    _EventCb = UserCallBack;
    IntoRobot.subscribe(pCmdSwitchTopic, NULL, this);
}

int  WidgetAircondition::getMode(void)
{
    return _mode;
}

int  WidgetAircondition::getTemperature(void)
{
    return _temperature;
}

char WidgetAircondition::getAirconditionSwitch(void)
{
    return _switchKey;
}

void WidgetAircondition::control(uint8_t ucPin, uint8_t ucVal)
{
    pinMode(ucPin,OUTPUT);
    digitalWrite(ucPin, ucVal);
    IntoRobot.publish(pDataStatusTopic,1);
}

void WidgetAircondition::widgetBaseCallBack(uint8_t *payload, uint32_t len)
{
    if(payload == NULL) return;
    if(!jsonGetValue(payload,"mode",_mode)) return;
    if(!jsonGetValue(payload,"temp",_temperature)) return;
    if(!jsonGetValue(payload,"switch",_switchKey)) return;

    IntoRobot.publish(pDataStatusTopic,1);
    _EventCb();
}
