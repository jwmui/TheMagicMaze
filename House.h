#pragma once

#include "Drawable.h"

class House : public Drawable
{

public:
	House();
	virtual ~House(void);
	virtual void draw(DrawData&);
	virtual void update(UpdateData&);
};



