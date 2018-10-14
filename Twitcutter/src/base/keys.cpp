#include "keys.h"


Keyring::Keyring() 
	:_myConsumerKey{ "ToEA7d1G4lsDgu5XO9lkI6E2R" },
	_myConsumerKeySecret{ "JLdCvUnOPg3IhokpM7wjFbM2chFhyIMnGqY8UZ99aRu79Kgu7l" },
	_myOAuthAccessTokenKey{ "21248597-nmGJFxqd6S5hmCY1jDCgYBe1x3vm9ISNJ3Y4OSpAc" },
	_myOAuthAccessTokenSecret{ "GKmECYdC7EO37pzvdwaD3U35z6I9YFP4HUQWmMYHoQzLK" }
{
}

Keyring::~Keyring()
{
}

const std::string& Keyring::getMyConsumerKey() const
{
	return _myConsumerKey;
}

const std::string& Keyring::getMyConsumerKeySecret() const
{
	return _myConsumerKeySecret;
}

const std::string& Keyring::getMyOAuthAccessTokenKey() const
{
	return _myOAuthAccessTokenKey;
}

const std::string& Keyring::getMyOAuthAccessTokenSecret() const
{
	return _myOAuthAccessTokenSecret;
}

void Keyring::setConsumerKey(const std::string& ck)
{
	_myConsumerKey = ck;
}

void Keyring::setConsumerKeySecret(const std::string & cs)
{
	_myConsumerKeySecret = cs;
}

void Keyring::setMyOAuthAccessTokenKey(const std::string& at)
{
	_myOAuthAccessTokenKey = at;
}

void Keyring::setMyOAuthAccessTokenSecret(const std::string& as)
{
	_myOAuthAccessTokenSecret = as;
}
