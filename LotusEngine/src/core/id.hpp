#ifndef LOTUS_ID_HPP_INCLUDED
#define LOTUS_ID_HPP_INCLUDED

namespace lotus {

	template <unsigned int N0, unsigned int N1>
	struct ID
	{
		unsigned int index : N0;
		unsigned int generation : N1;
	};

	template <unsigned int N0, unsigned int N1>
	unsigned int idToUnsignedInt(const ID<N0, N1> &h)
	{
		return h.index | h.generation << N0;
	}

	template <unsigned int N0, unsigned int N1>
	bool operator==(const ID<N0, N1> &h0, const ID<N0, N1> &h1)
	{
		return idToUnsignedInt(h0) == idToUnsignedInt(h1);
	}

	template <unsigned int N0, unsigned int N1>
	bool operator!=(const ID<N0, N1> &h0, const ID<N0, N1> &h1)
	{
		return !(h0 == h1);
	}

	template <unsigned int N0, unsigned int N1>
	bool operator<(const ID<N0, N1> &h0, const ID<N0, N1> &h1)
	{
		return idToUnsignedInt(h0) < idToUnsignedInt(h1);
	}

	template <unsigned int N0, unsigned int N1>
	bool operator>(const ID<N0, N1> &h0, const ID<N0, N1> &h1)
	{
		return idToUnsignedInt(h0) > idToUnsignedInt(h1);
	}

	template <unsigned int N0, unsigned int N1>
	bool operator<=(const ID<N0, N1> &h0, const ID<N0, N1> &h1)
	{
		return idToUnsignedInt(h0) <= idToUnsignedInt(h1);
	}

	template <unsigned int N0, unsigned int N1>
	bool operator>=(const ID<N0, N1> &h0, const ID<N0, N1> &h1)
	{
		return idToUnsignedInt(h0) >= idToUnsignedInt(h1);
	}

}

#endif