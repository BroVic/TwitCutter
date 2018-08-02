// post.cpp

#include "post.h"

// Class TwitterCred
// Default constructor initialises keys with those of the official Twitcutter app
TwitterCred::TwitterCred()
    : consumerKey("ToEA7d1G4lsDgu5XO9lkI6E2R"),
      consumerKeySecret("JLdCvUnOPg3IhokpM7wjFbM2chFhyIMnGqY8UZ99aRu79Kgu7l"),
      myOAuthAccessTokenKey("21248597-nmGJFxqd6S5hmCY1jDCgYBe1x3vm9ISNJ3Y4OSpAc"),
      myOAuthAccessTokenSecret("GKmECYdC7EO37pzvdwaD3U35z6I9YFP4HUQWmMYHoQzLK")
{
}


TwitterCred::TwitterCred(const std::string& ck,
                         const std::string& cs,
                         const std::string& at,
                         const std::string& as)
    : consumerKey(ck),
      consumerKeySecret(cs),
      myOAuthAccessTokenKey(at),
      myOAuthAccessTokenSecret(as)
{
}

TwitterCred::~TwitterCred()
{
}


const std::string& TwitterCred::get_consumerKey() const
{
    return consumerKey;
}

const std::string& TwitterCred::get_consumerKeySecret() const
{
    return consumerKeySecret;
}

const std::string& TwitterCred::get_myOAuthAccessTokenKey() const
{
    return myOAuthAccessTokenKey;
}

const std::string& TwitterCred::get_myOAuthAccessTokenSecret() const
{
    return myOAuthAccessTokenSecret;
}

// Class Updater
Updater::Updater()
    : keyring(),
      twitterObj(),
      replyMsg()
{
}

// Sets API keys 
void Updater::set_keys()
{
    twitterObj.getOAuth().setConsumerKey(keyring.get_consumerKey());
	twitterObj.getOAuth().setConsumerSecret(keyring.get_consumerKeySecret());
	twitterObj.getOAuth().setOAuthTokenKey(keyring.get_myOAuthAccessTokenKey());
	twitterObj.getOAuth().setOAuthTokenSecret(keyring.get_myOAuthAccessTokenSecret());
}

void Updater::post_status(const std::string& tweetStr)
{
    // TODO: Input validation and error checking
    if (twitterObj.statusUpdate(tweetStr))
	{
		twitterObj.getLastWebResponse(replyMsg);
		printf("\ntwitterClient:: twitCurl::statusUpdate web response: \n%s\n", replyMsg.c_str());
	}
	else
	{
		twitterObj.getLastCurlError(replyMsg);
		printf("\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", replyMsg.c_str());
	}
}