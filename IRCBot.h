#ifndef IRCBOT_H_
#define IRCBOT_H_
#include <string>
#include <list>
#include <unordered_map>
#include "socketwrapper.h"

class IrcBot
{
public:
	IrcBot(string domain_name, int port, list<string> channel, string nick, string usr);
	virtual ~IrcBot();

	bool quit;
	bool error;

	void start();
private:
	const string channelWhitelist = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_-#";

	Socket net_client;

	bool connected, joined;

	unordered_map<string,string> nicks;
	list<string> channels;
	string nick;
	string usr;

	string nick_command;
	string usr_command;
	string join_command;

	string awaiting_names;

	char * timeNow();

	string getNick(const string &buf);
	string getChannel(const string &buf);
	string getArgument(const string &buf, const string &command);
	list<string>getArguments(const string &buf, const string &command);
	void sendMessage(const string &msg, const string &channel);
	void msgHandle(const string &buf, const string &msgChannel, const string &msgNick);
	bool checkWhitelist(const string &buffer, const string &charstring);
};

#endif