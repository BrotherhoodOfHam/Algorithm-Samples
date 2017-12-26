/*
	Range class
	
	Wrapper around a pair of iterators
*/

#pragma once

namespace ag
{
	template<typename IteratorType>
	class Range
	{
	private:
		
		IteratorType m_begin;
		IteratorType m_end;
	
	public:
		
		using reference = typename IteratorType::reference;
		
		/*
			Construct a range from a pair of begin/end iterators
		*/
		Range(IteratorType begin, IteratorType end) :
			m_begin(begin),
			m_end(end)
		{}

		/*
			Copy constructor
		*/
		Range(const Range<IteratorType>& range) :
			m_begin(range.m_begin),
			m_end(range.m_end)
		{}
		
		/*
			Get iterators
		*/
		IteratorType begin() { return m_begin; }
		IteratorType end() { return m_end; }
		
		reference at(size_t idx)
		{
			return *(begin() + idx);
		}
		
		reference operator[](size_t idx)
		{
			return at(idx);
		}
	};
}
