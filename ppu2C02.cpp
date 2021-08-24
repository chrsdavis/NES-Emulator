#include "ppu2C02.h"

using namespace std;

ppu2C02::ppu2C02()
{

}

ppu2C02::~ppu2C02()
{

}

uint8_t ppu2C02::cpuRead(uint16_t addr, bool readOnly)
{
  uint8_t data = 0x00;

  /* cpu can address 8 locations on ppu */
  switch (addr)
  {
    case 0x0000: /* Control */
      break;
    case 0x0001: /* Mask */
      break;
    case 0x0002: /* Status */
      break:
    case 0x0003: /* OAM address */
      break;
    case 0x0004: /* OAM data */
      break;
    case 0x0005: /* Scroll */
      break;
    case 0x0006: /* PPU address */
      break;
    case 0x0007: /* PPU data */
      break;
  }
  return data;
}

void ppu2C02::cpuWrite(uint16_t addr, uint8_t data)
{
  /* cpu can address 8 locations on ppu */
  switch (addr)
  {
    case 0x0000: /* Control */
      break;
    case 0x0001: /* Mask */
      break;
    case 0x0002: /* Status */
      break:
    case 0x0003: /* OAM address */
      break;
    case 0x0004: /* OAM data */
      break;
    case 0x0005: /* Scroll */
      break;
    case 0x0006: /* PPU address */
      break;
    case 0x0007: /* PPU data */
      break;
  }
}

uint8_t ppu2C02::ppuRead(uint16_t addr, bool readOnly)
{
  uint8_t data = 0x00;
  addr &= 0x3FFF;

  if(cart->ppuRead(addr, data))
  {
    /* cartridge has read priority */

  }

  return data;
}

void ppu2C02::ppuWrite(uint16_t addr, uint8_t data)
{
  addr &= 0x3FFF;

  if(cart->ppuWrite(addr, data))
  {
    /* cartridge has write priority */
    
  }
}

void ppu2C02::ConnectCartridge(const shared_ptr<Cartridge>& cartridge)
{
  this->cart = cartridge;
}