// post.h

// Class(es) for Implementing Twitter REST API Access

#ifndef _POST_H_INCLUDED_
#define _POST_H_INCLUDED_

#include<string>
#include<sstream>
#include<algorithm>
#include "genproc.h"        // TwtProcessor class
#include "keys.h"           // default app credentials
#include "include/twitcurl.h"       // 
#include "include/oauthlib.h"       //

class TwitterClient
{
	Keyring _keys;
	twitCurl _twitterObj;
	TwtProcessor twts;     // TODO: This is not intuitive, so change it!
	std::string _srvResponse;
	// char tmpBuf[1024];

public:
	TwitterClient();
	~TwitterClient();

	void setup_twitter_oauth();
	void post_status();
};
#endif // !_POST_H_INCLUDED_
