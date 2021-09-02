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

  shared_ptr<Cartridge> cart; /* game cartridge */
  uint8_t cpuRAM[2048]; /* 2kb of ram */
  uint8_t controller[2]; /* controllers */

  public: /* Bus read write */
  void cpuWrite(uint16_t addr, uint8_t data);
  uint8_t cpuRead(uint16_t addr, bool bReadOnlyFlag = false);

  public: /* system interface */
  void insertCartridge(const shared_ptr<Cartridge>& cartridge);
  void reset(); /* resets entire system */
  void clock(); /* system tick */

  private:
  /* counts # of clock cycles that have passed */
  uint32_t sysClockCount = 0;

  /* internal cache of controller */
  uint8_t controller_state[2];
};