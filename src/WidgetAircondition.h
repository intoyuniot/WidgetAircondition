#ifndef WIDGET_AIRCONDITION_H_
#define WIDGET_AIRCONDITION_H_

#include "application.h"


#define   ON       1
#define   OFF      0
#define   NONE    -1


class WidgetAircondition : public WidgetBaseClass
{
    public:
        WidgetAircondition(uint8_t ucItem = 0);
        ~WidgetAircondition();
        void begin(void (*UserCallBack)(void) = NULL);
        int  getMode(void);
        int  getTemperature(void);
        char getAirconditionSwitch(void);
        void control(uint8_t ucPin, uint8_t ucVal);

    private:
        char pCmdSwitchTopic[64];
        char pDataStatusTopic[64];
        char _switchKey = NONE;
        int  _mode;
        int  _temperature;
        uint8_t _Item = 0;
        void (*_EventCb)(void);
        void widgetBaseCallBack(uint8_t *payload, uint32_t len);
};

#endif
