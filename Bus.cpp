#include "Bus.h"

Bus::Bus()
{
  for (auto &e : ram) e = 0x00;   /* clear ram */
  cpu.connectBus(this); /* connect cpu to bus */
}

Bus::~Bus()
{
  
}

void Bus::write(uint16_t addr, uint8_t data) /* write to bus */
{
  if(addr >= 0x0000 && adr <= 0xFFFF) /* bit range of bus */
    ram[addr] = data;
}

uint8_t read(uint16_t addr, bool bReadOnlyFlag = false) /* read bus */
{
  if(addr >= 0x0000 && adr <= 0xFFFF) /* bit range of bus */
    return ram[addr];
  return 0x00; /* if outside of range */
}