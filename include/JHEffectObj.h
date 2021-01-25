#pragma once
#include"JHObject.h"
class JHEffectObj:public JHObject
{
public:
	bool Frame() override;
	bool Render() override;
	JHEffectObj() {}
	virtual ~JHEffectObj(){}

private:

};