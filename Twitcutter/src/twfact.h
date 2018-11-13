// twfact.h

#ifndef _TWFACT_H_INCLUDED_
#define _TWFACT_H_INCLUDED_

#include <string>
#include <vector>
#include "twclient.h"
#include "constants.h"

class TwtProcessor
{
	std::string              fullText;
	std::string              piece;
	std::string::iterator    it;
	unsigned char            maxChainLen;
	unsigned char            twtNumb;
	unsigned char		     denom;

	void estimTwtNum();
	void spliceStr();

protected:
	std::vector<std::string> chain;
public:
	TwtProcessor();
	~TwtProcessor();
	void mkChain();

	inline void set_fulltxt(std::string& s_in)
	{
		fullText.assign(s_in);
	}

	inline unsigned char get_denom() const
	{
		return denom;
	}

	inline unsigned char get_twtNumb() const
	{
		return twtNumb;
	}

	inline bool chainIsEmpty() const
	{
		return chain.empty();
	}

	inline std::vector<std::string> get_chain() const
	{
		return chain;
	}

	inline unsigned short get_maxChainLen() const
	{
		return maxChainLen;
	}

	int reset_maxChainLen(char);
};
#endif // !_TWFACT_H_INCLUDED_

