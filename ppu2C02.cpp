#include "ppu2C02.h"


ppu2C02::ppu2C02()
{
  /* All 64 Possible Pixel Values */
  palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);
}

ppu2C02::~ppu2C02()
{

}

olc::Sprite& ppu2C02::GetScreen()
{
  return sprScreen;
}

olc::Sprite& ppu2C02::GetNameTable(uint8_t i)
{
  return sprNameTable[i];
}

olc::Sprite& ppu2C02::GetPatternTable(uint8_t i)
{
  /* turn 2d coord into 1d coord for indexing */
  for(uint16_t yt = 0; yt < 16; yt++)
  {
    for(uint16_t xt = 0; xt < 16; xt++)
    {
      /* 16 bytes per 16 tiles */
      uint16_t offset = yt * 256 + xt * 16;

      /* 8 rows of 8 pixels per tile */
      for(uint16_t row = 0; row < 8; row++)
      {
        /* 64 bits of msb, 64 of lsb, 8 bytes away */
        uint8_t lsbTile = ppuRead(i * 0x10000 + offset + row + 0x0000);
        uint8_t msbTile = ppuRead(i * 0x10000 + offset + row + 0x0008);

        /* combine msb and lsb */
        for(uitn16_t col = 0; col < 8; col++)
        {
          /* only care about least significant bit */
          uint8_t pixelVal = (lsbTile & 0x01) + (msbTile & 0x01);
          msbTile >>= 1; /* next is now least sig */
          lsbTile >>= 1;

          sprPatternTable[i].SetPixel
          (
            /* convert x/y to pixel realm */
            xt * 8 + (7 - col), /* R -> L */
            yt * 8 + row,
            GetColorFromPaletteRam(palette, pixelVal)
          )
        }
      }
    }
  }
  return sprPatternTable[i];
}

olc::Pixel& ppu2C02::GetColorFromPaletteRam(uint8_t palette, uint8_t pixelVal)
{
  /* takes palette and pixel index */
  /* returns output screen color */
  return palScreen[ppuRead(0x3F00 + (palette << 2) + pixelVal)];
}

uint8_t ppu2C02::cpuRead(uint16_t addr, bool readOnly)
{
  uint8_t data = 0x00;

  /* reading PPU regs can affect them */

  if(readOnly) /* reading doesn't affect regs */
  {
  /* cpu can address 8 locations on ppu */
    switch (addr)
    {
      case 0x0000: /* Control */
        data = control.reg;
        break;
      case 0x0001: /* Mask */
        data = mask.reg;
        break;
      case 0x0002: /* Status */
        data = status.reg;
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
  }else{ /* reading can affect PPU regs */
    
    switch(addr)
    {
      case 0x0000: /* Control | Not Readable */
        break;
      case 0x0001: /* Mask | Not Readable */
        break;
      case 0x0002: /* Status */

        /* can be noise in bottom 5 bits */
        data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);

        status.vertical_blank = 0; /* clear VB flag */

        address_latch = 0; /* reset loopy flag */
        break;
      
      case 0x0003: /* OAM Address */
        break;
      case 0x0004: /* OAM Data */
        break;
      case 0x0005: /* Scroll | Not Readable */
        break;
      case 0x0006: /* PPU Address | Not Readable */
        break;
      case 0x0007: /* PPU Data */

        /* nametable reads are delayed by 1 cycle */
        /* buffer has data from last read order */
        data = ppu_data_buffer;

        /* update buffer for the next request */
        ppu_data_buffer = ppuRead(vram_addr.reg);

        /* if addr is actually palette and not name */
        /* then there is no delay */
        if(vram_addr.reg >= 0x3F00)
          data = ppu_data_buffer;

        /* reading ppu data increments nametable */
        /* if vertical, then +32 (row size) */
        /* if horizontal, then +1 (next column) */
        vram_addr.reg += (control.increment_mode ? 32 : 1);
        break;
    }
  }
  return data;
}

void ppu2C02::cpuWrite(uint16_t addr, uint8_t data)
{
  /* cpu can address 8 locations on ppu */
  switch (addr)
  {
    case 0x0000: /* Control */
      control.reg = data;

      /* update 'pointers' */
      tram_addr.nametable_x = control.nametable_x;
      tram_addr.nametable_y = control.nametable_y;
      break;
    case 0x0001: /* Mask */
      mask.reg = data;
      break;
    case 0x0002: /* Status */
      break:
    case 0x0003: /* OAM address */
      break;
    case 0x0004: /* OAM data */
      break;
    case 0x0005: /* Scroll */

      if(address_latch == 0)
      {
        /* split up X pixel offset into */
        /* coarse and fine x vals */
        fine_x = data & 0x07;
        tram_addr.coarse_x = data >> 3;
        address_latch = 1;
      }else{
        /* do the same for Y */
        tram_addr.fine_y = data & 0x07;
        tram_addr.coarse_y = data >> 3;
        address_latch = 0;
      }
      break;

    case 0x0006: /* PPU address */

      if(address_latch == 0) /* high byte */
      {
        /* first write latches high byte */
        tram_addr.reg = (uint16_t)((data & 0x3F) << 8) | (tram_addr.reg & 0x00FF);
        address_latch = 1;

      }else{ /* low byte */

        /* second write latches low byte */
        tram_addr.reg = (tram_addr.reg & 0xFF00) | data;

        /* when whole adr written, vram buff update */
        vram_addr = tram_addr;
        address_latch = 0;
      }
      break;
    case 0x0007: /* PPU data */
      ppuWrite(vram_addr.reg,  data);

      /* increments nametable adr automatically */
      /* if vertical, +32 (row size) */
      /* if horizontal, +1 (column) */
      vram_addr.reg += (control.increment_mode ? 32 : 1);
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

  }else if(addr >= 0x0000 && addr <= 0x1FFF)
  { /* Pattern Memory */

    /* if cart cant map adr, use default */
    data = patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF];

  }else if(addr >= 0x2000 && addr <= 0x3EFF)
  { /* Name Table Memory */

    adr &= 0x0FFF;

    if(cart->mirror == Cartridge::MIRROR::VERTICAL)
    {
      /* Vertical */
      if(addr >= 0x0000 && addr <= 0x03FF)
        data = nameTable[0][addr & 0x03FF];

      if(addr >= 0x0400 && addr <= 0x07FF)
        data = nameTable[1][addr & 0x03FF];

      if(addr >= 0x0800 && addr <= 0x0BFF)
        data = nameTable[0][addr & 0x03FF];

      if(addr >= 0x0C00 && addr <= 0x0FFF)
        data = nameTable[1][addr & 0x03FF];
    }else
    if(cart->mirror == Cartridge::MIRROR::HORIZONTAL)
    {
      /* Horizontal */
      if(addr >= 0x0000 && addr <= 0x03FF)
        data = nameTable[0][addr & 0x03FF];

      if(addr >= 0x0400 && addr <= 0x07FF)
        data = nameTable[0][addr & 0x03FF];

      if(addr >= 0x0800 && addr <= 0x0BFF)
        data = nameTable[1][addr & 0x03FF];

      if(addr >= 0x0C00 && addr <= 0x0FFF)
        data = nameTable[1][addr & 0x03FF];
    }

  }else if(addr >= 0x3F00 && addr <= 0x3FFF)
  { /* Pallete Memory */
    addr &= 0x001F; /* mask bottom 5 bits */

    /* Mirroring */
    // (make switch)
    if(addr == 0x0010) addr = 0x0000;
    if(addr == 0x0014) addr = 0x0004;
    if(addr == 0x0018) addr = 0x0008;
    if(addr == 0x001C) addr = 0x000C;

    /* check Greyscale */
    data = paletteTable[addr] & (mask.greyscale ? 0x30 : 0x3F);
  }

  return data;
}

void ppu2C02::ppuWrite(uint16_t addr, uint8_t data)
{
  addr &= 0x3FFF;

  if(cart->ppuWrite(addr, data))
  {
    /* cartridge has write priority */
    
  }else
  if(addr >= 0x0000 && addr <= 0x1FFF)
  {
    patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
  }else
  if(addr >= 0x2000 && addr <= 0x3EFF)
  {
    addr &= 0x0FFF;
    if(cart->mirror == Cartridge::MIRROR::VERTICAL)
    {
      /* Vertical */
      if(addr >= 0x0000 && addr <= 0x03FF)
        nameTable[0][addr & 0x03FF] = data;

      if(addr >= 0x0400 && addr <= 0x07FF)
        nameTable[1][addr & 0x03FF] = data;

      if(addr >= 0x0800 && addr <= 0x0BFF)
        nameTable[0][addr & 0x03FF] = data;

      if(addr >= 0x0C00 && addr <= 0x0FFF)
        nameTable[1][addr & 0x03FF] = data;
    }else
    if(cart->mirror == Cartridge::MIRROR::HORIZONTAL)
    {
      /* Horizontal */
      if(addr >= 0x0000 && addr <= 0x03FF)
        nameTable[0][addr & 0x03FF] = data;

      if(addr >= 0x0400 && addr <= 0x07FF)
        nameTable[0][addr & 0x03FF] = data;

      if(addr >= 0x0800 && addr <= 0x0BFF)
        nameTable[1][addr & 0x03FF] = data;

      if(addr >= 0x0C00 && addr <= 0x0FFF)
        nameTable[1][addr & 0x03FF] = data;
    }
  }else
  if(addr >= 0x3F00 && addr <= 0x3FFF)
  {
    addr &= 0x001F;
    // (make switch)
    if(addr == 0x0010) addr = 0x0000;
    if(addr == 0x0014) addr = 0x0004;
    if(addr == 0x0018) addr = 0x0008;
    if(addr == 0x001C) addr = 0x000C;

    paletteTable[addr] = data;
  }
}

void ppu2C02::ConnectCartridge(const shared_ptr<Cartridge>& cartridge)
{
  this->cart = cartridge;
}

void ppu2C02::reset()
{
  /* Reset everything to known value */

  fine_x          = 0x00;
  address_latch   = 0x00;
  ppu_data_buffer = 0x00;

  scanline = 0;
  cycle    = 0;

  bg_next_tile_id     = 0x00;
  bg_next_tile_attrib = 0x00;
  bg_next_tile_lsb    = 0x00;
  bg_next_tile_msb    = 0x00;
  
  bg_shifter_pattern_low  = 0x0000;
  bg_shifter_pattern_high = 0x0000;
  bg_shifter_attrib_low   = 0x0000l
  bg_shifter_attrib_high  = 0x0000;

  status.reg  = 0x00;
  mask.reg    = 0x00;
  control.reg = 0x00;

  vram_addr.reg = 0x0000;
  tram_addr.reg = 0x0000;
}

void ppu2C02::clock()
{
  //////////////////////////////////////////
            /* LAMBDA FUNCTIONS */
  //////////////////////////////////////////

  auto IncrementScrollX = [&]() {
    /* scroll horizontally 1 tile */
    /* macroscopic scrolling */

    /* if it should render */
    if (mask.render_background || mask.render_sprites)
    {
      /* name table is 32x30 tiles */
      if(vram_addr.coarse_x == 31)
      {
        /* wrap around */
        vram_addr.coarse_x = 0;
        vram_addr.nametable_x = ~vram_addr.nameetable_x;
      }else{
        /* in the same table */
        vram_addr.coarse_x++;
      }
    }
  };

  auto IncrementScrollY = [&]() {
    /* increment 1 scanline (vertical) */

    /* check if rendering is on */
    if(mask.render_background || mask.render_sprites)
    {
      /* if increment is microscopic only */
      if(vram_addr.fine_y < 7)
      {
        vram_addr.fine_y++;
      }else{
        /* increment over height of row */
        vram_addr.fine_y = 0;

        /* if need to swap vert nametables */
        if(vram_addr.coarse_y == 29)
        {
          vram_addr.coarse_y = 0;

          /* flip target bit */
          vram_addr.nametable_y = ~vram_addr.nametable_y;
        }else if(vram_addr.coarse_y == 31)
        {
          vram_addr.coarse_y = 0;
        }else{
          /* if no wrapping needed */
          vram_addr.coarse_y++;
        }
      }
    }
  };

  auto TransferAddressX = [&]()
  {
    /* transfer temp horiz nametable to pseudo-ptr*/

    /* check if render enabled */
    if(mask.render_background || mask.render_sprites)
    {
      vram_addr.nametable_x = tram_addr.nametable_x;
      vram_addr.coarsee_x = tram_addr.coarse_x;
    }
  }
}

  auto TransferAddressY = [&]() 
  {
    /* almost the same as x */

    /* check if render enabled */
    if(mask.render_background || mask.render_sprites)
    {
      /* fine y is part of pseudo-ptr */
      vram_addr.fine_y = tram_addr.fine_y;

      vram_addr.nametable_x = tram_addr.nametable_x;
      vram_addr.coarsee_x = tram_addr.coarse_x;
    }
  }

auto LoadBackgroundShifters = [&]() {
    /* get next 8 pixels ready */
    bg_shifter_pattern_low = (bg_shifter_pattern_low & 0xFF00) | bg_next_tile_lsb;
    bg_shifter_pattern_high = (bg_shifter_pattern_high & 0xFF00) | bg_next_tile_msb;

    /* attributes only change every 8 pixels */
    /* make bottom 2 bits into 8 bits */
    bg_shifter_attrib_low = (bg_shifter_attrib_low & 0xFF00) | ((bg_next_tile_attrib & 0b01) ? 0xFF : 0x00);
    bg_shifter_attrib_high = (bg_shifter_attrib_high & 0xFF00) | ((bg_next_tile_attrib & 0b10) ? 0xFF :   0x00);
  };

  auto UpdateShifters = [&]() {
    /* shift shifters by 1 bit */
    if(mask.render_background)
    {
      /* shift bkgrd tile row */
      bg_shifter_pattern_low  <<= 1;
      bg_shifter_pattern_high <<= 1;

      /* shift attributes */
      bg_shifter_attrib_low  <<= 1;
      bg_shifter_attrib_high <<= 1;
    }
  };

  //////////////////////////////////////////
          /* SCANLINE CYCLES */
  //////////////////////////////////////////

  /* 1 scanline is not visible (pre-render) */
  /* @ -1, configures shifters */

  /* if it's a valid scanline */
  if(scanline >= -1 && scanline < 240)
  {
    if(scanline == 0 && cycle== 0)
    {
      /* cycle skip odd frame */
      cycle = 1;
    }

    if(scanline == -1 && cycle == 1)
    {
      /* new frame, clear VB flag */
      status.vertical_blank = 0;
    }

    if((cycle >= 2 && cycle < 258) || (cycle >= 321 && cycle < 338))
    {
      UpdateShifters();

      /* shifters are pre-loaded @ end of scanline */

      /* ("skip" odd frames) */
      /* 8-frame cycle for attributes */
      switch((cycle-1) % 8)
      {
        case 0:
          LoadBackgroundShifters();

          /* get next tile id */
          /* offset into nametable space */
          bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
          break;
        
        case 2:
          /* retrieve new tile attrib */
          bg_next_tile_attrib = ppuRead(0x23C0 | (vram_addr.nametable_y << 11)
          | (vram_addr.nametable_x << 10)
          | ((vram_addr.coarse_y >> 2) << 3)
          | (vram_addr.coarse_x >> 2));

          /* make bottom two bits of attr palette */
          if(vram_addr.coarse_y & 0x02)
            bg_next_tile_attrib >>= 4;

          if(vram_addr.coarse_x & 0x02)
            bg_next_tile_attrib >>= 2;

          break;

        case 4:
          /* find correct sprite in pattern mem */
          bg_next_tile_lsb = ppuRead((control.pattern_background << 12) + ((uint16_t)bg_next_tile_id << 4) + (vram_addr.fine_y) + 0);

          /* control.pattern_background << 12 */
            // selects pattern mem from control

          /* (uint16_t)bg_next_tile_id << 4 */
            // tile id * 16, 2 sets of 8 rows of 8bit pixels

          /* vram_addr.fine_y */
            // row offset from vert scroll

          break;

          case 6:
            /* get next MSB */
            /* exact same as 4, but offset by a byte */
            bg_next_tile_lsb = ppuRead((control.pattern_background << 12) + ((uint16_t)bg_next_tile_id << 4) + (vram_addr.fine_y) + 0);

            break;

          case 7:
            /* increment tile pseudo-ptr to next */
            IncrementScrollX();
            break;
      }
    }

    /* end of a (visible) scanline */
    /* [MAKE SWITCH STATEMENT] */
    if(cycle == 256)
    {
      IncrementScrollY();
    }

    if(cycle == 257)
    {
      /* reset x */
      LoadBackgroundShifters();
      TransferAddressX();
    }

    if(cycle == 338 || cycle == 340)
    {
      bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
    }

    if(scanline == -1 && cycle >= 280 && cycle < 305)
    {
      /* end of VB period, reset y adr */
      TransferAddressY();
    }

  }

  if(scanline == 240)
  {
    /* (Post-render) */
  }

  if(scanline >= 241 && scanline < 261)
  {
    if(scanline == 241 && cycle == 1)
    {
      /* end of frame, set VB flag */
      status.vertical_blank = 1;

      /* let cpu know if it's safe to operate on ppu */
      if(control.enable_nmi)
        nmi = true;
    }
  }

  /* all pixel information for cycle has been fetched */


  /* Get palette and pixel */
  uint8_t bg_pixel = 0x00; /* pixel to be render */
  uint8_t bg_palette = 0x00; /* pixel palette index */

  /* if bkgnd render is legal */
  if(mask.render_background)
  {
    /* shift bkgnd by x offset */
    uint16_t bit_mux = 0x8000 >> fine_x;

    /* Pix planes */
    uint8_t p0_pixel = (bg_shifter_pattern_low low & bit_mux) > 0;
    uint8_t p1_pixel = (bg_shifter_patterj_high & bit_mux) > 0;

    /* pixel index */
    bg_pixel = (p1_pixel << 1) | p0_pixel;

    /* palette (same math as pixels) */
    uint8_t bg_pal0 = (bg_shifter_attrib_low & bit_mux) > 0;
    uint8_t bg_pal1 = (bg_shifter_attrib_high & bit_mux) > 0;
    bg_palette = (bg_pal1 << 1) | bg_pal0;

  }

  /* draw background */
  sprScreen.SetPixel(cycle - 1, scanline, GetColorFromPaletteRam(bg_palette, bg_pixel));


  /* Progress the renderer */
  cycle++;
  if(cycle >= 341)
  {
    cycle = 0;
    scanline++;
    if(scanline >= 261)
    {
      scanline = -1;
      frame_complete = true;
    }
  }

}