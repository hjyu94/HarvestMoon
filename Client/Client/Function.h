#pragma once 


class CMyStrCmp
{
public:
	CMyStrCmp() {}
	CMyStrCmp(const TCHAR* pString)
		:m_pString(pString)
	{}
public:
	template<class T>
	bool operator()(T& rPair)
	{
		return !lstrcmp(rPair.first, m_pString);
	}
private:
	const TCHAR* m_pString;
};