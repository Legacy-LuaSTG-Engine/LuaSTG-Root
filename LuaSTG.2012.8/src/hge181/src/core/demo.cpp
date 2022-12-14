/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: HGE splash screen
*/


#include "hge_impl.h"

#ifdef DEMO

hgeQuad dquad;
float dtime;

unsigned char lstglogo[]={
	0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x08,0x03,0x00,0x00,0x00,0xF4,0xE0,0x91,
	0xF9,0x00,0x00,0x00,0x09,0x70,0x48,0x59,0x73,0x00,0x00,0x0B,0x13,0x00,0x00,0x0B,
	0x13,0x01,0x00,0x9A,0x9C,0x18,0x00,0x00,0x00,0x20,0x63,0x48,0x52,0x4D,0x00,0x00,
	0x7A,0x25,0x00,0x00,0x80,0x83,0x00,0x00,0xF9,0xFF,0x00,0x00,0x80,0xE9,0x00,0x00,
	0x75,0x30,0x00,0x00,0xEA,0x60,0x00,0x00,0x3A,0x98,0x00,0x00,0x17,0x6F,0x92,0x5F,
	0xC5,0x46,0x00,0x00,0x03,0x00,0x50,0x4C,0x54,0x45,0x00,0x00,0x00,0x01,0x01,0x01,
	0x02,0x02,0x02,0x03,0x03,0x03,0x04,0x04,0x04,0x05,0x05,0x05,0x06,0x06,0x06,0x07,
	0x07,0x07,0x08,0x08,0x08,0x09,0x09,0x09,0x0A,0x0A,0x0A,0x0B,0x0B,0x0B,0x0C,0x0C,
	0x0C,0x0D,0x0D,0x0D,0x0E,0x0E,0x0E,0x0F,0x0F,0x0F,0x10,0x10,0x10,0x11,0x11,0x11,
	0x12,0x12,0x12,0x13,0x13,0x13,0x14,0x14,0x14,0x15,0x15,0x15,0x16,0x16,0x16,0x17,
	0x17,0x17,0x18,0x18,0x18,0x19,0x19,0x19,0x1A,0x1A,0x1A,0x1B,0x1B,0x1B,0x1C,0x1C,
	0x1C,0x1D,0x1D,0x1D,0x1E,0x1E,0x1E,0x1F,0x1F,0x1F,0x20,0x20,0x20,0x21,0x21,0x21,
	0x22,0x22,0x22,0x23,0x23,0x23,0x24,0x24,0x24,0x25,0x25,0x25,0x26,0x26,0x26,0x27,
	0x27,0x27,0x28,0x28,0x28,0x29,0x29,0x29,0x2A,0x2A,0x2A,0x2B,0x2B,0x2B,0x2C,0x2C,
	0x2C,0x2D,0x2D,0x2D,0x2E,0x2E,0x2E,0x2F,0x2F,0x2F,0x30,0x30,0x30,0x31,0x31,0x31,
	0x32,0x32,0x32,0x33,0x33,0x33,0x34,0x34,0x34,0x35,0x35,0x35,0x36,0x36,0x36,0x37,
	0x37,0x37,0x38,0x38,0x38,0x39,0x39,0x39,0x3A,0x3A,0x3A,0x3B,0x3B,0x3B,0x3C,0x3C,
	0x3C,0x3D,0x3D,0x3D,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x40,0x40,0x40,0x41,0x41,0x41,
	0x42,0x42,0x42,0x43,0x43,0x43,0x44,0x44,0x44,0x45,0x45,0x45,0x46,0x46,0x46,0x47,
	0x47,0x47,0x48,0x48,0x48,0x49,0x49,0x49,0x4A,0x4A,0x4A,0x4B,0x4B,0x4B,0x4C,0x4C,
	0x4C,0x4D,0x4D,0x4D,0x4E,0x4E,0x4E,0x4F,0x4F,0x4F,0x50,0x50,0x50,0x51,0x51,0x51,
	0x52,0x52,0x52,0x53,0x53,0x53,0x54,0x54,0x54,0x55,0x55,0x55,0x56,0x56,0x56,0x57,
	0x57,0x57,0x58,0x58,0x58,0x59,0x59,0x59,0x5A,0x5A,0x5A,0x5B,0x5B,0x5B,0x5C,0x5C,
	0x5C,0x5D,0x5D,0x5D,0x5E,0x5E,0x5E,0x5F,0x5F,0x5F,0x60,0x60,0x60,0x61,0x61,0x61,
	0x62,0x62,0x62,0x63,0x63,0x63,0x64,0x64,0x64,0x65,0x65,0x65,0x66,0x66,0x66,0x67,
	0x67,0x67,0x68,0x68,0x68,0x69,0x69,0x69,0x6A,0x6A,0x6A,0x6B,0x6B,0x6B,0x6C,0x6C,
	0x6C,0x6D,0x6D,0x6D,0x6E,0x6E,0x6E,0x6F,0x6F,0x6F,0x70,0x70,0x70,0x71,0x71,0x71,
	0x72,0x72,0x72,0x73,0x73,0x73,0x74,0x74,0x74,0x75,0x75,0x75,0x76,0x76,0x76,0x77,
	0x77,0x77,0x78,0x78,0x78,0x79,0x79,0x79,0x7A,0x7A,0x7A,0x7B,0x7B,0x7B,0x7C,0x7C,
	0x7C,0x7D,0x7D,0x7D,0x7E,0x7E,0x7E,0x7F,0x7F,0x7F,0x80,0x80,0x80,0x81,0x81,0x81,
	0x82,0x82,0x82,0x83,0x83,0x83,0x84,0x84,0x84,0x85,0x85,0x85,0x86,0x86,0x86,0x87,
	0x87,0x87,0x88,0x88,0x88,0x89,0x89,0x89,0x8A,0x8A,0x8A,0x8B,0x8B,0x8B,0x8C,0x8C,
	0x8C,0x8D,0x8D,0x8D,0x8E,0x8E,0x8E,0x8F,0x8F,0x8F,0x90,0x90,0x90,0x91,0x91,0x91,
	0x92,0x92,0x92,0x93,0x93,0x93,0x94,0x94,0x94,0x95,0x95,0x95,0x96,0x96,0x96,0x97,
	0x97,0x97,0x98,0x98,0x98,0x99,0x99,0x99,0x9A,0x9A,0x9A,0x9B,0x9B,0x9B,0x9C,0x9C,
	0x9C,0x9D,0x9D,0x9D,0x9E,0x9E,0x9E,0x9F,0x9F,0x9F,0xA0,0xA0,0xA0,0xA1,0xA1,0xA1,
	0xA2,0xA2,0xA2,0xA3,0xA3,0xA3,0xA4,0xA4,0xA4,0xA5,0xA5,0xA5,0xA6,0xA6,0xA6,0xA7,
	0xA7,0xA7,0xA8,0xA8,0xA8,0xA9,0xA9,0xA9,0xAA,0xAA,0xAA,0xAB,0xAB,0xAB,0xAC,0xAC,
	0xAC,0xAD,0xAD,0xAD,0xAE,0xAE,0xAE,0xAF,0xAF,0xAF,0xB0,0xB0,0xB0,0xB1,0xB1,0xB1,
	0xB2,0xB2,0xB2,0xB3,0xB3,0xB3,0xB4,0xB4,0xB4,0xB5,0xB5,0xB5,0xB6,0xB6,0xB6,0xB7,
	0xB7,0xB7,0xB8,0xB8,0xB8,0xB9,0xB9,0xB9,0xBA,0xBA,0xBA,0xBB,0xBB,0xBB,0xBC,0xBC,
	0xBC,0xBD,0xBD,0xBD,0xBE,0xBE,0xBE,0xBF,0xBF,0xBF,0xC0,0xC0,0xC0,0xC1,0xC1,0xC1,
	0xC2,0xC2,0xC2,0xC3,0xC3,0xC3,0xC4,0xC4,0xC4,0xC5,0xC5,0xC5,0xC6,0xC6,0xC6,0xC7,
	0xC7,0xC7,0xC8,0xC8,0xC8,0xC9,0xC9,0xC9,0xCA,0xCA,0xCA,0xCB,0xCB,0xCB,0xCC,0xCC,
	0xCC,0xCD,0xCD,0xCD,0xCE,0xCE,0xCE,0xCF,0xCF,0xCF,0xD0,0xD0,0xD0,0xD1,0xD1,0xD1,
	0xD2,0xD2,0xD2,0xD3,0xD3,0xD3,0xD4,0xD4,0xD4,0xD5,0xD5,0xD5,0xD6,0xD6,0xD6,0xD7,
	0xD7,0xD7,0xD8,0xD8,0xD8,0xD9,0xD9,0xD9,0xDA,0xDA,0xDA,0xDB,0xDB,0xDB,0xDC,0xDC,
	0xDC,0xDD,0xDD,0xDD,0xDE,0xDE,0xDE,0xDF,0xDF,0xDF,0xE0,0xE0,0xE0,0xE1,0xE1,0xE1,
	0xE2,0xE2,0xE2,0xE3,0xE3,0xE3,0xE4,0xE4,0xE4,0xE5,0xE5,0xE5,0xE6,0xE6,0xE6,0xE7,
	0xE7,0xE7,0xE8,0xE8,0xE8,0xE9,0xE9,0xE9,0xEA,0xEA,0xEA,0xEB,0xEB,0xEB,0xEC,0xEC,
	0xEC,0xED,0xED,0xED,0xEE,0xEE,0xEE,0xEF,0xEF,0xEF,0xF0,0xF0,0xF0,0xF1,0xF1,0xF1,
	0xF2,0xF2,0xF2,0xF3,0xF3,0xF3,0xF4,0xF4,0xF4,0xF5,0xF5,0xF5,0xF6,0xF6,0xF6,0xF7,
	0xF7,0xF7,0xF8,0xF8,0xF8,0xF9,0xF9,0xF9,0xFA,0xFA,0xFA,0xFB,0xFB,0xFB,0xFC,0xFC,
	0xFC,0xFD,0xFD,0xFD,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,0xE2,0xB0,0x5D,0x7D,0x00,0x00,
	0x0B,0xFC,0x49,0x44,0x41,0x54,0x78,0xDA,0xEC,0x9A,0x7D,0x68,0x53,0xE7,0x1A,0xC0,
	0x9F,0xD3,0x68,0x13,0xAD,0x35,0xD5,0xCD,0xCD,0x38,0x74,0xD2,0x66,0x38,0x9C,0x78,
	0x75,0xC8,0xC4,0xE1,0x3A,0x86,0x4C,0x86,0x38,0x29,0x32,0x64,0xD8,0x20,0x63,0xC8,
	0x10,0x76,0x65,0x0C,0x64,0x0C,0xC6,0x16,0x10,0x11,0x44,0x2E,0xC3,0x22,0x45,0x44,
	0x44,0x64,0xCD,0x90,0xE2,0x18,0x83,0xA1,0xB4,0x28,0x56,0xB6,0x4B,0xAF,0xC5,0x8F,
	0xEC,0xBA,0xBB,0xD9,0xEA,0xDA,0x59,0x6D,0x62,0x6B,0x9A,0xE4,0xE4,0xBC,0xE7,0xBC,
	0xDF,0xCF,0xFD,0xE3,0x9C,0xA4,0xE9,0x87,0x4E,0x77,0x7B,0xDA,0x5D,0xF0,0xF9,0x27,
	0x39,0x1F,0xEF,0x79,0x7F,0x79,0xBE,0xDE,0xE7,0x7D,0x4E,0x00,0x9E,0xC8,0x13,0x79,
	0x22,0xFF,0xAF,0x52,0x51,0x31,0xCD,0x00,0x0B,0xFF,0x11,0x2A,0x7D,0x37,0x66,0x4C,
	0x03,0xC0,0xD3,0xFC,0xCE,0x62,0xEF,0xEB,0xB3,0xCD,0x4B,0x8C,0xA9,0x07,0x98,0xC9,
	0x34,0x7F,0xBF,0x02,0x00,0x66,0x1F,0xE4,0x6C,0xEE,0x34,0x68,0xC0,0x30,0x35,0xCA,
	0x8E,0xD9,0x33,0x76,0xDC,0xD3,0x78,0x3D,0x30,0x1D,0x00,0xD7,0xE9,0x65,0xAE,0x86,
	0x32,0xC4,0xE1,0xB8,0xD7,0x98,0x0E,0x80,0xE3,0xBC,0xA1,0x6E,0x40,0x98,0x5F,0xAE,
	0x2C,0xE8,0xE5,0xD3,0x12,0x06,0x1B,0xC5,0xB1,0x40,0xE5,0x47,0xCF,0xC3,0xD3,0x68,
	0x57,0x4D,0x0B,0xC0,0x1A,0xF5,0x6B,0x15,0x00,0xC0,0xBB,0x78,0x61,0x3A,0x5C,0x00,
	0xE6,0xDE,0x54,0x6D,0x41,0x00,0xA8,0xB8,0x31,0x3D,0x00,0x4B,0x06,0xD5,0x37,0x55,
	0x00,0x00,0xC6,0x6E,0x54,0xBB,0xA6,0x7E,0xFE,0xB5,0x84,0xED,0xF6,0xD2,0x5F,0xC5,
	0x29,0x54,0x6F,0x79,0xA7,0x1B,0xF6,0x4D,0x51,0x04,0x6C,0xE5,0xEA,0xD6,0x9E,0xE8,
	0x1C,0x77,0x39,0x08,0x74,0x20,0x5B,0x09,0x00,0x00,0x21,0xBB,0x30,0x7F,0x4A,0x00,
	0xE6,0xB4,0x65,0x0A,0x26,0x61,0xD6,0xF5,0x6A,0xA8,0x6C,0xD8,0xF3,0xE9,0x05,0xA6,
	0xAC,0x25,0x00,0x00,0x9F,0x2B,0x79,0x74,0xAA,0xB2,0x40,0xD5,0xF2,0x0F,0x3A,0x72,
	0xD6,0x3A,0x38,0xC0,0x85,0x90,0x9C,0xD2,0xDE,0x2A,0x80,0xA0,0xA9,0xF5,0x50,0x78,
	0x0A,0x1D,0xE1,0x43,0x7E,0x7C,0x5E,0x26,0xBF,0xE7,0x95,0xF5,0x6B,0x5F,0x7E,0x69,
	0x79,0x35,0xC0,0x27,0x5A,0xA3,0xFA,0x64,0x0A,0x01,0x22,0xF4,0x87,0xF3,0xF6,0xD1,
	0x52,0x5D,0x10,0x1A,0xD4,0x1A,0x71,0x70,0xCE,0xD4,0x01,0xCC,0xE8,0xCC,0x59,0x83,
	0x4B,0x4B,0x87,0xDB,0xA5,0xD2,0x88,0x7A,0xFB,0x14,0xAA,0x60,0x87,0x70,0x8E,0x94,
	0x14,0x30,0xAB,0x8F,0x0B,0xAE,0x11,0xEF,0xCD,0x9E,0x3A,0x80,0x05,0xD9,0xFB,0xB5,
	0xA5,0x83,0x06,0xEE,0x90,0xBD,0x0A,0x51,0x6F,0x98,0x3A,0x80,0xC0,0xD5,0x33,0x25,
	0x05,0x04,0xD3,0x94,0x75,0x3C,0x73,0x11,0x11,0x6F,0x57,0x4E,0x61,0x42,0x2C,0x7A,
	0x80,0x11,0xD8,0x2E,0xED,0xFC,0x4E,0xE3,0x69,0x44,0x54,0x6B,0xA6,0xB2,0x3C,0x30,
	0x02,0xC1,0xB9,0x8B,0xD6,0xEC,0x68,0xEE,0x24,0x94,0x76,0x85,0xC1,0xB8,0x86,0xA8,
	0xB3,0x5F,0xBE,0xFA,0xEC,0xEC,0x29,0xA9,0x53,0x8D,0xDA,0x5D,0x27,0xBB,0xEE,0x16,
	0x84,0xD2,0x5A,0x0B,0x66,0x7E,0x68,0x00,0x2C,0x41,0x44,0x44,0x94,0x99,0xAE,0x2F,
	0x37,0x2E,0xA9,0xF6,0x9B,0xC2,0xD8,0x22,0x35,0x22,0x2A,0x29,0x95,0x52,0xBA,0xB7,
	0x1A,0x00,0x2A,0x6E,0xB9,0x04,0x5A,0x6B,0xE5,0xA4,0x93,0x5F,0x2F,0xF0,0x79,0x77,
	0x72,0x50,0x2A,0xA5,0xB5,0xC8,0xFE,0xD2,0xFA,0xD1,0xBA,0x6A,0x03,0x00,0xE0,0xA9,
	0x2E,0x0B,0x11,0xB5,0x92,0x52,0x4A,0xA5,0x4E,0xCD,0xF4,0x7B,0x7F,0x74,0x5A,0x29,
	0x7D,0x7D,0x7F,0x4D,0xA0,0xA2,0xE4,0x78,0x15,0x33,0xAA,0x5E,0xF8,0xE8,0x32,0x51,
	0x52,0x48,0x71,0xD0,0x97,0xED,0x93,0x11,0x9C,0x3F,0xE2,0xE6,0x81,0x4E,0xA5,0xF8,
	0x8F,0x1F,0x8E,0x35,0xB6,0xB1,0x53,0x49,0x25,0xF6,0xF8,0x13,0x0E,0xDB,0x52,0xD9,
	0xDA,0xB2,0x7C,0xDC,0xA3,0x24,0xED,0xFE,0x38,0x30,0x76,0x7E,0xA5,0xE5,0x2E,0x7F,
	0xE6,0xAF,0xC8,0x98,0xD6,0x95,0xE0,0xC8,0x71,0xF0,0xA6,0x12,0x2C,0xB5,0xAB,0x5C,
	0xD9,0xC6,0x67,0x5A,0x69,0xB9,0xCD,0x27,0xB3,0x07,0xAD,0x42,0x86,0x7C,0x56,0xF6,
	0xE3,0x66,0x0F,0x6A,0xC1,0xEE,0xEF,0x18,0x21,0x30,0xF6,0x29,0xA9,0xC4,0x9B,0x7E,
	0xF9,0xDD,0xE2,0x02,0xC9,0x65,0x73,0x65,0x46,0x80,0x9A,0xBC,0x12,0xEC,0x42,0x69,
	0xB3,0x1C,0x38,0x28,0x84,0xB4,0x5F,0xF6,0x6F,0x43,0x62,0x11,0x2B,0x9B,0xBF,0x51,
	0x9E,0xF0,0x97,0x39,0x92,0x7D,0x52,0xF2,0xC3,0x67,0x4D,0xC6,0xF2,0x3E,0x6E,0x96,
	0x3E,0xB7,0x6D,0xC7,0xCA,0x64,0x9B,0xCA,0x8C,0xF0,0xBC,0x2D,0xED,0x2D,0xA5,0xA3,
	0xF9,0x19,0x46,0xFF,0x15,0xF4,0x0F,0xA0,0x87,0x39,0x94,0x15,0x86,0x86,0x56,0x8F,
	0x9C,0xDA,0xC0,0x65,0x76,0xAD,0x6B,0x7E,0x00,0xA8,0xEC,0xE7,0xEC,0x97,0x1A,0xFF,
	0x52,0xCF,0x30,0x67,0x8C,0xF3,0x5C,0xA6,0x7B,0xA4,0xF0,0xD8,0xA7,0x44,0xCF,0x8B,
	0x00,0x30,0x73,0xD9,0xE6,0x59,0x00,0xC6,0xAF,0x82,0xA6,0x9E,0xF7,0x0D,0xA0,0xDA,
	0x14,0x9C,0x0B,0x49,0x33,0xD9,0xE3,0x25,0xBF,0x3F,0xA3,0x58,0xEB,0x7C,0x08,0xBD,
	0x9E,0xB4,0x73,0x57,0x57,0x56,0xC2,0x39,0xEE,0x64,0xFD,0xF3,0xC1,0xE5,0x8E,0x14,
	0x42,0x4A,0x69,0x65,0x32,0x6B,0x8B,0x4A,0xB9,0x2A,0x9D,0x37,0x97,0x6D,0xED,0x13,
	0xCC,0xB2,0xCD,0xF4,0xBE,0x79,0x27,0x89,0x4D,0x1A,0xFC,0xAB,0x03,0xB9,0x74,0x65,
	0x38,0xDB,0xE3,0x15,0xC0,0xB3,0xEE,0x48,0xA7,0x6D,0x40,0x08,0x87,0x52,0x42,0xAC,
	0x4C,0xEB,0xF7,0x05,0x62,0x7F,0xEC,0x1B,0xC0,0xF7,0x4A,0x4A,0xA9,0xA4,0x54,0x6C,
	0x30,0xD7,0xEC,0x26,0xE0,0xA7,0x4C,0xC5,0x29,0x75,0xA8,0xDD,0xBA,0x25,0x65,0x13,
	0x7B,0x78,0xA8,0x60,0x95,0x55,0xEB,0x93,0x2D,0xBD,0x4A,0x4A,0xA9,0x94,0x52,0xD2,
	0x4A,0x67,0xD6,0x00,0x00,0xC0,0x52,0xA6,0x04,0xB3,0x73,0x47,0xC2,0x15,0x46,0x30,
	0x5E,0xB0,0x6D,0x62,0x11,0xE7,0xAC,0x5F,0x85,0xE1,0xCC,0xB4,0x37,0xBF,0x92,0x7C,
	0x78,0xA0,0xBB,0x1A,0x00,0x60,0x93,0x56,0x2C,0x13,0x9F,0x6D,0x00,0x00,0x18,0x35,
	0x17,0x88,0x43,0x88,0x9D,0xF4,0x6B,0x7F,0xF2,0x54,0x5E,0x4A,0x29,0xB8,0x52,0x52,
	0x0A,0xFB,0xEE,0xC0,0xF1,0x00,0x00,0x1C,0xD6,0xFD,0xEF,0x97,0x25,0x9E,0xBF,0xFD,
	0xE2,0x50,0xFB,0x8E,0x5F,0xA5,0xD0,0x0A,0x47,0x4A,0xE5,0x1C,0xB9,0xAF,0xA5,0x10,
	0xDC,0xEC,0x4D,0x6F,0x00,0x30,0x36,0x6E,0x1F,0xBD,0x18,0xCF,0xD8,0xDE,0x2F,0xAD,
	0xA8,0x4F,0x00,0x3B,0x85,0x10,0x8A,0xAC,0xFB,0x4C,0x4A,0x2E,0x04,0x1F,0xEA,0xFB,
	0x7D,0x1E,0x4C,0xB0,0xEA,0x57,0x1F,0xCE,0x2C,0xF3,0x09,0xE0,0x94,0xE2,0x42,0x0D,
	0xAD,0x5F,0x71,0x86,0x0B,0xCE,0x85,0x73,0x77,0xE0,0xEC,0x84,0x0D,0x22,0x63,0xAE,
	0x4F,0x7D,0xA3,0x8A,0x2B,0x92,0x71,0xF9,0x5B,0xFD,0xB2,0xE0,0x2D,0xC1,0x39,0x17,
	0xE6,0x9D,0x81,0xF1,0x9B,0x51,0xC3,0x30,0x0C,0x63,0x46,0xD0,0x97,0x7A,0x28,0xD8,
	0x27,0x19,0xE3,0x57,0x36,0x2D,0x82,0x67,0x28,0xE7,0x42,0xF0,0xC1,0xDE,0xAE,0x97,
	0x17,0xD5,0x2E,0xAD,0x7B,0x71,0xC5,0xEA,0x57,0xD6,0x6F,0xDC,0xB2,0x75,0xDB,0xB6,
	0xED,0x3B,0x76,0xEC,0xD8,0xBE,0xFD,0x83,0x03,0xEB,0x7C,0xC9,0x04,0x0B,0xF2,0x92,
	0x31,0x7A,0xF6,0x83,0x1A,0x80,0x8F,0x04,0x17,0x82,0xD3,0xEE,0x33,0x89,0xAF,0x4E,
	0x1E,0x3D,0x72,0xE4,0xC4,0xC9,0x53,0xDF,0xB5,0x75,0x74,0x5E,0xBA,0x7C,0xF5,0xDF,
	0xFF,0xE9,0xEE,0xED,0x1F,0x6E,0xF5,0x27,0x11,0xAC,0xE0,0x9C,0x73,0x3B,0xB1,0xAB,
	0x0A,0x20,0xD0,0xA3,0x38,0xE7,0x9C,0xDA,0x0E,0xA5,0x8E,0x4D,0x08,0x71,0x28,0x17,
	0x42,0x4A,0x29,0xA5,0x92,0x3A,0xE7,0xCB,0x7A,0x5C,0x51,0xB9,0x5F,0x71,0x2E,0x48,
	0xD3,0x3B,0x95,0x00,0x30,0x8F,0x4A,0xCE,0x19,0x63,0x94,0x3A,0x36,0xB1,0x2C,0xCB,
	0x66,0x5C,0x78,0xEB,0x84,0xE2,0x3E,0x54,0x44,0x95,0xD5,0xB5,0x3B,0xBE,0x37,0x05,
	0xE7,0x22,0x1F,0xAF,0x0F,0x00,0x80,0x11,0x53,0x9C,0x51,0xEA,0x38,0xC4,0xB2,0x2C,
	0x8B,0x38,0x8C,0x0B,0x29,0x95,0x52,0x52,0x2A,0xF5,0xDE,0x64,0x37,0x02,0xAA,0x6B,
	0xB7,0x7C,0x75,0xCB,0xB4,0xB9,0xE0,0x9C,0xF1,0x7B,0xFB,0x57,0x18,0x00,0x00,0x81,
	0x6B,0x8A,0x3A,0xB6,0x4D,0x0A,0x05,0xCB,0x22,0x0E,0x13,0x42,0xB9,0x22,0xF5,0xE9,
	0xC9,0x8C,0x00,0x63,0xF6,0xE2,0xB7,0x0E,0x27,0xB3,0x0E,0xE5,0x9E,0xB0,0xEE,0x66,
	0xEF,0x65,0xCD,0xD3,0x39,0xEE,0x6A,0x9F,0x38,0x94,0x09,0xA9,0x94,0xD2,0x4A,0x2B,
	0xA5,0x6F,0x4C,0xDE,0xAE,0x78,0x46,0xE4,0x8D,0x83,0x9D,0x29,0x9B,0xB9,0xE2,0x01,
	0x5C,0xDE,0x5B,0xF4,0xB0,0x37,0x6E,0x24,0x3B,0x2F,0x9C,0x6D,0xFD,0xEA,0xD4,0xA9,
	0xD6,0xD6,0xAF,0x8F,0xFF,0x24,0xB5,0xD6,0x5A,0x6B,0xB3,0x7A,0xB2,0x7C,0xAE,0x66,
	0x57,0x47,0xAF,0xC9,0x38,0x17,0x9C,0x51,0x87,0x32,0xC6,0x39,0x17,0x52,0x90,0x03,
	0x55,0xA3,0x73,0x8E,0x61,0x18,0x86,0x01,0x50,0xF1,0x83,0xD6,0x5A,0x6B,0x94,0x75,
	0x93,0xB6,0xFB,0xCF,0x3B,0xC5,0xDF,0xCD,0x28,0xA5,0x5C,0x28,0xE9,0xDC,0xEF,0x6E,
	0x5E,0x31,0x71,0x96,0x35,0x76,0xB9,0xF3,0xEB,0x77,0x26,0x2F,0xEB,0x9C,0x67,0x8C,
	0x52,0x17,0x80,0x0B,0x6E,0xFD,0xDE,0xB9,0x77,0xCD,0x83,0x97,0xF9,0xE5,0x52,0x2B,
	0xAD,0x11,0x4F,0x4E,0x62,0x06,0x0C,0xBC,0x6B,0x09,0x57,0xF3,0xF6,0xC0,0x95,0x33,
	0xDF,0x3D,0xF7,0xB0,0x7B,0xE7,0x38,0xA8,0xB5,0xD6,0x78,0x6B,0x72,0xDB,0x32,0x8B,
	0xBA,0x25,0xA3,0x8C,0x71,0xE7,0xDC,0xFA,0xD5,0xB1,0xAD,0x0F,0x69,0x44,0x07,0x6E,
	0xBB,0xF3,0x5B,0x93,0x5D,0x09,0xCD,0xDC,0xCF,0x38,0xA5,0xD4,0x29,0x5C,0x8B,0xEF,
	0x3E,0x96,0x58,0xFB,0xA0,0xF8,0x36,0x4E,0x23,0xA2,0xD6,0x28,0x6B,0x27,0xBF,0x1F,
	0xB2,0xEC,0x3E,0xA3,0xB6,0x6D,0x93,0xFB,0x17,0x4F,0x7E,0xD7,0x79,0x60,0xD6,0xC4,
	0x77,0x6D,0xD5,0x88,0x38,0xA9,0x0E,0x58,0x26,0xA1,0x73,0x84,0x12,0x8B,0x10,0xEB,
	0x76,0xE7,0x0F,0xC9,0xAE,0xBA,0x89,0x7C,0x6C,0xB1,0x74,0x15,0x70,0xDC,0x9F,0x9E,
	0x88,0xB1,0x69,0xC8,0x29,0x14,0x2C,0x42,0xF3,0xDD,0xC9,0x9F,0xFB,0x77,0x05,0x27,
	0xE8,0x59,0x20,0x22,0x6A,0xBC,0xEE,0x5B,0x5F,0xF0,0xA9,0x7F,0x52,0xDB,0x22,0x36,
	0x25,0xF7,0x6E,0xF5,0x0E,0x5E,0x5A,0x34,0x46,0x09,0x95,0xBF,0x22,0x6A,0xD4,0x58,
	0xF0,0xB1,0x4F,0x3E,0xF3,0x83,0x02,0xB5,0x08,0xB1,0x49,0xF6,0x6E,0x7F,0xE6,0xCE,
	0xC2,0x31,0x45,0x82,0x46,0x8D,0x1A,0x55,0xD2,0xD7,0xC6,0xE8,0xE2,0x1E,0xDB,0x22,
	0x96,0x65,0xE5,0x87,0x7A,0x2F,0xAD,0x19,0x7D,0x69,0x56,0x1E,0x35,0xA2,0xCE,0x65,
	0x5F,0xF2,0xB5,0x27,0x19,0x3C,0x40,0xAC,0x82,0x69,0x16,0xCC,0x1F,0xBF,0x59,0x3D,
	0xE6,0xD2,0x61,0xD4,0x5A,0x6B,0x92,0xB9,0xE8,0xEF,0x2B,0x54,0x63,0x75,0xDA,0x34,
	0x4D,0xD3,0x3C,0xFF,0xED,0x58,0x80,0x79,0x14,0xB5,0xD6,0x22,0x9B,0xF7,0xB9,0x33,
	0x0C,0xD5,0x37,0x2C,0xD3,0x34,0x3B,0xBE,0x79,0x65,0xEC,0x85,0x2B,0x5A,0x6B,0xAD,
	0x48,0xEE,0x98,0xCF,0x00,0x81,0x13,0x8E,0x69,0x9A,0x17,0xBE,0x7A,0x65,0xA4,0x48,
	0x74,0x3F,0x97,0x0A,0xAD,0x94,0xE6,0xF9,0xA1,0x59,0xFE,0x02,0x54,0x1C,0x76,0xCC,
	0x82,0x79,0xE1,0x48,0xB1,0xFF,0x12,0xD8,0x72,0x7E,0x63,0xB5,0x01,0x00,0x46,0x5A,
	0x29,0xA5,0x95,0x95,0xDF,0xED,0x33,0x40,0x93,0x93,0x37,0xCD,0x73,0x07,0x3D,0x80,
	0xCA,0xBD,0x03,0x77,0xEF,0x5D,0x79,0x6F,0xA1,0x01,0xF0,0x86,0x56,0x4A,0x69,0x5A,
	0xF8,0xCD,0x5F,0x37,0xAC,0xD8,0x4F,0x4D,0xD3,0x6C,0xFF,0xD4,0x75,0xC2,0x79,0x3F,
	0x3A,0x66,0xAA,0xA7,0xFB,0xF7,0x4B,0x9F,0xBE,0x58,0x61,0x98,0x4A,0x29,0x25,0x0B,
	0xB9,0x57,0xFD,0x8D,0x83,0x4F,0x98,0x69,0x9A,0x67,0x76,0xAE,0x04,0x00,0xE3,0xA5,
	0xDB,0xD4,0xB6,0x49,0x61,0xE0,0xA7,0xAE,0xAB,0x67,0xF6,0xAD,0x39,0xA1,0xA4,0x94,
	0xCA,0xB6,0x2E,0xFA,0xFA,0xC2,0xCA,0xD8,0x49,0xF3,0x66,0xFE,0xDB,0x86,0xE5,0x00,
	0x81,0x86,0x8C,0x43,0x2C,0xCB,0xA6,0x94,0xF4,0x77,0xB4,0x1E,0xDD,0x77,0x5C,0x08,
	0x2E,0x24,0xB3,0x06,0x17,0xFB,0xAA,0x82,0x77,0x58,0x3E,0x9F,0x3F,0xBD,0xBE,0x0E,
	0x2A,0x9B,0x0B,0x36,0x21,0x96,0x65,0x53,0xC6,0xB9,0xD3,0xD7,0xFA,0xF1,0xB6,0xDF,
	0x25,0x17,0x42,0x58,0xF6,0x41,0x5F,0x01,0x36,0xB2,0x5C,0x2E,0x97,0x78,0x21,0x32,
	0xFF,0x22,0x21,0x84,0x10,0xCB,0x71,0x1C,0xCA,0x18,0x17,0x4E,0xCF,0xE7,0xCD,0x82,
	0x73,0x21,0xA8,0xD5,0x57,0xED,0x27,0xC0,0xEB,0x34,0x9B,0xCD,0x36,0xCF,0xDB,0xDC,
	0x6F,0x9B,0x05,0xCB,0x22,0x34,0x6D,0x0B,0x4A,0x29,0xE7,0x5C,0xD8,0x37,0x2D,0xCE,
	0x38,0xE7,0x05,0x67,0x8B,0x9F,0x00,0x6B,0x59,0x66,0x38,0x73,0xE4,0xBD,0x01,0x2B,
	0x97,0xCF,0x9B,0x16,0x3D,0xB5,0xE0,0xE5,0x0E,0x2A,0xDC,0xC2,0x5D,0x30,0xCA,0x18,
	0xE7,0x36,0xE9,0xF2,0xF3,0xCD,0xED,0x4A,0x7A,0x3F,0x93,0xE9,0x1D,0xCA,0x67,0x86,
	0xB3,0xD9,0x82,0xF9,0x6E,0x00,0x60,0x46,0xED,0x37,0x4C,0x72,0x6F,0x97,0xCC,0x18,
	0x73,0x4C,0xF2,0xA2,0x8F,0x00,0xCB,0x9C,0xA1,0xA1,0xFB,0xC3,0x99,0xA1,0x4C,0x26,
	0x93,0xFB,0x6D,0xB1,0x1B,0x71,0x81,0xF9,0xCD,0x8E,0xE4,0x8C,0x51,0xEA,0x50,0x4A,
	0xA9,0xE5,0x24,0x7C,0x4C,0x46,0x4B,0xC9,0x60,0xFA,0x5E,0xFA,0xDE,0xE0,0x50,0x26,
	0x73,0x6C,0xA4,0x32,0x33,0xAA,0xF6,0x14,0x18,0x63,0xD4,0x71,0x1C,0x87,0xDA,0xA6,
	0x39,0xCF,0x3F,0x80,0xE7,0x72,0xE9,0x74,0x6A,0x20,0x3D,0x38,0x9C,0x7E,0x73,0x74,
	0x59,0x56,0xD9,0x30,0x40,0x38,0xB5,0x6D,0x9B,0x3A,0x05,0xB2,0xDB,0xBF,0x64,0xB4,
	0x20,0x9D,0xBE,0x7B,0xFB,0x4E,0x7A,0xF8,0xE7,0x45,0xE3,0xD3,0xF4,0xAB,0x97,0xF2,
	0x9C,0xDA,0xC4,0xB6,0xF2,0x03,0xFE,0xB9,0x61,0xB8,0xE7,0x4E,0x5F,0xDF,0x9D,0xC1,
	0xB2,0xBF,0x93,0x96,0x4B,0xED,0x89,0x21,0x41,0x09,0xC9,0x9B,0x9B,0xFC,0xAB,0x48,
	0xBA,0x6E,0xDF,0xEC,0xEB,0x5F,0xFF,0xC0,0xED,0xE7,0x82,0x3D,0xFD,0xD2,0x31,0xF3,
	0xA7,0x7D,0xB3,0xC1,0xAC,0x33,0x37,0x7B,0xBA,0x1E,0xBE,0x47,0xDD,0xD0,0xCD,0x2D,
	0xFF,0xD6,0x83,0xE0,0xB1,0xDF,0x4E,0xFC,0xD1,0xEE,0xB3,0x72,0xE5,0x3A,0xFF,0x9C,
	0x70,0xE6,0xE1,0xDD,0xD3,0xF1,0x17,0xE2,0xB2,0x96,0x51,0x78,0xBA,0xFF,0x4F,0xFD,
	0x44,0x9E,0xC8,0x13,0xF9,0x0B,0x4B,0x38,0x1C,0x0E,0x01,0x84,0x1E,0xD8,0xC9,0xAB,
	0x0B,0x45,0xC2,0x00,0x10,0x0E,0xFD,0xF1,0xA3,0x52,0xEE,0x9F,0xB1,0xF0,0x35,0x00,
	0x00,0x68,0xF2,0x8E,0x0E,0x01,0x6C,0x46,0x44,0x6C,0x74,0x6F,0x8A,0x21,0x22,0x62,
	0xA9,0x8F,0xD5,0x98,0xC4,0x58,0x23,0xB6,0xC5,0xDA,0x9B,0x00,0x10,0x31,0xE6,0x5E,
	0x6E,0x8C,0x79,0xF7,0x84,0xE2,0x29,0xAC,0x6B,0xC1,0x74,0xFC,0xED,0x54,0xE3,0x1F,
	0x03,0xD4,0xBB,0x04,0x4D,0x35,0x00,0x00,0x10,0x6D,0x47,0x44,0xC4,0xF6,0x28,0x40,
	0x4D,0x3B,0x62,0xBB,0x7B,0xD6,0xE3,0xF2,0xDE,0x4E,0x86,0x93,0x88,0x87,0x6A,0xC2,
	0x31,0x44,0x4C,0x00,0x20,0xE2,0xEA,0x46,0x17,0x60,0xB5,0x0B,0xB0,0x30,0x85,0x18,
	0x0F,0x45,0x5E,0xBB,0x86,0x88,0xB1,0x47,0xD0,0x66,0x4B,0xF9,0xC3,0xC1,0x7D,0x56,
	0x0C,0x00,0x20,0x84,0x58,0xD4,0xE0,0xE6,0x91,0xB3,0x00,0xED,0x88,0x49,0x00,0x80,
	0x08,0x62,0x0B,0x00,0x62,0xAC,0x34,0x28,0x86,0x08,0x50,0x93,0x42,0x77,0x60,0xA8,
	0xAD,0xA4,0xC1,0x87,0x4A,0x62,0x02,0x00,0x77,0x5C,0x22,0xE1,0x9D,0x8C,0x44,0x10,
	0xDD,0xDF,0x0B,0x00,0xAB,0x4A,0xDF,0x62,0xAE,0x06,0x42,0x9E,0x85,0x1A,0x21,0x84,
	0xE8,0x3D,0xCF,0x35,0x55,0xEA,0x4F,0x6B,0x60,0x0C,0xC0,0x6E,0xC0,0x11,0x27,0x88,
	0x23,0x22,0xD6,0xBB,0x2A,0x4A,0x00,0x60,0x5B,0x99,0xDA,0xDA,0x10,0xA2,0x65,0xEE,
	0xF2,0xF7,0x47,0x02,0x18,0xAD,0x81,0x58,0x39,0x40,0x8B,0x77,0x32,0x19,0x75,0x6F,
	0x8A,0x8C,0x00,0x27,0xA2,0x00,0x90,0x88,0x03,0x60,0xBC,0x8C,0x3A,0x8E,0x70,0xA8,
	0x0C,0x20,0xF2,0xA7,0x01,0xDC,0x71,0x2D,0x9E,0x06,0xC2,0xB8,0xCA,0x9D,0xE2,0x6D,
	0x00,0xF0,0x66,0x40,0x4C,0xD6,0xBB,0x93,0x84,0xCA,0x06,0x05,0x23,0x5E,0x54,0x79,
	0x4F,0xFB,0x22,0xF2,0xC8,0x00,0x75,0xE3,0x9D,0xB0,0x64,0x82,0x7A,0x0C,0xAD,0x72,
	0x43,0x05,0x00,0xE0,0x6D,0x2C,0x4A,0x32,0x32,0x7E,0x50,0x0D,0x8E,0x8A,0x58,0xF8,
	0x5F,0xA2,0xA0,0x04,0xD0,0x94,0x80,0x10,0x22,0x22,0xA6,0x00,0x00,0x42,0xE9,0x12,
	0x41,0x2A,0x32,0x4E,0x6D,0xD1,0xC7,0x07,0x78,0xB0,0x09,0x8A,0x3E,0x90,0x6E,0x04,
	0xB8,0x86,0x88,0x88,0x61,0x00,0x80,0xC8,0x08,0x41,0x72,0x9C,0xE3,0x14,0x01,0x42,
	0xDE,0x1D,0xD1,0x49,0xD0,0x40,0x04,0x23,0x9E,0xEF,0xA3,0x67,0xF6,0xF6,0x12,0x41,
	0x74,0x2C,0x75,0xB8,0xA8,0x81,0x48,0xA2,0x64,0xB4,0x47,0x07,0xA8,0x1B,0x1D,0x86,
	0x9E,0x13,0xC6,0xD2,0x00,0x50,0x8F,0x88,0x88,0x71,0x00,0x88,0xD6,0x03,0xD4,0x27,
	0x3C,0x80,0xC6,0x71,0x6A,0x2B,0x39,0x61,0x0C,0x1F,0x31,0x13,0x8E,0x98,0x60,0x15,
	0x46,0x27,0x02,0x48,0x34,0xAD,0x2E,0x57,0x79,0x02,0x01,0x00,0xA2,0x2D,0x65,0x93,
	0x96,0x03,0x34,0x15,0x01,0x1A,0x1F,0x1F,0x20,0x8E,0x75,0xA3,0xF2,0x40,0x7B,0x1C,
	0x00,0x00,0xB0,0x3E,0x1A,0xF3,0xD6,0x1B,0x0C,0x03,0xB4,0xA0,0xDB,0xB7,0x7B,0x7B,
	0x42,0x13,0x8C,0x24,0xA2,0xC7,0xD7,0x40,0x28,0x35,0x5A,0x03,0x61,0xD7,0xE4,0xAB,
	0x5C,0xD7,0x73,0x6F,0x5B,0x05,0xD0,0x82,0xED,0xEE,0x40,0x44,0x4C,0x8F,0xCF,0x5E,
	0xAE,0x49,0x1F,0x47,0x03,0x25,0x1F,0x68,0x42,0xAC,0xF3,0x9C,0x28,0x0E,0x00,0x70,
	0x28,0x1D,0x82,0x92,0xCA,0xBD,0x49,0x76,0x03,0x24,0xBC,0xCB,0x51,0x97,0x67,0x1C,
	0x40,0x71,0x31,0x6A,0x2C,0xA5,0xAE,0x47,0x5A,0x8E,0xA3,0xF5,0x49,0x17,0x63,0x55,
	0xCA,0x1D,0xF8,0x5A,0x1B,0xD6,0x03,0x40,0xF8,0x10,0xE2,0xA1,0x1A,0x80,0x90,0xEB,
	0xF9,0xA9,0x28,0x24,0x10,0xB1,0x29,0x12,0xAA,0x4F,0x15,0x83,0x02,0xA2,0x6D,0x88,
	0x88,0xD8,0xE6,0x45,0x52,0x24,0x85,0x18,0x0F,0x45,0x93,0x88,0xB8,0xF9,0x11,0x14,
	0xE0,0x05,0xB5,0x9B,0xED,0xA3,0x00,0x10,0xFA,0x22,0x8D,0x88,0x80,0xC9,0x55,0xEE,
	0x7A,0xE2,0x2A,0xB2,0x98,0xFF,0xDA,0xA1,0xA9,0x3D,0x96,0xC0,0x44,0x1D,0xE2,0xA1,
	0x62,0xF6,0x2C,0x56,0x31,0xC5,0x98,0x0B,0xC5,0xD3,0x18,0x6D,0xC1,0xD4,0x17,0x35,
	0x7F,0xB6,0xE0,0x8A,0x44,0xA3,0xF0,0xC0,0x2C,0x1E,0x0A,0x01,0x84,0x22,0xA1,0xE8,
	0x43,0xAB,0xAD,0x68,0x28,0x12,0x81,0x27,0xF2,0x57,0x94,0xFF,0x0E,0x00,0xA8,0xD1,
	0x6D,0x80,0x62,0xE4,0x29,0x84,0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,0xAE,0x42,
	0x60,0x82
};

void DInit() {
	int x=pHGE->System_GetState(HGE_SCREENWIDTH)/2;
	int y=pHGE->System_GetState(HGE_SCREENHEIGHT)/2;
	
	dquad.tex=pHGE->Texture_Load((char *)lstglogo, sizeof(lstglogo));
	dquad.blend=BLEND_DEFAULT;

	for(int i=0; i<4; i++) {
		dquad.v[i].z=0.5f;
		dquad.v[i].col=0xFFFFFFFF;
	}

	dquad.v[0].tx=0.0f; dquad.v[0].ty=1.0f;
	dquad.v[1].tx=1.0f; dquad.v[1].ty=1.0f;
	dquad.v[2].tx=1.0f; dquad.v[2].ty=0.0f;
	dquad.v[3].tx=0.0f; dquad.v[3].ty=0.0f;

	dquad.v[0].x=x-64.5f; dquad.v[0].y=y-64.5f;
	dquad.v[1].x=x+63.5f; dquad.v[1].y=y-64.5f;
	dquad.v[2].x=x+63.5f; dquad.v[2].y=y+63.5f;
	dquad.v[3].x=x-64.5f; dquad.v[3].y=y+63.5f;

	dtime=0.0f;
}

void DDone() {
	pHGE->Texture_Free(dquad.tex);
}

bool DFrame() {
	BYTE alpha;
	DWORD col;

	dtime+=pHGE->Timer_GetDelta();

	if(dtime<0.5) alpha=(BYTE)((dtime*2)*0xFF);
	else if(dtime<1.5) alpha=0xFF;
	else if(dtime<2.0) alpha=(BYTE)((1.0f-(dtime-1.5f)*2)*0xFF);
	else return true;

	col=0xFFFFFF | (alpha<<24);
	dquad.v[0].col=col;
	dquad.v[1].col=col;
	dquad.v[2].col=col;
	dquad.v[3].col=col;

	pHGE->Gfx_BeginScene();
	pHGE->Gfx_Clear(0);
	pHGE->Gfx_RenderQuad(&dquad);
	pHGE->Gfx_EndScene();

	return false;
}

#endif