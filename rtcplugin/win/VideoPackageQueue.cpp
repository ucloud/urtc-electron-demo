#include "VideoPackageQueue.h"


CVideoPackageQueue	*CVideoPackageQueue::m_lpVideoPackageQueue = NULL;

CVideoPackageQueue::CVideoPackageQueue()
{
	m_nPackageSize = 0;
	m_nBufferSize = 0x800000;
	m_bufQueue.Create(3, 0x800000);
}


CVideoPackageQueue::~CVideoPackageQueue()
{
	m_bufQueue.FreeAllBusyBlock();
	m_bufQueue.Close();
}

CVideoPackageQueue *CVideoPackageQueue::GetInstance()
{
	if (m_lpVideoPackageQueue == NULL)
		m_lpVideoPackageQueue = new CVideoPackageQueue();

	return m_lpVideoPackageQueue;
}

void CVideoPackageQueue::CloseInstance()
{
	if (m_lpVideoPackageQueue == NULL)
		return;

	delete m_lpVideoPackageQueue;
	m_lpVideoPackageQueue = NULL;
}

void CVideoPackageQueue::SetVideoFrameLen(const int &len)
{
	m_nPackageSize = len;
}

bool CVideoPackageQueue::PushVideoPackage(uint8_t* lpVideoPackage, uint32_t nPackageLen)
{
	if (m_bufQueue.GetFreeCount() == 0)
		m_bufQueue.FreeBusyHead(NULL, 0);

	void* lpBuffer = m_bufQueue.AllocBuffer(false);
	if (lpBuffer == NULL) 
		return false;
	memcpy_s(lpBuffer, m_bufQueue.GetBytesPreUnit(), lpVideoPackage, nPackageLen);

	return true;
}

bool CVideoPackageQueue::PopVideoPackage(uint8_t* lpVideoPackage, uint32_t *nPackageSize)
{
	if (nPackageSize == 0)
		return false;

	if (m_bufQueue.GetBusyCount() == 0)
		return false;

	if (*nPackageSize < m_nPackageSize) {
		*nPackageSize = m_nPackageSize;
		return false;
	}

	*nPackageSize = m_nPackageSize;
	m_bufQueue.FreeBusyHead(lpVideoPackage, m_nPackageSize);

	return true;
}