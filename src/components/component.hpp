#pragma once

#include <cstdint>

class Component {
protected:
	~Component()=default;
public:
	virtual bool respondToRead(uint32_t loc) = 0;
	virtual uint8_t read(uint32_t loc) = 0;
	virtual void write(uint32_t loc, uint8_t val) = 0;
};
