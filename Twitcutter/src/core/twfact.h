// twfact.h

#ifndef _TWFACT_H_INCLUDED_
#define _TWFACT_H_INCLUDED_

#include <string>
#include <vector>
#include "coredll.h"
#include "constants.h"

class TWITCUTAPI TwtProcessor
{
BEGIN_WARNINGS_ACTION
DISABLE_WARNING_4251
	std::string              fullText;
	std::string              piece;
	std::string::iterator    it;
protected:
	std::vector<std::string> chain;
END_WARNINGS_ACTION
private:
	unsigned char            maxChainLen;
	unsigned char            twtNumb;
	unsigned char		     denom;

	void estimTwtNum();
	void spliceStr();
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

