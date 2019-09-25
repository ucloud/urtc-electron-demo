#pragma once

#include <stdint.h>
#include <list>
#include <cstddef>
#include <mutex>

class CBufferQueue
{
public:
	CBufferQueue();
	~CBufferQueue();

	bool Create(int nUnitCount, uint32_t nBytesPreUnit);
	bool Close();

	uint32_t	GetBytesPreUnit() const { return m_nBytesPreUnit; };
	int		GetUnitCount() const { return m_nUnitCount; };
	int		GetCurrentCount() const { return m_nCurrentCount; };

	int		GetFreeCount() const;
	int		GetBusyCount() const;

	void*	AllocBuffer(bool bForceAlloc = false);

	bool	FreeBusyHead(void* lpDestBuf, uint32_t nBytesToCpoy);
	void	FreeAllBusyBlock();

private:
	int			m_nUnitCount;		// 单元初始值
	int			m_nCurrentCount;	// 当前块数目
	uint32_t		m_nBytesPreUnit;

	std::list<uint8_t*>	m_listFreeUnit;	// 闲置单元
	std::list<uint8_t*>	m_listBusyUnit;	// 非闲置单元

	std::mutex   m_csListLock;	// 忙表锁
};

