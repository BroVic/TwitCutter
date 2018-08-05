// post.cpp

#include "post.h"

// Class TwitterCred
// Default constructor initialises keys with those of the official Twitcutter app
TwitterCred::TwitterCred()
    : _consumerKey("ToEA7d1G4lsDgu5XO9lkI6E2R"),
      _consumerKeySecret("JLdCvUnOPg3IhokpM7wjFbM2chFhyIMnGqY8UZ99aRu79Kgu7l"),
      _myOAuthAccessTokenKey("21248597-nmGJFxqd6S5hmCY1jDCgYBe1x3vm9ISNJ3Y4OSpAc"),
      _myOAuthAccessTokenSecret("GKmECYdC7EO37pzvdwaD3U35z6I9YFP4HUQWmMYHoQzLK")
{
}

TwitterCred::TwitterCred(const std::string& ck,
                         const std::string& cs,
                         const std::string& at,
                         const std::string& as)
    : _consumerKey(ck),
      _consumerKeySecret(cs),
      _myOAuthAccessTokenKey(at),
      _myOAuthAccessTokenSecret(as)
{
}

TwitterCred::~TwitterCred()
{
}


const std::string& TwitterCred::get_consumerKey() const
{
    return _consumerKey;
}

const std::string& TwitterCred::get_consumerKeySecret() const
{
    return _consumerKeySecret;
}

const std::string& TwitterCred::get_myOAuthAccessTokenKey() const
{
    return _myOAuthAccessTokenKey;
}

const std::string& TwitterCred::get_myOAuthAccessTokenSecret() const
{
    return _myOAuthAccessTokenSecret;
}

// Class Updater
Updater::Updater()
    : _keyring(),
      _twitterObj(),
      _replyMsg()
{
}

// Sets API keys 
void Updater::set_keys()
{
    _twitterObj.getOAuth().setConsumerKey(_keyring.get_consumerKey());
	_twitterObj.getOAuth().setConsumerSecret(_keyring.get_consumerKeySecret());
	_twitterObj.getOAuth().setOAuthTokenKey(_keyring.get_myOAuthAccessTokenKey());
	_twitterObj.getOAuth().setOAuthTokenSecret(_keyring.get_myOAuthAccessTokenSecret());
}

void Updater::post_status(const TwtProcessor& tweets)
{
    // TODO: Input validation and error checking
    for (auto& tweetStr :tweets.chain)
    {
        if (_twitterObj.statusUpdate(tweetStr))
        {
            _twitterObj.getLastWebResponse(_replyMsg);
            printf("\ntwitterClient:: twitCurl::statusUpdate web response: \n%s\n", _replyMsg.c_str());
        }
        else
        {
            _twitterObj.getLastCurlError(_replyMsg);
            printf("\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", _replyMsg.c_str());
        }
    }
}
