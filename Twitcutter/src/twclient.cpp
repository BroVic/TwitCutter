// post.cpp

#include "twclient.h"

// Posts entire chain
void TwitterClient::post_all_tweets()
{
	// TODO: Input validation and error checking
	setup_twitter_oauth();
	for (auto& t : chainIn)
	{
		update_status(t);
	}
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
void TwitterClient::update_status(std::string& twt)
{
    if (twitterObj.statusUpdate(twt))
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

// Grabs a copy of the chain for the TwitterClient object.
// Returns a bool to indicate whether this was successfully done.
bool TwitterClient::transferred_tweets(const std::vector<std::string>& chn)
{
	chainIn = chn;
	if (chainIn.size() != chn.size())
	{
		// TODO: Handle error?
		return false;
	}
	return chainIn == chn;
}

bool TwitterClient::operator==(const std::vector<std::string>& yrVec)
{
	// TODO: Consider using iterator or ranged loops
	size_t len = yrVec.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (chainIn[i] == yrVec[i])
		{
			continue;
		}
		return false;
	}
	return true;
}

bool TwitterClient::operator!=(const std::vector<std::string>& yrVec)
{
	return !(chainIn == yrVec);
}
