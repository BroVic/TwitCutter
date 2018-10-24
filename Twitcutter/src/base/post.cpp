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
	twitterObj.getOAuth().setConsumerKey(keys.getMyConsumerKey());
	twitterObj.getOAuth().setConsumerSecret(keys.getMyConsumerKeySecret());
	twitterObj.getOAuth().setOAuthTokenKey(keys.getMyOAuthAccessTokenKey());
	twitterObj.getOAuth().setOAuthTokenSecret(keys.getMyOAuthAccessTokenSecret());
}

// Updates status
void TwitterClient::post_status(TwtProcessor& twts)
{
    // TODO: Input validation and error checking
    for (const auto& twit : twts.chain)
    {
        if (twitterObj.statusUpdate(twit))
        {
            twitterObj.getLastWebResponse(srvResponse);
            printf("\ntwitterClient:: statusUpdate web response: \n%s\n", srvResponse.c_str());
        }
        else
        {
            twitterObj.getLastCurlError(srvResponse);
            printf("\ntwitterClient:: statusUpdate error:\n%s\n", srvResponse.c_str());
        }
    }
}
