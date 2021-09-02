#include "Bus.h"

using namespace std;

Bus::Bus()
{
  for (auto &e : ram) e = 0x00;   /* clear ram */
  cpu.connectBus(this); /* connect cpu to bus */
}

Bus::~Bus()
{
  
}

void Bus::cpuWrite(uint16_t addr, uint8_t data) /* write to bus */
{
  if(cart->cpuWrite(addr, data)) /* if cart is writing */
  {
    /* cartridge read/write has priority */

  }else if(addr >= 0x0000 && adr <= 0x1FFF) /* bit range of bus */
  {
    ramCPU[addr & 0x07FF] = data;

  }else if(addr >= 0x2000 && addr <= 0x3FFF)
  { /* ppu bus range */
    ppu.cpuWrite(addr & 0x007, data); /* mirroring */

  }else if(addr >= 0x4016 && addr <= 0x4017)
  {
    controller_state[addr & 0x0001] = controller[addr & 0x0001];
  }
}

uint8_t cpuRead(uint16_t addr, bool bReadOnlyFlag = false) /* read bus */
{
  uint8_t data = 0x00;

  if(cart->cpuWrite(addr, data)) /* if cart is writing */
  {
    /* cartridge read/write has priority */

  }else if(addr >= 0x0000 && adr <= 0x1FFF) /* bit range of bus */
  {
    data = ramCPU[addr & 0x07FF];
    
  }else if(addr >= 0x2000 && addr <= 0x3FFF)
  { /* ppu range */
    data = ppu.cpuRead(addr & 0x0007, bReadOnly);
  }else if(addr >= 0x4016 && addr <= 0x4017)
  {
    data = (controller_state[addr & 0x0001] & 0x80) > 0;
    controller_state[addr & 0x0001] <<= 1;
  }

  return data;
}

void Bus::insertCartridge(const shared_ptr<Cartridge>& cartridge)
{
  /* connect bus to cartridge */
  this->cart = cartridge;
  /*connect ppu to cartridge */
  ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
  cart->reset();     /* reset cartridge */
  cpu.reset();       /* reset the cpu */
  ppu.reset();       /* reset the ppu */
  sysClockCount = 0; /* reset clock count */
}

void Bus::clock()
{
  ppu.clock(); /* ppu clock is fastest */

  /* cpu clock is 1/3 speed of ppu */
  if(sysClockCount % 3 == 0)
  {
    cpu.clock();
  }

  /* ppu's interrupt for vertical blanking period */
  if(ppu.nmi)
  {
    ppu.nmi = false;
    cpu.nmi();
  }

  sysClockCount++;
}