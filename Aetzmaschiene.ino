#include <SPI.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include "SimpleTimer.h"
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"

#define OW_MessurePin 12
#define HotPlateRelayPIN 13
#define SwingServoPIN 11
Servo SwingServo;
OneWire oneWire(OW_MessurePin);
DallasTemperature sensors(&oneWire);
double TempHotPlate = 0;
long mills = 0;
bool HeatingEnabled = true;
bool Heating = false;


struct ConfigModel
{
	bool IsConfigInit;
	int LeftMaxPosition;
	int RightMaxPosition;
	int CenterPosition;
	int SwingSpeed;
	double TargetTemp;
	int DisplayBrightness;
}Config;

/* settings for lcd */
#define _LCDMenuLib_LCD_cols             18
#define _LCDMenuLib_LCD_rows             2
/* pin settings */
#define _LCDMenuLib_LCD_rs               8
#define _LCDMenuLib_LCD_e                9
#define _LCDMenuLib_LCD_dat0             4
#define _LCDMenuLib_LCD_dat1             5
#define _LCDMenuLib_LCD_dat2             6
#define _LCDMenuLib_LCD_dat3             7 
#define _LCDMenuLib_LCD_backlight        10
#define _LCDMenuLib_LCD_rw				 0
/* lib config */
#define _LCDMenuLib_cfg_initscreen       0      /* 0=disable, 1=enable */
#define _LCDMenuLib_cfg_initscreen_time  0		/* 0=time disabled, >0 wait time in ms */
#define _LCDMenuLib_cfg_scrollbar		 0      /* 0=no scrollbar, 1=complex scrollbar, 2=easy scrollbar */
#define _LCDMenuLib_cfg_lcd_standard	 0      /* 0=HD44780 standard / 1=HD44780U standard */
#define _LCDMenuLib_cfg_press_time       200    /* button press time in ms */
/* menu element count - last element id */
#define _LCDMenuLib_cnt					 14
/* init lcdmenulib */
LCDMenuLib_init(_LCDMenuLib_cnt);

LCDMenuLib_element(0, Item, Item_1, "Start   Swing", FUNC_StartSwing);
LCDMenuLib_element(1, Item, Item_2, "Heater  Option", FUNC);
LCDMenuLib_element(2, Item_2, Item_2_1, "Check Temp", FUNC_heater_temp);
LCDMenuLib_element(3, Item_2, Item_2_2, "Heater On / Off", FUNC_HeaterOnOff);
LCDMenuLib_element(4, Item_2, Item_2_3, "Set Heater Temp", FUNC_SetTargetTemp);
LCDMenuLib_element(5, Item_2, Item_2_4, "<--Go Back", FUNC_back);
LCDMenuLib_element(6, Item, Item_3, "Swing   Option", FUNC);
LCDMenuLib_element(7, Item_3, Item_3_1, "Set Right Pos.", FUNC_SetRightMaxPosition);
LCDMenuLib_element(8, Item_3, Item_3_2, "Set Center Pos.", FUNC_SetCenterPosition);
LCDMenuLib_element(9, Item_3, Item_3_3, "Set Left Pos.", FUNC_SetLeftMaxPosition);
LCDMenuLib_element(10, Item_3, Item_3_4, "Set Swing Speed", FUNC_SetSwingSpeed);
LCDMenuLib_element(11, Item_3, Item_3_5, "<--Go Back", FUNC_back);
LCDMenuLib_element(12, Item, Item_4, "Diverse Option", FUNC);
LCDMenuLib_element(13, Item_4, Item_4_1, "Display Brigth.", FUNC_SetDisplayBrightness);
LCDMenuLib_element(14, Item_4, Item_4_5, "<--Go Back", FUNC_back);


LCDMenuLib_createMenu(_LCDMenuLib_cnt);

void setup()
{
	LCDMenuLib_setup(_LCDMenuLib_cnt);  /* Setup for LcdMenuLib */
	SwingServo.attach(SwingServoPIN);
	sensors.begin();
	sensors.setResolution(9);
	EEPROM_readAnything(0, Config);
	// Für das erste Initialisieren
	if (!Config.IsConfigInit)
	{
		Config = { true, 90, 90, 90, 20, 0.00, 255 };
	}

	pinMode(_LCDMenuLib_LCD_backlight, OUTPUT);
	pinMode(HotPlateRelayPIN, OUTPUT);

	analogWrite(_LCDMenuLib_LCD_backlight, Config.DisplayBrightness);
	SwingToPosition(Config.CenterPosition, false);
}

void loop()
{
	LCDMenuLib_control_analog();      /* lcd menu control - config in tab "LCDML_control" */
	LCDMenuLib_loop();
	if (millis() - mills > 1000)
	{
		HotPlateHeating();
		mills = millis();
	}
}

void HotPlateHeating()
{
	if (HeatingEnabled)
	{
		TempHotPlate = GetTemp();
		if (TempHotPlate < Config.TargetTemp)
		{
			digitalWrite(HotPlateRelayPIN, true);
			Heating = true;
		}
		else if (TempHotPlate >= Config.TargetTemp + 0.25)
		{
			digitalWrite(HotPlateRelayPIN, false);
			Heating = false;
		}
	}
	else
	{
		digitalWrite(HotPlateRelayPIN, false);
		Heating = false;
	}
}

double GetTemp()
{
	sensors.requestTemperatures();
	return sensors.getTempCByIndex(0);
}

void SwingToPosition(int TargetPosition, bool LCDUpdate)
{
	int Position = SwingServo.read();
	while (Position > TargetPosition)
	{
		Position--;
		SwingServo.write(Position);
		if (LCDUpdate)
		{
			lcd.setCursor(10, 1);
			lcd.print(Position);
			lcd.print(F("  "));
		}
		LCDMenuLib_control_analog();
		delay(Config.SwingSpeed);
	}

	while (Position < TargetPosition)
	{
		Position++;
		SwingServo.write(Position);
		if (LCDUpdate)
		{
			lcd.setCursor(10, 1);
			lcd.print(Position);
			lcd.print(F("  "));
		}
		LCDMenuLib_control_analog();
		delay(Config.SwingSpeed);
	}
}

