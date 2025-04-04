//////////////////////////////////////////////////////////////////////////////
// CGenArray class
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

#ifndef __CGenArray__
#define __CGenArray__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GenPtrArray.h"

template<class TYPE, class PTRARRAY>
class CGenArray
{
// Implementation
protected:
	PTRARRAY	m_PointerArray;

protected:
	virtual void SetPtrArraySize(int nNewSize, int nGrowBy = -1);

public:
// Construction / Destruction
	CGenArray(int nGrowBy = 0);
	CGenArray(const CGenArray<TYPE, PTRARRAY>& Source);
	CGenArray(const PTRARRAY& Source);
	virtual ~CGenArray();

// Attributes
	virtual int GetSize() const { return m_PointerArray.GetSize(); }
	virtual int GetUpperBound() const { return m_PointerArray.GetUpperBound(); }
	virtual int	GetGrowBy() const { return m_PointerArray.GetGrowBy(); }
	virtual void SetGrowBy(int nGrowBy) { m_PointerArray.SetGrowBy(nGrowBy); }
	virtual BOOL IsEmpty() const { return m_PointerArray.IsEmpty(); }

// Operations
	// Clean up
	virtual void FreeExtra() { m_PointerArray.FreeExtra(); }
	virtual void RemoveAll();

	// Accessing elements
	virtual TYPE* GetAt(int nIndex) const { return m_PointerArray.GetAt(nIndex); }
	virtual void SetAt(int nIndex, TYPE& newElement);
	virtual TYPE& ElementAt(int nIndex) const { return *m_PointerArray.GetAt(nIndex); }

	// Direct Access to the element data (may return NULL)
	virtual const TYPE** GetData() const { return m_PointerArray.GetData(); }
	virtual TYPE** GetData() { return m_PointerArray.GetData(); }

	// access to the protected pointer array
	virtual operator const PTRARRAY&() const { return m_PointerArray; }
	virtual operator const PTRARRAY*() const { return &m_PointerArray; }

	virtual const PTRARRAY& GetPointerArray() const { return m_PointerArray; }

	// Potentially growing the array
	virtual void SetSize(int nNewSize, int nGrowBy = -1);
	virtual TYPE* SetAtGrow(int nIndex, TYPE& newElement);
	virtual TYPE* Add();
	virtual TYPE* Add(const TYPE& newElement);

	// overloaded operator helpers
	virtual const TYPE& operator[](int nIndex) const;
	virtual TYPE& operator[](int nIndex);

	virtual void Copy(const CGenArray<TYPE, PTRARRAY>& Source);
	virtual const CGenArray<TYPE, PTRARRAY>& operator=(const CGenArray<TYPE, PTRARRAY>& Source)
			{ Copy(Source); return *this; }

	virtual void Copy(const PTRARRAY& Source);
	virtual const CGenArray<TYPE, PTRARRAY>& operator=(const PTRARRAY& Source)
			{ Copy(Source); return *this; }

	// Operations that move elements around
	virtual void InsertAt(int nIndex, const TYPE& newElement, int nCount = 1);
	virtual void RemoveAt(int nIndex, int nCount = 1);
	virtual void Remove(TYPE*& pElement);
	virtual void Swap(int FirstIndex, int SecondIndex) { m_PointerArray.Swap(FirstIndex, SecondIndex); }
	virtual void Move(int ToIndex, int FromIndex) { m_PointerArray.Move(ToIndex, FromIndex); }
};

template<class TYPE, class PTRARRAY>
inline const TYPE& CGenArray<TYPE, PTRARRAY>::operator[](int nIndex) const
{
	return *m_PointerArray.GetAt(nIndex);
}

template<class TYPE, class PTRARRAY>
inline TYPE& CGenArray<TYPE, PTRARRAY>::operator[](int nIndex)
{
	return *m_PointerArray.GetAt(nIndex);
}

template<class TYPE, class PTRARRAY>
inline void CGenArray<TYPE, PTRARRAY>::SetAt(int nIndex, TYPE& newElement)
{ 
	*m_PointerArray.GetAt(nIndex) = newElement;
}

template<class TYPE, class PTRARRAY>
inline TYPE* CGenArray<TYPE, PTRARRAY>::Add(const TYPE& newElement)
{
	TYPE* pNewElement = new TYPE(newElement);
	ASSERT(pNewElement);

	m_PointerArray.Add(pNewElement);

	return pNewElement;
}

template<class TYPE, class PTRARRAY>
inline TYPE* CGenArray<TYPE, PTRARRAY>::Add()
{
	TYPE* pNewElement = new TYPE;
	ASSERT(pNewElement);

	m_PointerArray.Add(pNewElement);

	return pNewElement;
}

//////////////////////////////////////////////////////////////////////////////
// Constructor / Destructor
//
template<class TYPE, class PTRARRAY>
CGenArray<TYPE, PTRARRAY>::CGenArray(int nGrowBy)
	: m_PointerArray(nGrowBy)
{
}

template<class TYPE, class PTRARRAY>
CGenArray<TYPE, PTRARRAY>::CGenArray(const CGenArray<TYPE, PTRARRAY>& Source)
	: m_PointerArray(Source.GetGrowBy())
{
	Copy(Source);
}

template<class TYPE, class PTRARRAY>
CGenArray<TYPE, PTRARRAY>::CGenArray(const PTRARRAY& Source)
	: m_PointerArray(Source.GetGrowBy())
{
	Copy(Source);
}

template<class TYPE, class PTRARRAY>
CGenArray<TYPE, PTRARRAY>::~CGenArray()
{
	RemoveAll();
}

//////////////////////////////////////////////////////////////////////////////
// CGenArray functions
//
template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::RemoveAll()
{
	// sanity
	if( m_PointerArray.GetData() == NULL )
		return;

	// delete all the objects
	for( int i=0; i < m_PointerArray.GetSize(); i++ )
	{
		ASSERT(m_PointerArray.GetAt(i));
		delete m_PointerArray.GetAt(i);
	}

	// delete the memory for the pointer array
	m_PointerArray.RemoveAll();
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::Copy(const CGenArray<TYPE, PTRARRAY>& Source)
{
	// clear out this array
	RemoveAll();

	// set this array's size to the sources size
	int ssize = Source.GetSize();
	SetPtrArraySize(ssize);

	// copy the sources data members
	for( register int i=0; i < ssize; i++ )
	{
		const TYPE* pType = Source.GetAt(i);
		ASSERT(pType);

		TYPE* pCopy = new TYPE(*pType);
		ASSERT(pCopy);

		m_PointerArray.SetAt(i, pCopy);
		ASSERT(m_PointerArray.GetAt(i) != NULL);
	}
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::Copy(const PTRARRAY& Source)
{
	// clear out this array
	RemoveAll();

	// set this array's size to the sources size
	int ssize = Source.GetSize();
	SetPtrArraySize(ssize);

	// copy the sources data members
	for( register int i=0; i < ssize; i++ )
	{
		const TYPE* pType = Source.GetAt(i);
		ASSERT(pType);

		TYPE* pCopy = new TYPE(*pType);
		ASSERT(pCopy);

		m_PointerArray.SetAt(i, pCopy);
		ASSERT(m_PointerArray.GetAt(i) != NULL);
	}
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::SetPtrArraySize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	// new size less than the current size?
	if( nNewSize < m_PointerArray.GetSize() )
	{
		// delete the objects which will be cut off
		for( int i=nNewSize; i < m_PointerArray.GetSize(); i++ )
		{
			ASSERT(m_PointerArray.GetAt(i));
			delete m_PointerArray.GetAt(i);
		}
	}

	// call pointer array set size
	m_PointerArray.SetSize(nNewSize, nGrowBy);
}

template<class TYPE, class PTRARRAY>
TYPE* CGenArray<TYPE, PTRARRAY>::SetAtGrow(int nIndex, TYPE& newElement)
{
	ASSERT(nIndex >= 0);

	// grow array if necessary
	if( nIndex >= m_PointerArray.GetSize() )
	{
		int oldsize = m_PointerArray.GetSize();

		// set new pointer array size
		SetPtrArraySize(nIndex+1);

		// allocate an object for each new element
		for( int i=oldsize; i < m_PointerArray.GetSize(); i++ )
		{
			TYPE* pNewElement = new TYPE(newElement);
			ASSERT(pNewElement);

			m_PointerArray.SetAt(i, pNewElement);
			ASSERT(m_PointerArray.GetAt(i) != NULL);
		}
	}
	else // just set the object
		*m_PointerArray.GetAt(nIndex) = newElement;

	return m_PointerArray.GetAt(nIndex);
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	// already desired size?
	if( nNewSize == m_PointerArray.GetSize() )
		return;

	// grow array if necessary
	if( nNewSize > m_PointerArray.GetSize() )
	{
		int oldsize = m_PointerArray.GetSize();

		// set new pointer array size
		SetPtrArraySize(nNewSize, nGrowBy);

		// allocate an object for each new element
		for( int i=oldsize; i < m_PointerArray.GetSize(); i++ )
		{
			TYPE* pNewElement = new TYPE;
			ASSERT(pNewElement);

			m_PointerArray.SetAt(i, pNewElement);
			ASSERT(m_PointerArray.GetAt(i) != NULL);
		}
	}
	else // just set the pointer array (will delete extra objects)
		SetPtrArraySize(nNewSize, nGrowBy);
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::InsertAt(int nIndex, const TYPE& newElement, int nCount)
{
	// insert the pointer(s)
	m_PointerArray.InsertAt(nIndex, NULL, nCount);

	// allocate the element(s)
	while( nCount-- )
	{
		TYPE* pNewElement = new TYPE(newElement);
		ASSERT(pNewElement);

		m_PointerArray.SetAt(nIndex, pNewElement);
		ASSERT(m_PointerArray.GetAt(nIndex) != NULL);

		nIndex++;
	}
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	ASSERT(nIndex + nCount <= m_PointerArray.GetSize());

	// do nothing?
	if( nCount <= 0 )
		return;

	// delete the object(s)
	for( int i=nIndex; i < (nIndex + nCount); i++ )
		delete m_PointerArray.GetAt(i);

	// remove the pointer(s) 
	m_PointerArray.RemoveAt(nIndex, nCount);
}

template<class TYPE, class PTRARRAY>
void CGenArray<TYPE, PTRARRAY>::Remove(TYPE*& pElement)
{
	// look for the object in the array
	// (from the last element forward, since we usually delete
	//  the last element allocated in the array)
	for( int i=m_PointerArray.GetSize()-1; i >= 0; i-- )
	{
		TYPE* pTest = m_PointerArray.GetAt(i);

		// is this the object?
		if( pTest == pElement )
		{
			// remove it and set pointer to NULL
			RemoveAt(i);
			pElement = NULL;
			return;
		}
	}
}

#endif // __CGenArray__
