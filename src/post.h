// post.h

// Class(es) for Implementing Twitter REST API Access

#ifndef _POST_H_INCLUDED_
#define _POST_H_INCLUDED_

#include<string>
#include<sstream>
#include<algorithm>
#include "twitcurl.h"
#include "oauthlib.h"

class TwitterCred
{
    const std::string consumerKey;
    const std::string consumerKeySecret;
    const std::string myOAuthAccessTokenKey;
    const std::string myOAuthAccessTokenSecret;

public:
    TwitterCred() = default;
    TwitterCred(const std::string&,
                const std::string&,
                const std::string&,
                const std::string&);
    ~TwitterCred()
    {
    }

    const std::string& get_consumerKey() const;
    const std::string& get_consumerKeySecret() const;
    const std::string& get_myOAuthAccessTokenKey() const;
    const std::string& get_myOAuthAccessTokenSecret() const;
};


class Updater
{
    TwitterCred keyring;
    twitCurl twitterObj;
    // char tmpBuf[1024];
    std::string replyMsg;

    Updater() = default;
    ~Updater()
    {
    }

    void set_keys();
    void post_status(const std::string&);
};

#endif // !_POST_H_INCLUDED_