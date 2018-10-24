// post.h

// Class(es) for Implementing Twitter REST API Access

#ifndef _POST_H_INCLUDED_
#define _POST_H_INCLUDED_

#include <string>
#include <sstream>
#include <algorithm>
#include <twitcurl.h>       // header from twitcurl library
#include <oauthlib.h>       // ditto
#include "genproc.h"        // for 'TwtProcessor' class
#include "keys.h"           // for login credentials

class TwitterClient
{
	Keyring keys;
	twitCurl twitterObj;
	std::string srvResponse;
	// char tmpBuf[1024];

public:
	TwitterClient();
	~TwitterClient();

	void setup_twitter_oauth();
	void post_status(TwtProcessor&);
};
#endif // !_POST_H_INCLUDED_
