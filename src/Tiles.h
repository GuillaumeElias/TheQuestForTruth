/** This file is part of TheQuestForTruth project for Arduboy by Guillaume Elias
 * You can reuse it in accordance with the GNU LESSER GENERAL PUBLIC LICENSE (see LICENSE) 
 **/

#ifndef _TILES_H_
#define _TILES_H_

namespace tiles
{
  PROGMEM static const byte WALL[] = {0x87, 0xb1, 0x31, 0x37, 0x87, 0x87, 0xb1, 0x31, 
  0x37, 0x87, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
  0x01, 0x00, 0x00, 0x01};

  PROGMEM static const byte WALL_BACK[] = {0x02, 0x10, 0x10, 0x12, 0x02, 0x02, 0x20, 0x20, 
  0x22, 0x02, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
  0x01, 0x00, 0x00, 0x01};

  PROGMEM static const byte DOOR_UP[] = {0x02, 0x80, 0x40, 0x42, 0x22, 0x22, 0x40, 0x40, 
  0x82, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01};

  PROGMEM static const byte BRICK[] = {0xfe, 0x09, 0x83, 0x21, 0x0b, 0x21, 0x45, 0x11, 
  0x01, 0xfe, 0x01, 0x02, 0x02, 0x02, 0x02, 0x03, 
  0x02, 0x03, 0x02, 0x01};

  PROGMEM static const byte FIRTREE_UPLEFT[] = {0x00, 0x00, 0x00, 0x40, 0x40, 0xe0, 0xe0, 0xf8, 
  0xfe, 0x7f, 0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 
  0x03, 0x03, 0x02, 0x01};

  PROGMEM static const byte FIRTREE_UPRIGHT[] = {0xfe, 0xfc, 0xf0, 0xa0, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 
  0x03, 0x02, 0x00, 0x00};

  PROGMEM static const byte FIRTREE_DOWNLEFT[] = {0x80, 0xcc, 0xec, 0xfe, 0xfe, 0xff, 0xff, 0xf7, 
  0xeb, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03};

  PROGMEM static const byte FIRTREE_DOWNRIGHT[] = {0xff, 0xdf, 0xaf, 0xdf, 0xff, 0xff, 0xfe, 0xec, 
  0xc8, 0x80, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00};

  PROGMEM static const byte DIRT[] = {0xff, 0xf7, 0x7d, 0xdf, 0xf5, 0xdf, 0xbb, 0xee, 
  0xff, 0x75, 0x03, 0x01, 0x03, 0x03, 0x03, 0x02, 
  0x03, 0x02, 0x03, 0x03};

}

#endif