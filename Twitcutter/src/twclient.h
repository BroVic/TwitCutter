// twclient.h

// Class(es) for Implementing Twitter REST API Access

#ifndef _TWCLIENT_H_INCLUDED_
#define _TWCLIENT_H_INCLUDED_

#include <string>
#include <twitcurl.h>       // header from twitcurl library
#include <oauthlib.h>       // ditto
#include "twfact.h"         // for 'TwtProcessor' class
#include "keys.h"           // for login credentials
#include "constants.h"

// TwitterClient class
class TwitterClient
{
	Keyring keys;
	twitCurl twitterObj;
	std::string srvResponse;
	std::vector<std::string> chainIn;
	std::vector<std::string> chainMonitor;

	void setup_twitter_oauth();
	void update_status(std::string&);
	inline std::vector<std::string> shrink_chain()
	{
		// chainMonitor.insert();
	}
public:
	void post_all_tweets();
	bool transferred_tweets(const std::vector<std::string>&);
	bool operator==(const std::vector<std::string>&);
	bool operator!=(const std::vector<std::string>&);
};
#endif // !_TWCLIENT_H_INCLUDED_
