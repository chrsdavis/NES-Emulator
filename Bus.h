//#pragma once
#include <cstdint>
#include "mos6502.h"
#include <array>

using namespace std;

class Bus
{
  public: /* constructor destructor */
  Bus();
  ~Bus();

  public: /* Bus apparati */
  cpu6502 cpu;

  array<uint8_t, 64*1024> ram; //fake ram


  public: /* read write */
  void write(uint16_t addr, uint8_t data);
  uint8_t read(uint16_t addr, bool bReadOnlyFlag = false);
};