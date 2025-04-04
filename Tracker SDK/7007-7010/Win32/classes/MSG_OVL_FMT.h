///////////////////////////////////////////////////////////////////////////////
// MSG_OVL_FMT.H
//
// Message structure definitions to support video overlay and sprites in the
// following products:
// * Series 7000 VME, PCI and PCI Express Video Trackers
// * Series 8000 Video Trackers (Sprites ONLY)
//

/*******************************************************************************
 * Copyright (c) 2003-2019 Moog, Inc. All Rights Reserved
 *
 * Moog, Inc. licenses this software under specific terms and conditions.
 * Use of any of the software or derivatives thereof in any product without
 * a Moog, Inc. video tracker is strictly prohibited.
 *
 * Moog, Inc. provides this software AS IS, WITHOUT ANY WARRANTY, EXPRESS OR
 * IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  Moog makes no guarantee or representations
 * regarding the use of, or the results of the use of, the software and
 * documentation in terms of correctness, accuracy, reliability, currentness,
 * or otherwise; and you rely on the software, documentation and results
 * solely at your own risk.
 *
 * IN NO EVENT SHALL MOOG BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
 * LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
 * OF ANY KIND.  IN NO EVENT SHALL MOOG'S TOTAL LIABILITY EXCEED THE SUM
 * PAID TO MOOG FOR THE PRODUCT LICENSED HEREUNDER.
 *
 ******************************************************************************/

#ifndef __MSG_OVL_FMT_H__
#define __MSG_OVL_FMT_H__

#pragma pack(push, 2)	// pack all messages with two byte alignment

// data types
#ifndef USHORT
	typedef unsigned short	USHORT;
#endif

#ifndef UCHAR
	typedef unsigned char	UCHAR;
#endif

// total overlay data structure size in bytes
#define OVL_DATA_SIZE				36

// maximum overlay message pixels (in 16-bit words)
#define OVL_MAX_PIXELS				15

// maximum overlay text string length
#define OVL_MAX_STRING_LEN			28

// video overlay size
#define OVL_OVERLAY_SIZE_X			2048
#define OVL_OVERLAY_SIZE_Y			2048

// sprite sizes
#define OVL_SPRITE1_SIZE_X			128
#define OVL_SPRITE1_SIZE_Y			128

#define OVL_SPRITE2_SIZE_X			128
#define OVL_SPRITE2_SIZE_Y			128

#define OVL_SPRITE3_SIZE_X			128
#define OVL_SPRITE3_SIZE_Y			128

#define OVL_SPRITE4_SIZE_X			128
#define OVL_SPRITE4_SIZE_Y			128

// diamond line segments can be drawn / not drawn
#define OVL_DIAMOND_ALL_SEGMENTS	0x0000		// note: same as 0x000F
#define OVL_DIAMOND_UPPER_LEFT		0x0008
#define OVL_DIAMOND_UPPER_RIGHT		0x0004
#define OVL_DIAMOND_LOWER_LEFT		0x0002
#define OVL_DIAMOND_LOWER_RIGHT		0x0001

// diamond constructions (for your convenience)
#define OVL_DIAMOND_UP_ARROW		(OVL_DIAMOND_UPPER_LEFT  | OVL_DIAMOND_UPPER_RIGHT)
#define OVL_DIAMOND_DOWN_ARROW		(OVL_DIAMOND_LOWER_LEFT  | OVL_DIAMOND_LOWER_RIGHT)
#define OVL_DIAMOND_LEFT_ARROW		(OVL_DIAMOND_UPPER_LEFT  | OVL_DIAMOND_LOWER_LEFT)
#define OVL_DIAMOND_RIGHT_ARROW		(OVL_DIAMOND_UPPER_RIGHT | OVL_DIAMOND_LOWER_RIGHT)

//////////////////////////////////////////////////////////////////////////////
//  OVERLAY PIXEL FORMAT
//
//	Mixed Pixel Format (FPGA revisions 23 and greater):
//		Pixels are unsigned 16-bit values.
//		The 15th bit (highest bit) is the color flag (0=monochrome, 1=color)
//		If the color flag is clear, the following data format is used:
//			The luma (B&W) value is stored in the lower 10 bits and
//			the alpha (transparency) in the next 5 bits.
//			If all alpha bits are clear, the pixel is 100% opaque.
//			If all alpha bit are set, the pixel is ~97% transparent.
//		If the color flag is set, the following data format is used:
//			A 15-bit high color RGB value is stored in the pixel with
//			5 bits of red (bits 14 though 10),
//			5 bits of green (bits 9 though 5) and
//			5 bits of blue (bits 4 though 0)
//		A special case value of 0xFFFF is 100% transparent (pass though).
//		On 7000 series boards, only monochrome is used for analog video.
//
//	Monochrome Pixel Format (legacy, FPGA revisions up to 22):
//		Pixels are unsigned 16-bit values.
//		Each 16-bit value is divided into the intensity (lower 10 bits)
//		and alpha (transparency) in the upper 6 bits.
//		An alpha value of 0x00 is 100% opaque.
//		An alpha value of 0x3F is 100% transparent.
//		A special case value of 0xFFFF is 100% transparent (pass though).
//		On 7000 series boards, only (B&W) luma is used for analog video.
//

#define OVL_COLOR_TRANSPARENT		0xFFFF	// transparency pixel value


//////////////////////////////////////////////////////////////////////////////
// Overlay Commands
//
#define	OVL_CMD_NONE			0

// overlay control
#define	OVL_CMD_ENABLE			1		// enable the video overlay/sprite
#define	OVL_CMD_DISABLE			2		// disable the video overlay/sprite
#define	OVL_CMD_CLEAR			3		// clear the overlay/sprite
#define	OVL_CMD_TOGGLE			4		// toggle selected overlay buffer
#define	OVL_CMD_SELECT1			5		// select overlay buffer #1
#define	OVL_CMD_SELECT2			6		// select overlay buffer #2
#define OVL_CMD_POSITION		7		// set the overlay/sprite position
#define OVL_CMD_NORMAL_OUTPUT	8		// normal pixel output for the video overlay/sprite (opposite of invert)
#define OVL_CMD_INVERT_OUTPUT	9		// invert the pixel output for the video overlay/sprite

// drawing
#define	OVL_CMD_POINTS			20		// draw pixel(s)
#define	OVL_CMD_LINE			21		// draw a line
#define	OVL_CMD_RECTANGLE		22		// draw a rectangle
#define	OVL_CMD_SQUARE			23		// draw a square
#define	OVL_CMD_TRIANGLE		24		// draw a triangle
#define	OVL_CMD_ELLIPSE			25		// draw an ellipse
#define	OVL_CMD_CIRCLE			26		// draw a circle
#define	OVL_CMD_ARC				27		// draw an arc (partial circle)
#define OVL_CMD_DIAMOND			28		// draw a diamond

// symbols
#define	OVL_CMD_COLORBAR		100		// draw a color bar
#define	OVL_CMD_GRATICULE		101		// draw a graticule
#define	OVL_CMD_STRING			102		// draw an ASCII character string (NULL terminated)
#define OVL_CMD_FONT_STRING		103		// draw an ASCII character string using the currently loaded user font (NULL terminated)

// user font
#define OVL_CMD_FONT_SETUP		110		// setup user font
#define OVL_CMD_FONT_DOWNLOAD	111		// download user font 
#define OVL_CMD_FONT_SAVE		112		// save current user font to flash
#define OVL_CMD_FONT_LOAD		113		// load user font from flash


//////////////////////////////////////////////////////////////////////////////
// Overlay Targets
//
#define OVL_TGT_NONE			0
#define OVL_TGT_OVERLAY			1
#define OVL_TGT_SPRITE1			2
#define OVL_TGT_SPRITE2			3
#define OVL_TGT_SPRITE3			4
#define OVL_TGT_SPRITE4			5


//////////////////////////////////////////////////////////////////////////////
// OVERLAY COORDINATE SYSTEM
// The origin (0,0 point) for the overlay/sprites is the upper left (NW)
// corner of the video. All coordinates are positive increasing from left
// to right and top to bottom.

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_POSITION
// Sets the overlay/sprite position in the video. The x,y position is the
// location of the top/left corner of the overlay/sprite with respect to
// the origin of the video.  Negative values are off the video display and
// will result in the overlay/sprite being cropped on the top/left sides
// as necessary.
//
typedef struct  
{
	short		x;								// upper left pixel/column
	short		y;								// upper left line/row

} OVERLAY_POSITION;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_POINTS
// Sets pixel value(s) in the overlay
//
typedef struct  
{
	USHORT		x;								// start pixel/column
	USHORT		y;								// start line/row
	USHORT		count;							// number of pixels to write
	USHORT		pixel[OVL_MAX_PIXELS];			// pixel data

} OVERLAY_POINTS;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_LINE
// Draws a line between to points (x1,y1 to x2,y2) in the overlay.
//
typedef struct  
{
	USHORT		x1;								// start pixel/column
	USHORT		y1;								// start line/row
	USHORT		x2;								// end pixel/column
	USHORT		y2;								// end line/row
	USHORT		pixel;							// pixel value

} OVERLAY_LINE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_RECTANGLE
// Draws a rectangle with an upper/left corner at x,y and with sides
// of length xLength and yLength.
//
typedef struct  
{
	USHORT		x;								// start pixel/column
	USHORT		y;								// start line/row
	USHORT		xLength;						// length in pixels/columns
	USHORT		yLength;						// length in lines/rows
	USHORT		pixel;							// pixel value

} OVERLAY_RECTANGLE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_SQUARE
// Draws a square with an upper/left corner at x,y and with the sides
// of length xLength and the y length calculated using the video
// aspect ratio.
//
typedef struct  
{
	USHORT		x;								// start pixel/column
	USHORT		y;								// start line/row
	USHORT		xLength;						// length in pixels/columns (y is calculated)
	USHORT		pixel;							// pixel value

} OVERLAY_SQUARE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_TRIANGLE
// Draws an isosceles triangle in a bounding rectangle with an upper/left
// corner at x,y and with sides of length xLength and yLength.
//
typedef struct  
{
	USHORT		x;								// start pixel/column
	USHORT		y;								// start line/row
	USHORT		xLength;						// length in pixels/columns
	USHORT		yLength;						// length in lines/rows
	USHORT		direction;						// direction (0=up, 1=right, 2=down, 3=left)
	USHORT		pixel;							// pixel value

} OVERLAY_TRIANGLE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_ELLIPSE
// Draws an ellipse centered at x,y and with a radius of length xRadius
// and yRadius.
//
typedef struct  
{
	USHORT		x;								// center pixel/column
	USHORT		y;								// center line/row
	USHORT		xRadius;						// radius in pixels/columns
	USHORT		yRadius;						// radius in lines/rows
	USHORT		pixel;							// pixel value

} OVERLAY_ELLIPSE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_CIRCLE
// Draws an ellipse centered at x,y and with a radius of length xRadius
// and y radius calculated using the video aspect ratio.
//
typedef struct  
{
	USHORT		x;								// center pixel/column
	USHORT		y;								// center line/row
	USHORT		xRadius;						// radius in pixels/columns
	USHORT		pixel;							// pixel value

} OVERLAY_CIRCLE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_ARC
// Draws an arc centered at x,y and with a radius of length xRadius
// and drawing start and stop point(s) on the circle.
// The start and stop points are 0.01 increments (30 degrees = 3000 counts).
// Y-radius is calculated using the video aspect ratio.
//
typedef struct  
{
	USHORT		x;								// center pixel/column
	USHORT		y;								// center line/row
	USHORT		xRadius;						// radius in pixels/columns
	USHORT		start;							// start point in 1/100 degrees
	USHORT		stop;							// stop point in 1/100 degrees
	USHORT		pixel;							// pixel value

} OVERLAY_ARC;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_DIAMOND
// Draws a diamond with an upper/left corner of the bounding rectangle
// at x,y and with dimensions of length xLength and yLength and a bit-map
// that allows each of the (4) segments to be drawn / not drawn
//
typedef struct
{
	USHORT		x;								// start pixel/column
	USHORT		y;								// start line/row
	USHORT		xLength;						// length in pixels/columns
	USHORT		yLength;						// length in lines/rows
	USHORT		segmentMap;						// line segment(s) not/drawn
	USHORT		pixel;							// pixel value

} OVERLAY_DIAMOND;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_COLORBAR
// Draws a color bar with an upper/left corner at x,y and with sides
// of length xLength and yLength.
//
typedef struct  
{
	USHORT		x;								// start pixel/column
	USHORT		y;								// start line/row
	USHORT		xLength;						// length in pixels/columns
	USHORT		yLength;						// length in lines/rows

} OVERLAY_COLORBAR;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_GRATICULE
// Draws a graticule centered at x,y and with a radius of length xLength.
//
typedef struct  
{
	USHORT		x;								// center pixel/column
	USHORT		y;								// center line/row
	USHORT		xRadius;						// radius in pixels/columns
	USHORT		pixel;							// pixel value

} OVERLAY_GRATICULE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_STRING
// Draws a text string with the upper/left corner of the first character's
// bounding rectangle at x,y, background and foreground colors, and NULL
// terminated (or up-to-buffer-length terminated) ASCII text. The high bit
// in each ASCII character is ignored.
//
typedef struct
{
	USHORT		x;								// left most position (pixel/column) of first character
	USHORT		y;								// top most position (line/row) of first character
	USHORT		pixelBackground;				// pixel value of character background
	USHORT		pixelForeground;				// pixel value of character foreground
	char		string[OVL_MAX_STRING_LEN];		// ASCII text string (NULL / buffer-length terminated)

} OVERLAY_STRING;


//////////////////////////////////////////////////////////////////////////////
// OVERLAY_FONT_SETUP
// Setup the current character size for the user defined font download.
// The size can be changed from character to character (or just set once).
//
typedef struct
{
	USHORT		xSize;						// number of pixels in a character (1 to 32)
	USHORT		ySize;						// number of lines in a character (1 to 32)

} OVERLAY_FONT_SETUP;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_FONT_DOWNLOAD
// Set the pixels in (part of) a character in the user defined font.
//
typedef struct
{
	UCHAR		character;					// font ASCII character to download (0 to 127)
	UCHAR		xStart;						// character start pixel (0 to 31)
	UCHAR		yStart;						// character start line (0 to 31)
	UCHAR		count;						// number of pixels to set (0 to 31)
	UCHAR		pixel[32];					// pixel data (luma only, 0=transparent, 1 to 255)

} OVERLAY_FONT_DOWNLOAD;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_FONT_SAVE
// Save the current user defined font to flash memory.
//
typedef struct
{
	USHORT		fontInfo;					// optional user defined font information tag

} OVERLAY_FONT_SAVE;

//////////////////////////////////////////////////////////////////////////////
// OVERLAY_FONT_STRING
// Draws a text string using the currently loaded user font with the
// upper/left corner of the first character's bounding rectangle at x,y
// and NULL terminated (or up-to-buffer-length terminated) ASCII text.
// The high bit in each ASCII character is ignored (0 to 127 only).
//
typedef struct
{
	USHORT		x;							// left most position (pixel/column) of first character
	USHORT		y;							// top most position (line/row) of first character
	USHORT		spare1;						// future chroma/alpha/etc...
	USHORT		spare2;
	char		string[OVL_MAX_STRING_LEN];	// ASCII text string (NULL / buffer-length terminated)

} OVERLAY_FONT_STRING;


//////////////////////////////////////////////////////////////////////////////
// OVERLAY_DATA
//
// Main overlay data structure is a union of all possible commands
// This structure is 36 bytes long
//
typedef struct
{
	union
	{
		OVERLAY_POSITION		position;

		OVERLAY_POINTS			points;
		OVERLAY_LINE			line;
		OVERLAY_RECTANGLE		rectangle;
		OVERLAY_SQUARE			square;
		OVERLAY_TRIANGLE		triangle;
		OVERLAY_ELLIPSE			ellipse;
		OVERLAY_CIRCLE			circle;
		OVERLAY_ARC				arc;
		OVERLAY_DIAMOND			diamond;

		OVERLAY_COLORBAR		colorbar;
		OVERLAY_GRATICULE		graticule;
		OVERLAY_STRING			string;

		OVERLAY_FONT_SETUP		fontSetup;
		OVERLAY_FONT_DOWNLOAD	fontDownload;
		OVERLAY_FONT_SAVE		fontSave;
		OVERLAY_FONT_STRING		fontString;

		USHORT					rawWords[OVL_DATA_SIZE/2];	// access to raw words
		UCHAR					rawBytes[OVL_DATA_SIZE];	// access to raw bytes

	} msg;

} OVERLAY_DATA;


/****************************************************************************/
#pragma pack(pop)	// reset to default packing

#endif //__MSG_OVL_FMT_H__
