#include "keys.h"


Keyring::Keyring() 
	:myConsumerKey{ "ToEA7d1G4lsDgu5XO9lkI6E2R" },
	myConsumerKeySecret{ "JLdCvUnOPg3IhokpM7wjFbM2chFhyIMnGqY8UZ99aRu79Kgu7l" },
	myOAuthAccessTokenKey{ "21248597-nmGJFxqd6S5hmCY1jDCgYBe1x3vm9ISNJ3Y4OSpAc" },
	myOAuthAccessTokenSecret{ "GKmECYdC7EO37pzvdwaD3U35z6I9YFP4HUQWmMYHoQzLK" }
{
}

Keyring::~Keyring()
{
}

const std::string& Keyring::getMyConsumerKey() const
{
	return myConsumerKey;
}

const std::string& Keyring::getMyConsumerKeySecret() const
{
	return myConsumerKeySecret;
}

const std::string& Keyring::getMyOAuthAccessTokenKey() const
{
	return myOAuthAccessTokenKey;
}

const std::string& Keyring::getMyOAuthAccessTokenSecret() const
{
	return myOAuthAccessTokenSecret;
}

void Keyring::setConsumerKey(const std::string& ck)
{
	myConsumerKey = ck;
}

void Keyring::setConsumerKeySecret(const std::string & cs)
{
	myConsumerKeySecret = cs;
}

void Keyring::setMyOAuthAccessTokenKey(const std::string& at)
{
	myOAuthAccessTokenKey = at;
}

void Keyring::setMyOAuthAccessTokenSecret(const std::string& as)
{
	myOAuthAccessTokenSecret = as;
}
