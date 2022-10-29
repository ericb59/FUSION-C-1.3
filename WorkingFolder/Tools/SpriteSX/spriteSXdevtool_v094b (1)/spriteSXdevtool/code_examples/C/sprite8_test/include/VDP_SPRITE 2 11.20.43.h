/* =============================================================================
   VDP_SPRITE.h
   v1.0 (11 February 2014)
   Description:
     Header for VDP TMS9918 SPRITE Lib.
============================================================================= */
#ifndef  __VDP_SPRITE_H__
#define  __VDP_SPRITE_H__

#include "newTypes.h"



/* =============================================================================
 setSpritesSize
 Function : set size of the sprites
 Input    : size (char)-> 0 = 8x8;    1 = 16x16                     
============================================================================= */
extern void setSpritesSize(char);



/* =============================================================================
 setSpritesZoom
 Function : set zoom of the sprites
 Input    : zoom (boolean)-> false = x1; true = zoom x2
============================================================================= */
extern void setSpritesZoom(boolean);



/* =============================================================================
 clearSprites
 Function : Initialises all sprite data
============================================================================= */
extern void clearSprites();



/* =============================================================================
 putSprite
 Function : Displays the sprite pattern.
 Input    : 
            (char) sprite plane (0-31) 
            (byte) x 
            (byte) y
            (char) color (0-15) 
            (byte) pattern      
============================================================================= */
extern void putSprite(char, byte, byte, char, byte);



/* =============================================================================
 setSpritePattern
 Function : Assign a pattern to a sprite plane.
 Input    : 
            (char) sprite plane (0-31) 
            (byte) pattern           
============================================================================= */
extern void setSpritePattern(char, char);



/* =============================================================================
 setSpriteColor
 Function : Assign a color to a sprite plane.
 Input: 
            (char) sprite plane (0-31) 
            (char) color (0-15)         
============================================================================= */
extern void setSpriteColor(char, char);



/* =============================================================================
 setSpritePosition
 Function : Assigns the position coordinates of a sprite plane.
 Input: 
            (char) sprite plane (0-31) 
            (byte) x 
            (byte) y           
============================================================================= */
extern void setSpritePosition(char, byte, byte);



/* =============================================================================
 setSpriteVisible
 Function : Hides or shows a sprite plane.
 Input: 
            (char) sprite plane (0-31) 
            (boolean) visible state          
============================================================================= */
extern void setSpriteVisible(char, boolean);



#endif