// keys.h

// App OAuth credentials
#ifndef _KEYS_H_INCLUDED
#define _KEYS_H_INCLUDED

#include <string>
// Keyring class
class Keyring
{
	std::string myConsumerKey;
	std::string myConsumerKeySecret;
	std::string myOAuthAccessTokenKey;
	std::string myOAuthAccessTokenSecret;

public:
	Keyring();
	~Keyring();

	const std::string& getMyConsumerKey() const;
	const std::string& getMyConsumerKeySecret() const;
	const std::string& getMyOAuthAccessTokenKey() const;
	const std::string& getMyOAuthAccessTokenSecret() const;

	void setConsumerKey(const std::string&);
	void setConsumerKeySecret(const std::string&);
	void setMyOAuthAccessTokenKey(const std::string&);
	void setMyOAuthAccessTokenSecret(const std::string&);
};
#endif // !_KEYS_H_INCLUDED