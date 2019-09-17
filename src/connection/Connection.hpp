/*
 * Connection.hpp
 *
 *  Created on: Sep 17, 2019
 *      Author: chorm
 */

#ifndef SRC_CONNECTION_CONNECTION_HPP_
#define SRC_CONNECTION_CONNECTION_HPP_

#include <cstdint>

enum class Interrupts : std::uint8_t{
	RESET = 1, IRQB = 2, ABORTB = 4, MASK = 7
};

constexpr Interrupts operator|(Interrupts a,Interrupts b){
	return Interrupts{static_cast<std::uint8_t>(a)|static_cast<std::uint8_t>(b)};
}
constexpr Interrupts operator&(Interrupts a,Interrupts b){
	return Interrupts{static_cast<std::uint8_t>(a)&static_cast<std::uint8_t>(b)};
}
constexpr Interrupts operator^(Interrupts a,Interrupts b){
	return Interrupts{static_cast<std::uint8_t>(a)^static_cast<std::uint8_t>(b)};
}
constexpr Interrupts operator~(Interrupts a){
	return Interrupts::MASK^a;
}

class Connection{
protected:
	~Connection()=default;
public:
	virtual void sendChar(char c)=0;
	virtual std::uint8_t recvCmd()=0;
	virtual Interrupts checkInterrupts()=0;
};



#endif /* SRC_CONNECTION_CONNECTION_HPP_ */
