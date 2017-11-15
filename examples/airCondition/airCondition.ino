/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 空调控制：

 格力遥控器编码格式

 ** head1_tab 35bit sep1_tab 32bit end1_tab  head2_tab 35bit sep2_tab 32bit end2_tab **

 35bit数据1
 32bit数据(后四位校验1)

 35bit数据1(重复)
 32bit数据(后四位校验2)

 所需器件:

 */

#include <WidgetAircondition.h>

WidgetAircondition airCondition = WidgetAircondition();

#define IR_PIN_PWM  A0


/***************head date******************/
int head1_tab[]={9000,4500};
int sep1_tab[]={600,20000};
int end1_tab[]={600,40000};

int head2_tab[]={9000,4500};
int sep2_tab[]={600,20000};
int end2_tab[]={600,600};

int one_tab[]={600,1600};
int zero_tab[]={600,600};

/****************************************/

int power_on_22_tab[]={\
    /*35bit*/1,0,0,1,0,0,0,0,/**/0,1,1,0/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,1,0,1/**/,\
        /*35bit*/1,0,0,1,0,0,0,0,/**/0,1,1,0/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,0,0,1/**/,\
};

int power_on_23_tab[]={\
    /*35bit*/1,0,0,1,0,0,0,0,/**/1,1,1,0/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/0,0,1,1/**/,\
        /*35bit*/1,0,0,1,0,0,0,0,/**/1,1,1,0/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/0,1,0,1/**/,\
};

int power_on_24_tab[]={\
    /*35bit*/1,0,0,1,0,0,0,0,/**/0,0,0,1/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,0,1,1/**/,\
        /*35bit*/1,0,0,1,0,0,0,0,/**/0,0,0,1/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,1,0,1/**/,\
};

int power_on_25_tab[]={\
    /*35bit*/1,0,0,1,0,0,0,0,/**/1,0,0,1/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/0,1,1,1/**/,\
        /*35bit*/1,0,0,1,0,0,0,0,/**/1,0,0,1/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/0,0,1,1/**/,\
};

int power_on_26_tab[]={\
    /*35bit*/1,0,0,1,0,0,0,0,/**/0,1,0,1/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,1,1,1/**/,\
        /*35bit*/1,0,0,1,0,0,0,0,/**/0,1,0,1/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,0,1,1/**/,\
};

int power_off_22_tab[]={\
    /*35bit*/1,0,0,0,0,0,0,0,/**/0,1,1,0/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,1,0,0/**/,\
        /*35bit*/1,0,0,0,0,0,0,0,/**/0,1,1,0/**/,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,\
        /*32bit*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/**/1,0,0,0/**/,\
};


void ir_init()
{
    pinMode(IR_PIN_PWM,OUTPUT);
    analogWriteAndSetF(IR_PIN_PWM,0,379*100); // 占空比值 0 - 255 频率 0低电平
}


void ir_send(int *p_tab,int size_tab)
{
    if((p_tab==NULL) ||(size_tab%2 != 0))
    {
        IntoRobot.printf("error:send_ir bad param \r\n");
        return;
    }

    int i;

    for(i=0;i<size_tab;i+=2)
    {
        analogWriteAndSetF(IR_PIN_PWM,85,379*100); // 占空比值 0 - 255 频率500Hz
        delayMicroseconds(p_tab[i]);
        analogWriteAndSetF(IR_PIN_PWM,0,379*100); // 占空比值 0 - 255 频率500Hz
        delayMicroseconds(p_tab[i+1]);
    }
}


#define IR_SEND(n) ir_send(n,sizeof(n)/sizeof((n)[0]))


void data_send(int dat)
{
    if(dat==1)
    {
        IR_SEND(one_tab);
    }else if(dat==0)
    {
        IR_SEND(zero_tab);
    }else
    {
        IntoRobot.printf("error:data_send bad param \r\n");
    }
}

void all_data_send(int *p_tab,int size_tab)
{
    if((p_tab==0)||(size_tab!=134))
    {
        IntoRobot.printf("error:send_ir bad param \r\n");
        return;
    }


    int i;

    IR_SEND(head1_tab);
    for(i=0;i<35;i++)
    {
        data_send(p_tab[i]);
    }

    IR_SEND(sep1_tab);
    for(i=35;i<67;i++)
    {
        data_send(p_tab[i]);
    }

    IR_SEND(end1_tab);


    IR_SEND(head2_tab);
    for(i=67;i<102;i++)
    {
        data_send(p_tab[i]);
    }

    IR_SEND(sep2_tab);
    for(i=102;i<134;i++)
    {
        data_send(p_tab[i]);
    }

    IR_SEND(end2_tab);

}


#define ALL_DATA_SEND(n) all_data_send(n,sizeof(n)/sizeof((n)[0]))


int  AirCondition_temprature = 24;
boolean  AirCondition_switch = 0;


void AirConditionSwitchCb(void)
{
    AirCondition_temprature = airCondition.getTemperature();
    AirCondition_switch = (boolean)(airCondition.getAirconditionSwitch());

    if(AirCondition_switch==0)
    {
        ALL_DATA_SEND(power_off_22_tab);
        ALL_DATA_SEND(power_off_22_tab);
    }
    else
    {
        if(AirCondition_temprature==22)
        {
            ALL_DATA_SEND(power_on_22_tab);
            ALL_DATA_SEND(power_on_22_tab);
        }
        else if(AirCondition_temprature==23)
        {
            ALL_DATA_SEND(power_on_23_tab);
            ALL_DATA_SEND(power_on_23_tab);
        }
        else if(AirCondition_temprature==24)
        {
            ALL_DATA_SEND(power_on_24_tab);
            ALL_DATA_SEND(power_on_24_tab);
        }
        else if(AirCondition_temprature==25)
        {
            ALL_DATA_SEND(power_on_25_tab);
            ALL_DATA_SEND(power_on_25_tab);
        }
        else if(AirCondition_temprature==26)
        {
            ALL_DATA_SEND(power_on_26_tab);
            ALL_DATA_SEND(power_on_26_tab);
        }
    }
}


void setup()
{
    airCondition.begin(AirConditionSwitchCb);
}

void loop()
{

}
