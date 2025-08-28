/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

 /* Derived from code by Ethan Lee (Copyright 2009-2024).
  * Released under the Microsoft Public License.
  * See fna.LICENSE for details.

  * Derived from code by the Mono.Xna Team (Copyright 2006).
  * Released under the MIT License.
  * See monoxna.LICENSE for details.
  */

#include "WaveFileData.h"
#include "../utils/Utils.h"
#include "../utils/Exception.h"

#define LENGTH_OF_SIG 4

void ReadFourChar(BufferReader* br, char* sig)
{
	sig[0] = 'X';
	sig[1] = 'X';
	sig[2] = 'X';
	sig[3] = 'X';

	for (int i = 0; i < LENGTH_OF_SIG; i += 1)
	{
		uint8_t c = BufferReader_ReadU8(br);
		sig[i] = c;
	}
}

WaveFileData* WaveFileData_FromStream(BufferReader* br)
{
	// RIFF Signature
	char tempSig[LENGTH_OF_SIG + 1] = "XXXX";
	ReadFourChar(br, tempSig);

	char signature[LENGTH_OF_SIG];
	Utils_memcpy(signature, tempSig, LENGTH_OF_SIG);
	if (Utils_StringEqualTo(signature, "RIFF"))
	{
		Exception_Run("Specified stream is not a wave file.", false);
		return NULL;
	}
	
	BufferReader_ReadU32(br); // Riff Chunk Size

	ReadFourChar(br, tempSig);
	char wformat[LENGTH_OF_SIG];
	Utils_memcpy(wformat, tempSig, LENGTH_OF_SIG);
	if (Utils_StringEqualTo(wformat, "WAVE"))
	{
		Exception_Run("Specified stream is not a wave file.", false);
		return NULL;
	}

	// WAVE Header
	ReadFourChar(br, tempSig);
	char format_signature[LENGTH_OF_SIG];
	Utils_memcpy(format_signature, tempSig, LENGTH_OF_SIG);
	while (Utils_StringEqualTo(format_signature, "fmt "))
	{
		int32_t bytesToRead = BufferReader_ReadI32(br);
		BufferReader_ReadBytes(br, bytesToRead);
		ReadFourChar(br, tempSig);
		Utils_memcpy(format_signature, tempSig, LENGTH_OF_SIG);
	}

	int format_chunk_size = BufferReader_ReadI32(br);

	WaveFileData* waveData = Utils_malloc(sizeof(WaveFileData));
	Utils_memset(waveData, 0, sizeof(WaveFileData));
	waveData->wFormatTag = BufferReader_ReadU16(br);
	waveData->nChannels = BufferReader_ReadU16(br);
	waveData->nSamplesPerSec = BufferReader_ReadU32(br);
	waveData->nAvgBytesPerSec = BufferReader_ReadU32(br);
	waveData->nBlockAlign = BufferReader_ReadU16(br);
	waveData->wBitsPerSample = BufferReader_ReadU16(br);

	// Reads residual bytes
	if (format_chunk_size > 16)
	{
		BufferReader_ReadBytes(br, format_chunk_size - 16);
	}

	// data Signature
	ReadFourChar(br, tempSig);
	char data_signature[LENGTH_OF_SIG];
	Utils_memcpy(data_signature, tempSig, LENGTH_OF_SIG);
	while (Utils_StringEqualTo(data_signature, "data")) //ToLowerInvariant... normally
	{
		int32_t bytesToRead = BufferReader_ReadI32(br);
		ReadFourChar(br, tempSig);
		Utils_memcpy(data_signature, tempSig, LENGTH_OF_SIG);
	}
	if (Utils_StringEqualTo(data_signature, "data"))
	{
		Exception_Run("Specified wave file is not supported.", false);
		return NULL;
	}

	waveData->mWaveDataLength = BufferReader_ReadI32(br);
	waveData->mWaveData = BufferReader_ReadBytes(br, waveData->mWaveDataLength);

	// Scan for other chunks
	while (BufferReader_HasNext(br))
	{
		//char chunkIDChars[4];
		ReadFourChar(br, tempSig);

		char chunk_signature[LENGTH_OF_SIG];
		Utils_memcpy(chunk_signature, tempSig, LENGTH_OF_SIG);
		int32_t chunkDataSize = BufferReader_ReadI32(br);
		if (Utils_StringEqualTo(chunk_signature, "smpl")) // "smpl", Sampler Chunk Found
		{
			BufferReader_ReadU32(br); // Manufacturer
			BufferReader_ReadU32(br); // Product
			BufferReader_ReadU32(br); // Sample Period
			BufferReader_ReadU32(br); // MIDI Unity Note
			BufferReader_ReadU32(br); // MIDI Pitch Fraction
			BufferReader_ReadU32(br); // SMPTE Format
			BufferReader_ReadU32(br); // SMPTE Offset
			uint32_t numSampleLoops = BufferReader_ReadU32(br);
			int samplerData = BufferReader_ReadI32(br);

			for (int i = 0; i < numSampleLoops; i += 1)
			{
				BufferReader_ReadU32(br); // Cue Point ID
				BufferReader_ReadU32(br); // Type
				int start = BufferReader_ReadI32(br);
				int end = BufferReader_ReadI32(br);
				BufferReader_ReadU32(br); // Fraction
				BufferReader_ReadU32(br); // Play Count

				if (i == 0) // Grab loopStart and loopEnd from first sample loop
				{
					waveData->samplerLoopStart = start;
					waveData->samplerLoopEnd = end;
				}
			}

			if (samplerData != 0) // Read Sampler Data if it exists
			{
				BufferReader_ReadBytes(br, samplerData);
			}
		}
		else // Read unwanted chunk data and try again
		{
			BufferReader_ReadBytes(br, chunkDataSize);
		}
	}
	// End scan

	return waveData;
}
