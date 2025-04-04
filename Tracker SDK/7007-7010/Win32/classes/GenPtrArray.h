//////////////////////////////////////////////////////////////////////////////
// CGenPtrArray class
//

/*******************************************************************************
 * Copyright (c) 2003 Electro-Optical Imaging, Inc. All Rights Reserved
 *
 * Electro-Optical Imaging, Inc. (E-O Imaging) licenses this software under 
 * specific terms and conditions.  Use of any of the software or derivatives
 * thereof in any product without a Electro-Optical Imaging, Inc. tracker is 
 * strictly prohibited.
 *
 * Electro-Optical Imaging, Inc. provides this software AS IS, WITHOUT ANY 
 * WARRANTY, EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  E-O Imaging makes
 * no guarantee or representations regarding the use of, or the results of the
 * use of, the software and documentation in terms of correctness, accuracy,
 * reliability, currentness, or otherwise; and you rely on the software,
 * documentation and results solely at your own risk.
 *
 * IN NO EVENT SHALL E-O IMAGING BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
 * LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
 * OF ANY KIND.  IN NO EVENT SHALL E-O IMAGING'S TOTAL LIABILITY EXCEED THE SUM
 * PAID TO E-O IMAGING FOR THE PRODUCT LICENSED HEREUNDER.
 *
 ******************************************************************************/

#ifndef __CGenPtrArray__
#define __CGenPtrArray__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template<class TYPE>
class CGenPtrArray
{
// Data
protected:
	TYPE** m_pData;		// the actual array of data
	int m_nSize;		// # of elements (upperBound - 1)
	int m_nMaxSize;		// max allocated
	int m_nGrowBy;		// grow amount

public:
// Construction / Destruction
	CGenPtrArray(int nGrowBy = 0);
	CGenPtrArray(const CGenPtrArray<TYPE>& src);
	virtual ~CGenPtrArray();

// Attributes
	virtual int GetSize() const { return m_nSize; }
	virtual int GetUpperBound() const { return m_nSize-1; }
	virtual int	GetGrowBy() const { return m_nGrowBy; }
	virtual void SetSize(int nNewSize, int nGrowBy = -1);
	virtual void SetGrowBy(int nGrowBy) { m_nGrowBy = nGrowBy; }
	virtual BOOL IsEmpty() const { return (m_nSize <= 0); }

// Operations
	// Clean up
	virtual void FreeExtra();
	virtual void RemoveAll();

	// Accessing elements
	virtual TYPE* GetAt(int nIndex) const;
	virtual void SetAt(int nIndex, TYPE* newElement);
	virtual TYPE*& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	virtual const TYPE** GetData() const { return (const TYPE**)m_pData; }
	virtual TYPE** GetData() { return (TYPE**)m_pData; }

	// Potentially growing the array
	virtual void SetAtGrow(int nIndex, TYPE* newElement);
	virtual int Add(TYPE* newElement);
	virtual int Append(const CGenPtrArray<TYPE>& src);
	virtual void Copy(const CGenPtrArray<TYPE>& src);

	// overloaded operator helpers
	virtual TYPE* operator[](int nIndex) const;
	virtual TYPE*& operator[](int nIndex);
	virtual const CGenPtrArray<TYPE>& operator=(const CGenPtrArray<TYPE>& src);

	// Operations that move elements around
	virtual void InsertAt(int nIndex, TYPE* newElement, int nCount = 1);
	virtual void RemoveAt(int nIndex, int nCount = 1);
	virtual void InsertAt(int nStartIndex, CGenPtrArray<TYPE>* pNewArray);
	virtual void Swap(int FirstIndex, int SecondIndex);
	virtual void Move(int ToIndex, int FromIndex);
};


template<class TYPE>
inline void CGenPtrArray<TYPE>::RemoveAll()
{
	if( m_pData == NULL )
		return;

	// shrink to nothing
	delete[] (BYTE*)m_pData;
	m_pData = NULL;
	m_nSize = m_nMaxSize = 0;
}

template<class TYPE>
inline TYPE* CGenPtrArray<TYPE>::GetAt(int nIndex) const
{
	ASSERT( (nIndex >= 0) && (nIndex < m_nSize) );

	if( (nIndex < 0) || (nIndex >= m_nSize) )
		return NULL;

	return m_pData[nIndex];
}

template<class TYPE>
inline void CGenPtrArray<TYPE>::SetAt(int nIndex, TYPE* newElement)
{
	ASSERT( (nIndex >= 0) && (nIndex < m_nSize) );

	if( (nIndex < 0) || (nIndex >= m_nSize) )
		return;

	m_pData[nIndex] = newElement;
}

template<class TYPE>
inline TYPE*& CGenPtrArray<TYPE>::ElementAt(int nIndex)
{
	ASSERT( (nIndex >= 0) && (nIndex < m_nSize) );

	return m_pData[nIndex];
}

template<class TYPE>
inline TYPE* CGenPtrArray<TYPE>::operator[](int nIndex) const
{ return GetAt(nIndex); }

template<class TYPE>
inline const CGenPtrArray<TYPE>& CGenPtrArray<TYPE>::operator=(const CGenPtrArray<TYPE>& src)
{ 
	Copy(src);
	return *this; 
}

template<class TYPE>
inline TYPE*& CGenPtrArray<TYPE>::operator[](int nIndex)
{ return ElementAt(nIndex); }

template<class TYPE>
inline int CGenPtrArray<TYPE>::Add(TYPE* newElement)
{
	int nIndex = m_nSize;
	SetAtGrow(nIndex, newElement);
	return nIndex;
}

//////////////////////////////////////////////////////////////////////////////
// Constructor / Destructor
//
template<class TYPE>
CGenPtrArray<TYPE>::CGenPtrArray(int nGrowBy)
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = 0;
	m_nGrowBy = nGrowBy;
}

template<class TYPE>
CGenPtrArray<TYPE>::CGenPtrArray(const CGenPtrArray<TYPE>& src)
{
	m_pData = NULL;
	m_nSize = src.m_nSize;
	m_nMaxSize = src.m_nMaxSize;
	m_nGrowBy = src.m_nGrowBy;

	Copy(src);
}

template<class TYPE>
CGenPtrArray<TYPE>::~CGenPtrArray()
{
	RemoveAll();
}

//////////////////////////////////////////////////////////////////////////////
// CGenPtrArray functions
//
template<class TYPE>
void CGenPtrArray<TYPE>::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if( nGrowBy >= 0 )
		m_nGrowBy = nGrowBy;  // set new grow size

	if( nNewSize == 0 )
	{
		RemoveAll();
	}
	else if( m_pData == NULL )
	{
		// set max to grow value
		m_nMaxSize = m_nGrowBy;
		if( nNewSize > m_nMaxSize )
			m_nMaxSize = nNewSize;

		// create pointer array
		m_pData = (TYPE**) new BYTE[m_nMaxSize * sizeof(TYPE*)];
		ASSERT(m_pData);

		memset(m_pData, 0, m_nMaxSize * sizeof(TYPE*));  // zero fill

		m_nSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements
			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(TYPE*));
		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array

		// heuristically determine growth
		// (this avoids heap fragmentation in many situations)
		int nGrowBy = min(1024, max(4, m_nSize / 8));

		// use the maximum of heuristic and user set growth
		if( m_nGrowBy > nGrowBy )
			nGrowBy = m_nGrowBy;

		int nNewMax = m_nMaxSize + nGrowBy;
		if( nNewMax < nNewSize )
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

		TYPE** pNewData = (TYPE**) new BYTE[nNewMax * sizeof(TYPE*)];
		ASSERT(pNewData);

		// copy new data from old
		memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE*));

		// zero remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(TYPE*));

		// get rid of old stuff
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

template<class TYPE>
int CGenPtrArray<TYPE>::Append(const CGenPtrArray<TYPE>& src)
{
	ASSERT(this != &src);   // cannot append to itself

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

	memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(TYPE*));

	return nOldSize;
}

template<class TYPE>
void CGenPtrArray<TYPE>::Copy(const CGenPtrArray<TYPE>& src)
{
	ASSERT(this != &src);   // cannot append to itself

	// are there are no elements in the source?
	if( src.m_nSize <= 0 )
	{
		RemoveAll();
		return;
	}

	// set this array to the size of the other, and copy
	// the data
	SetSize(src.m_nSize);
	memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(TYPE*));
}

template<class TYPE>
void CGenPtrArray<TYPE>::FreeExtra()
{
	if( m_nSize != m_nMaxSize )
	{
		// shrink to desired size
		TYPE** pNewData = NULL;
		if( m_nSize != 0 )
		{
			// allocate new pointer array
			pNewData = (TYPE**) new BYTE[m_nSize * sizeof(TYPE*)];
			ASSERT(pNewData);

			// copy pointers
			memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE*));
		}

		// get rid of old stuff
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template<class TYPE>
void CGenPtrArray<TYPE>::SetAtGrow(int nIndex, TYPE* newElement)
{
	ASSERT(nIndex >= 0);

	if( nIndex >= m_nSize )
	{
		SetSize(nIndex+1);
	}

	m_pData[nIndex] = newElement;
}

template<class TYPE>
void CGenPtrArray<TYPE>::InsertAt(int nIndex, TYPE* newElement, int nCount)
{
	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size

		// shift old data up to fill gap
		memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
				(nOldSize-nIndex) * sizeof(TYPE*));

		// re-init slots we copied from
		memset(&m_pData[nIndex], 0, nCount * sizeof(TYPE*));

	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);
	while( nCount-- > 0 )
	{
		m_pData[nIndex++] = newElement;
	}
}

template<class TYPE>
void CGenPtrArray<TYPE>::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	ASSERT(nIndex + nCount <= m_nSize);

	// do nothing?
	if( nCount <= 0 )
		return;

	// just remove a range
	int nMoveCount = m_nSize - (nIndex + nCount);

	if( nMoveCount > 0 )
	{
		memcpy(&m_pData[nIndex], &m_pData[nIndex + nCount],
				nMoveCount * sizeof(TYPE*));
	}

	m_nSize -= nCount;
}

template<class TYPE>
void CGenPtrArray<TYPE>::InsertAt(int nStartIndex, CGenPtrArray<TYPE>* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if( pNewArray->GetSize() > 0 )
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());

		for(int i = 0; i < pNewArray->GetSize(); i++)
		{
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
		}
	}
}

template<class TYPE>
inline void CGenPtrArray<TYPE>::Swap(int FirstIndex, int SecondIndex)
{
	ASSERT(FirstIndex >= 0 && FirstIndex < m_nSize);
	ASSERT(SecondIndex >= 0 && SecondIndex < m_nSize);
//	ASSERT(FirstIndex != SecondIndex);

	TYPE* pTemp = m_pData[FirstIndex];
	m_pData[FirstIndex] = m_pData[SecondIndex];
	m_pData[SecondIndex] = pTemp;
}

template<class TYPE>
inline void CGenPtrArray<TYPE>::Move(int ToIndex, int FromIndex)
{
	ASSERT(FromIndex >= 0 && FromIndex < m_nSize);
	ASSERT(ToIndex >= 0 && ToIndex < m_nSize);

	// already there?
	if( FromIndex == ToIndex )
		return;

	// save from pointer
	TYPE* pTemp = m_pData[FromIndex];
	ASSERT(pTemp);

	// move pointers
	if( FromIndex < ToIndex )
	{
		memmove(&m_pData[FromIndex], &m_pData[FromIndex+1], 
				(ToIndex-FromIndex) * sizeof(TYPE*));
	}
	else
	{
		memmove(&m_pData[ToIndex+1], &m_pData[ToIndex], 
				(FromIndex-ToIndex) * sizeof(TYPE*));
	}

	// set the new position
	m_pData[ToIndex] = pTemp;
}

#endif //__CGenPtrArray__
