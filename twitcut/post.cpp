// post.cpp

#include "post.h"


TwitterClient::TwitterClient()
{
}

TwitterClient::~TwitterClient()
{
}

// Sets API keys 
void TwitterClient::setup_twitter_oauth()
{
	_twitterObj.getOAuth().setConsumerKey(_keys.getConsumerKey());
	_twitterObj.getOAuth().setConsumerSecret(_keys.getConsumerKeySecret());
	_twitterObj.getOAuth().setOAuthTokenKey(_keys.getMyOAuthAccessTokenKey());
	_twitterObj.getOAuth().setOAuthTokenSecret(_keys.getMyOAuthAccessTokenSecret());
}

// Updates status
void TwitterClient::post_status()
{
    // TODO: Input validation and error checking
    for (const auto& twit : twts.chain)
    {
        if (_twitterObj.statusUpdate(twit))
        {
            _twitterObj.getLastWebResponse(_srvResponse);
            printf("\ntwitterClient:: statusUpdate web response: \n%s\n", _srvResponse.c_str());
        }
        else
        {
            _twitterObj.getLastCurlError(_srvResponse);
            printf("\ntwitterClient:: statusUpdate error:\n%s\n", _srvResponse.c_str());
        }
    }
}
