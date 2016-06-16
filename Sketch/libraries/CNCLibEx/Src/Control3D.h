
#pragma once

////////////////////////////////////////////////////////

#include <Control.h>

////////////////////////////////////////////////////////

class CControl3D : public CControl
{
private:

	typedef CControl super;

public:

	CControl3D()				 { }

protected:

	virtual void Init() override;
	virtual void Initialized() override;
	virtual bool Parse(CStreamReader* reader, Stream* output) override;

	void InitSD(pin_t sdEnablePin);

	virtual void ReadAndExecuteCommand() override;

public:

	void ReInitSD();

private:

	pin_t _sdEnablePin;
};

////////////////////////////////////////////////////////
