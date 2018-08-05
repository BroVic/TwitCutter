// post.h

// Class(es) for Implementing Twitter REST API Access

#ifndef _POST_H_INCLUDED_
#define _POST_H_INCLUDED_

#include<string>
#include<sstream>
#include<algorithm>
#include "twitcurl.h"
#include "oauthlib.h"
#include "genproc.h"        // To receive TwtProcessor class

class TwitterCred
{
    const std::string _consumerKey;
    const std::string _consumerKeySecret;
    const std::string _myOAuthAccessTokenKey;
    const std::string _myOAuthAccessTokenSecret;

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
    TwitterCred _keyring;
    twitCurl _twitterObj;
    TwtProcessor _tweets;
    // char tmpBuf[1024];
    std::string _replyMsg;

    Updater() = default;
    ~Updater()
    {
    }

    void set_keys();
    void post_status(const TwtProcessor&);
};
#endif // !_POST_H_INCLUDED_
