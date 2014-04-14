#ifndef IRCBOT_H_
#define IRCBOT_H_
#include <string>
#include <list>
#include <set>
#include <unordered_map>
#include "socketwrapper.h"

class IrcBot
{
public:
	IrcBot(const string &host, const int &port, const list<string> &channel, const string &nick, const string &usr, const string &owner, const string &trigger);
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
	string my_owner;
	string trigger;
	set<string> admins;

	string nick_command;
	string usr_command;
	string join_command;

	string awaiting_names;
	string names_channel;

	char * timeNow();

	string getNick(const string &buf);
	string getChannel(const string &buf);
	string getArgument(const string &buf, const string &command);
	list<string>getArguments(const string &buf, const string &command);
	void sendData(const string &buf);
	void sendAction(const string &msg, const string &channel);
	void sendMessage(const string &msg, const string &channel);
	bool checkTrigger(const string &buf, const string &msgChannel, const string &command);
	void msgHandle(const string &buf, const string &msgChannel, const string &msgNick);
	bool checkWhitelist(const string &buffer, const string &charstring);

    void addAdmin(const string &name);
    void removeAdmin(const string &name);
	bool isAdmin(const string &msgNick);
};

#endif
