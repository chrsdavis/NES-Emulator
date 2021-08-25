//#pragma once
#include <cstdint>
#include <array>

#include "mos6502.h"
#include "ppu2C02.h"
#include "Cartridge.h"

using namespace std;

class Bus
{
  public: /* constructor destructor */
  Bus();
  ~Bus();

  public: /* Bus apparati */
  mos6502 cpu;
  ppu2C02 ppu;

  array<uint8_t, 2048> ramCPU; //fake ram

  shared_ptr<Cartridge> cart; //game cartridge

  public: /* Bus read write */
  void cpuWrite(uint16_t addr, uint8_t data);
  uint8_t cpuRead(uint16_t addr, bool bReadOnlyFlag = false);

  public: /* system interface */
  void insertCartridge(const shared_ptr<Cartridge>& cartridge);
  void reset();
  void clock(); /* system tick */

  private:
  /* counts # of clock cycles that have passed */
  uint32_t sysClockCount = 0;
};