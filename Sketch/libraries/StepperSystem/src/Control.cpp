
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arduino.h>

#include "Control.h"
#include "Lcd.h"

#ifdef _MSC_VER
#include "HelpParser.h"
#endif

////////////////////////////////////////////////////////////

template<> CControl* CSingleton<CControl>::_instance = NULL;

////////////////////////////////////////////////////////

CControl::CControl()
{
	_bufferidx = 0;
	_pause = false;

	_oldStepperEvent = NULL;
}

////////////////////////////////////////////////////////////

void CControl::Init()
{
	CStepper::GetInstance()->Init();
	CStepper::GetInstance()->AddEvent(MyStepperEvent, this, _oldStepperEvent, _oldStepperEventParam);

	if (CLcd::GetInstance())
		CLcd::GetInstance()->Init();

	pinMode(BLINK_LED, OUTPUT);

	HALInitTimer0(HandleInterrupt);
	HALStartTimer0(IDLETIMER0VALUE);
}

////////////////////////////////////////////////////////////

void CControl::Initialized()
{
	StepperSerial.println(MESSAGE_OK);
}

////////////////////////////////////////////////////////////

void CControl::Kill()
{
	// may be in ISR context, do not print anything
	CStepper::GetInstance()->EmergencyStop();
}

////////////////////////////////////////////////////////

void CControl::Resurrect()
{
	CStepper::GetInstance()->EmergencyStopResurrect();
	_bufferidx = 0;
	StepperSerial.println(MESSAGE_OK);
}

////////////////////////////////////////////////////////////

void CControl::Pause()
{
	_pause = true;
}

////////////////////////////////////////////////////////////

void CControl::Continue()
{
	_pause = false;
}

////////////////////////////////////////////////////////////

void CControl::Idle(unsigned int idletime)
{
	if (CLcd::GetInstance())
		CLcd::GetInstance()->Idle(idletime);
}

////////////////////////////////////////////////////////////

void CControl::ParseAndPrintResult(CParser *parser)
{
// send OK pre Parse => give PC time to send next
#define SENDOKIMMEDIATELY
#undef SENDOKIMMEDIATELY
#ifdef SENDOKIMMEDIATELY 
	StepperSerial.println(MESSAGE_OK);
#endif

	parser->Parse();

	if (parser->GetError() != NULL)
	{
		StepperSerial.print(MESSAGE_ERROR);
		StepperSerial.print(parser->GetError());
		StepperSerial.print(F(" => "));
		StepperSerial.println(_buffer);
	}

#ifndef SENDOKIMMEDIATELY 
	StepperSerial.print(MESSAGE_OK);
#endif
	if (parser->GetOkMessage() != NULL)
	{
#ifdef SENDOKIMMEDIATELY 
		StepperSerial.print(MESSAGE_OK);
#endif
		StepperSerial.print(F(" "));
		parser->GetOkMessage()();
#ifdef SENDOKIMMEDIATELY 
		StepperSerial.println();
#endif
	}

#ifndef SENDOKIMMEDIATELY 
	StepperSerial.println();
#endif
}

////////////////////////////////////////////////////////////

void CControl::Command(char* buffer)
{
	if (IsKilled())
	{
		if (IsResurrectCommand(buffer))		// restart with "!!!"
		{
			Resurrect();
			return;
		}
		StepperSerial.print(MESSAGE_ERROR); StepperSerial.println(MESSAGE_CONTROL_KILLED);
	}
	else
	{
		_reader.Init(buffer);

		while (_reader.GetChar())
		{
			Parse();
		}
	}
}

////////////////////////////////////////////////////////////

bool CControl::IsEndOfCommandChar(char ch)
{
	return ch == '\n' || ch == '\r' || ch == -1;
}

////////////////////////////////////////////////////////////

void CControl::ReadAndExecuteCommand(Stream* stream, bool filestream)
{
	// call this methode if ch is available in stream

	while (stream->available() > 0)
	{
		_lasttime = millis();

		_buffer[_bufferidx] = stream->read();

		if (IsEndOfCommandChar(_buffer[_bufferidx]))
		{
			_buffer[_bufferidx] = 0;			// remove from buffer 
			Command(_buffer);
			_bufferidx = 0;
			return;
		}

		_bufferidx++;
		if (_bufferidx > sizeof(_buffer))
		{
			StepperSerial.print(MESSAGE_ERROR); StepperSerial.println(MESSAGE_CONTROL_FLUSHBUFFER);
			_bufferidx = 0;
		}
	}

	if (filestream)						// e.g. SD card => execute last line without "EndOfLine"
	{
		if (_bufferidx > 0)
		{
			_buffer[_bufferidx + 1] = 0;
			Command(_buffer);
			_bufferidx = 0;
		}
	}
}

////////////////////////////////////////////////////////////

bool CControl::SerialReadAndExecuteCommand()
{
	if (StepperSerial.available() > 0)
	{
		ReadAndExecuteCommand(&StepperSerial, false);
	}

	return _bufferidx > 0;		// command pending, buffer not empty
}

////////////////////////////////////////////////////////

void CControl::FileReadAndExecuteCommand(Stream* stream)
{
	if (!_pause)
		ReadAndExecuteCommand(stream, true);
}

////////////////////////////////////////////////////////////

void CControl::Run()
{
	_bufferidx = 0;
	_lasttime = _timeBlink = 0;

	Init();
	Initialized();

#ifdef _MSC_VER
	while (!CHelpParser::_exit)
#else
	while (true)
#endif
	{
		while (SerialReadAndExecuteCommand())
		{
			// wait until serial command processed
			CheckIdle();
		}

		CheckIdle();

		ReadAndExecuteCommand();
	}
}

////////////////////////////////////////////////////////////

void CControl::CheckIdle()
{
	unsigned long time = millis();

	if (_lasttime + TIMEOUTCALLIDEL < time)
	{
		Idle(time - _lasttime);
	}

	if (_timeBlink < time)
	{
		digitalWrite(BLINK_LED, digitalRead(BLINK_LED) == HIGH ? LOW : HIGH);
		_timeBlink = time + TIMEOUTBLINK;
	}
}

////////////////////////////////////////////////////////////

void CControl::ReadAndExecuteCommand()
{
	// override for alternative command source e.g. File
}

////////////////////////////////////////////////////////////

void CControl::TimerInterrupt()
{
	EnableInterrupts();	// enable irq for timer1 (Stepper)

	if (CLcd::GetInstance())
		CLcd::GetInstance()->TimerInterrupt();
}

////////////////////////////////////////////////////////////

void CControl::Delay(unsigned long ms)
{
	unsigned long expected_end = millis() + ms;

	while (expected_end > millis())
	{
		if (CLcd::GetInstance())
			CLcd::GetInstance()->Idle(0);
	}
}

////////////////////////////////////////////////////////////

bool CControl::OnStepperEvent(CStepper*stepper, EnumAsByte(CStepper::EStepperEvent) eventtype, unsigned char addinfo)
{
	switch (eventtype)
	{
		case CStepper::OnWaitEvent:

			if (CStepper::WaitTimeCritical > (CStepper::EWaitType) addinfo && CLcd::GetInstance())
				CLcd::GetInstance()->DrawRequest(false, CLcd::DrawStepperPos);
			break;
	}

	return _oldStepperEvent ? _oldStepperEvent(stepper, _oldStepperEventParam, eventtype, addinfo) : true;
}
