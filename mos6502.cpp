#include "mos6502.h"

mos6502::mos6502()
{

}

mos6502::~mos6502()
{

}

uint8_t mos6502::read(uint16_t a) /* cpu read */
{
  return bus->read(a,false); /* return bus' read (adr,flag)*/
}

void mos6502::write(uint16_t a, uint8_t d) /*cpu write */
{
  bus->write(a,d); /* bus write (adr,data) */
}