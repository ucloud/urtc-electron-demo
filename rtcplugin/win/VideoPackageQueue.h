#pragma once

#include "BufferQueue.h"

class CVideoPackageQueue
{
protected:
	CVideoPackageQueue();
	~CVideoPackageQueue();

public:
	static CVideoPackageQueue *GetInstance();
	static void CloseInstance();

	void SetVideoFrameLen(const int &len);

	bool PushVideoPackage(uint8_t* lpAudioPackage, uint32_t nPackageLen);
	bool PopVideoPackage(uint8_t* lpVideoPackage, uint32_t *nPackageSize);

	uint32_t GetVideoPackageSize() const { return m_nPackageSize; };
	uint32_t GetBufferSize() const { return m_nBufferSize; };

private:
	CBufferQueue		    m_bufQueue;
	uint32_t				m_nPackageSize;
	uint32_t				m_nBufferSize;

	static CVideoPackageQueue	*m_lpVideoPackageQueue;
};


