
void FUNC_init_screen()
{
	/* setup function */
	if (!LCDML.FuncInit())
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("  The Ultimate"));
		lcd.setCursor(0, 1);
		lcd.print(F("  Aetz-Machine"));
	}

	/* end function for callback */
	if (LCDML.FuncEnd(0, 1, 1, 1, 1, 1)) /* (direct, up, down, left, right) */
	{
		/* do something bevor this function is closed */
	}
}

void FUNC_heater_temp()
{
	/* setup function */
	if (!LCDML.FuncInit())
	{
		HotPlateHeating();
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Target: "));
		lcd.print(Config.TargetTemp);
		lcd.print(F("C"));
		lcd.setCursor(0, 1);
		lcd.print(F("Current: "));
		lcd.print(TempHotPlate);
		lcd.print(F("C"));
		mills = millis();
	}

	lcd.setCursor(8, 0);
	lcd.print(Config.TargetTemp);
	lcd.print(F("C"));
	lcd.setCursor(9, 1);
	lcd.print(TempHotPlate);
	lcd.print(F("C"));
	if (Heating)
	{
		lcd.setCursor(15, 0);
		lcd.print(F("X"));
	}
	else
	{
		lcd.setCursor(15, 0);
		lcd.print(F(" "));
	}

	/* end function for callback */
	if (LCDML.FuncEnd(0, 1, 1, 1, 1, 1)) /* (direct, up, down, left, right) */
	{
		/* do something bevor this function is closed */
	}
}

void FUNC_back()
{

	LCDML.FuncInit();            /* setup function */

	LCDML.Button_quit();         /* quit button */

	LCDML.FuncEnd(1, 0, 0, 0, 0, 0); /* direct func end */
}

void FUNC_SetRightMaxPosition()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Set Right Pos."));
		lcd.setCursor(0, 1);
		lcd.print(F("Position: "));
		lcd.print(Config.RightMaxPosition);
		SwingToPosition(Config.RightMaxPosition, false);
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonUp())
		{
			LCDMenuLib_resetButtonUp();
			Config.RightMaxPosition++;
			lcd.setCursor(10, 1);
			lcd.print(Config.RightMaxPosition);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonDown())
		{
			LCDMenuLib_resetButtonDown();
			Config.RightMaxPosition--;
			lcd.setCursor(10, 1);
			lcd.print(Config.RightMaxPosition);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonEnter())
		{
			LCDMenuLib_resetButtonEnter();
			EEPROM_writeAnything(0, Config);
			SwingToPosition(Config.CenterPosition, false);
			LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
		}
		else
		{
			SwingServo.write(Config.RightMaxPosition);
		}
	}
}

void FUNC_SetLeftMaxPosition()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Set Left Pos."));
		lcd.setCursor(0, 1);
		lcd.print(F("Position: "));
		lcd.print(Config.LeftMaxPosition);
		SwingToPosition(Config.LeftMaxPosition, false);
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonUp())
		{
			LCDMenuLib_resetButtonUp();
			Config.LeftMaxPosition++;
			lcd.setCursor(10, 1);
			lcd.print(Config.LeftMaxPosition);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonDown())
		{
			LCDMenuLib_resetButtonDown();
			Config.LeftMaxPosition--;
			lcd.setCursor(10, 1);
			lcd.print(Config.LeftMaxPosition);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonEnter())
		{
			LCDMenuLib_resetButtonEnter();
			EEPROM_writeAnything(0, Config);
			SwingToPosition(Config.CenterPosition, false);
			LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
		}
		else
		{
			SwingServo.write(Config.LeftMaxPosition);
		}
	}
}

void FUNC_SetCenterPosition()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Set Center Pos."));
		lcd.setCursor(0, 1);
		lcd.print(F("Position: "));
		lcd.print(Config.CenterPosition);
		SwingToPosition(Config.CenterPosition, false);
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonUp())
		{
			LCDMenuLib_resetButtonUp();
			Config.CenterPosition++;
			lcd.setCursor(10, 1);
			lcd.print(Config.CenterPosition);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonDown())
		{
			LCDMenuLib_resetButtonDown();
			Config.CenterPosition--;
			lcd.setCursor(10, 1);
			lcd.print(Config.CenterPosition);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonEnter())
		{
			LCDMenuLib_resetButtonEnter();
			EEPROM_writeAnything(0, Config);
			LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
		}
		else
		{
			SwingServo.write(Config.CenterPosition);
		}

	}
}

void FUNC_SetSwingSpeed()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Set Swing Speed"));
		lcd.setCursor(0, 1);
		lcd.print(F("Speed: "));
		lcd.print(Config.SwingSpeed);
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonUp())
		{
			LCDMenuLib_resetButtonUp();
			Config.SwingSpeed++;
			lcd.setCursor(7, 1);
			lcd.print(Config.SwingSpeed);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonDown()) {
			LCDMenuLib_resetButtonDown();
			if (Config.SwingSpeed == 0)
				return;
			Config.SwingSpeed--;
			lcd.setCursor(7, 1);
			lcd.print(Config.SwingSpeed);
			lcd.print(F("   "));
		}
		if (LCDMenuLib_checkButtonEnter())
		{
			LCDMenuLib_resetButtonEnter();
			EEPROM_writeAnything(0, Config);
			LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
		}
	}
}

void FUNC_StartSwing()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		HotPlateHeating();
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Temp: "));
		lcd.print(TempHotPlate);
		lcd.print(F("C"));
		lcd.setCursor(0, 1);
		lcd.print(F("Position: "));
		lcd.print(SwingServo.read());
		mills = millis();
	}
	while (true)
	{
		SwingToPosition(Config.LeftMaxPosition, true);
		HotPlateHeating();
		lcd.setCursor(6, 0);
		lcd.print(TempHotPlate);
		lcd.print(F("C"));
		if (Heating)
		{
			lcd.setCursor(15, 0);
			lcd.print(F("X"));
		}
		else
		{
			lcd.setCursor(15, 0);
			lcd.print(F(" "));
		}

		delay(40);
		SwingToPosition(Config.RightMaxPosition, true);
		// Stop!
		if (LCDML.checkButtons())
		{
			if (LCDMenuLib_checkButtonEnter())
			{
				LCDMenuLib_resetButtonEnter();
				SwingToPosition(Config.CenterPosition, true);
				LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
				break;
			}
		}
		HotPlateHeating();
		lcd.setCursor(6, 0);
		lcd.print(TempHotPlate);
		lcd.print(F("C"));
		if (Heating)
		{
			lcd.setCursor(15, 0);
			lcd.print(F("X"));
		}
		else
		{
			lcd.setCursor(15, 0);
			lcd.print(F(" "));
		}
		delay(40);
	}
}

void FUNC_SetTargetTemp()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Set Heater Temp."));
		lcd.setCursor(0, 1);
		lcd.print(F("Temp: "));
		lcd.print(Config.TargetTemp);
		lcd.print(F("C"));
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonUp())
		{
			if (Config.TargetTemp < 90.00)
			{
				LCDMenuLib_resetButtonUp();
				Config.TargetTemp++;
				lcd.setCursor(6, 1);
				lcd.print(Config.TargetTemp);
				lcd.print(F("C  "));
			}
		}
		if (LCDMenuLib_checkButtonDown())
		{
			LCDMenuLib_resetButtonDown();
			//if (Config.TargetTemp > 40.00)
			//{
			Config.TargetTemp--;
			lcd.setCursor(6, 1);
			lcd.print(Config.TargetTemp);
			lcd.print(F("C  "));
			//}
		}
		if (LCDMenuLib_checkButtonEnter())
		{
			LCDMenuLib_resetButtonEnter();
			EEPROM_writeAnything(0, Config);
			LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
		}
	}
}

void FUNC_SetDisplayBrightness()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Display Brigth."));
		lcd.setCursor(0, 1);
		lcd.print(F("Bright: "));
		lcd.print(Config.DisplayBrightness);
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonUp())
		{
			if (Config.DisplayBrightness < 255)
			{
				LCDMenuLib_resetButtonUp();
				if ((Config.DisplayBrightness = Config.DisplayBrightness + 10) > 255)
				{
					Config.DisplayBrightness = 255;
				}
				analogWrite(_LCDMenuLib_LCD_backlight, Config.DisplayBrightness);
				lcd.setCursor(8, 1);
				lcd.print(Config.DisplayBrightness);
				lcd.print(F("  "));
			}
		}
		if (LCDMenuLib_checkButtonDown())
		{
			LCDMenuLib_resetButtonDown();
			if (Config.DisplayBrightness > 0)
			{
				if ((Config.DisplayBrightness = Config.DisplayBrightness - 10) < 0)
				{
					Config.DisplayBrightness = 0;
				}
				analogWrite(_LCDMenuLib_LCD_backlight, Config.DisplayBrightness);
				lcd.setCursor(8, 1);
				lcd.print(Config.DisplayBrightness);
				lcd.print(F("  "));
			}
		}
	}
	if (LCDMenuLib_checkButtonEnter())
	{
		LCDMenuLib_resetButtonEnter();
		EEPROM_writeAnything(0, Config);
		LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
	}
}

void FUNC_HeaterOnOff()
{
	if (!LCDML.FuncInit())
	{
		/* Init Function */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(F("Heater is "));

		if (HeatingEnabled)
		{
			lcd.print("On ");
		}
		else
		{
			lcd.print("Off");
		}

		lcd.setCursor(0, 1);
		lcd.print(F("<--To Switch-->"));
	}

	if (LCDML.checkButtons()) {
		if (LCDMenuLib_checkButtonLeft() || LCDMenuLib_checkButtonRight())
		{
			LCDMenuLib_resetButtonLeft();
			LCDMenuLib_resetButtonRight();
			HeatingEnabled = !HeatingEnabled;
			lcd.setCursor(10, 0);
			if (HeatingEnabled)
			{
				lcd.print("On ");
			}
			else
			{
				lcd.print("Off");
			}
		}
	}

	if (LCDMenuLib_checkButtonEnter())
	{
		LCDMenuLib_resetButtonEnter();
		LCDML.FuncEnd(1, 0, 0, 0, 0, 0);
	}
}







