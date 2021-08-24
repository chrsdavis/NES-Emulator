#include "Mapper_000.h"

Mapper_000::Mapper_000()
{

}

Mapper_000::~Mapper_000()
{

}

bool Mapper_000::cpuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
  if(addr >= 0x8000 && addr <= 0xFFFF) /* adr in cart */
  {
    mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
    return true;
  }
  return false;
}

bool Mapper_000::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
  if(addr >= 0x8000 && addr <= 0xFFFF) /* adr in cart */
  {
    return true;
  }
  return false;
}

bool Mapper_000::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
  if(addr >= 0x0000 && addr <= 0x1FFF) /* ppu adrs in cart */
  {
    mapped_addr = addr;
    return true;
  }
  return false;
}

bool Mapper_000::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
  /* do nothing */
  /*
  if(addr >= 0x0000 && addr <= 0x1FFF) // ppu adrs in cart
  {

    return true;
  }
  */

  return false;
}