#include "potato.h"
#include "PRNG.h"
#include "printer.h"

Potato::Potato( Printer &prt ):prt(prt){}

Mashed::Mashed( Printer &prt, unsigned int maxTicks ):Potato(prt){
	maxticks = maxTicks;
	reset();
}

void Mashed::reset(){
	uint32_t tick = prng(1,maxticks);
	ticks = (unsigned int)tick;
	prt.print(Printer::Mashed,ticks);
}

void Mashed::countdown(){
	ticks--;
	if(ticks == 0) throw Expire();
}

Fried::Fried( Printer &prt, unsigned int maxTicks ):Potato(prt){
	maxticks = maxTicks;
	reset();
}

void Fried::reset(){
	ticks = maxticks;
	prt.print(Printer::Fried,ticks);
}

void Fried::countdown(){
	ticks--;
	if(ticks == 0) throw Expire();
}
