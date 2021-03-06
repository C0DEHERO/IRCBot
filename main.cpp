#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <getopt.h>
#include "MyBot.h"

using namespace std;

void help(const string&);

int main(int argc, char* argv[])
{
	if(argc < 2) {
	    cout << "Missing arguments!" << endl;
		help(argv[0]);
		return 1;
	}
	
	string server, channel_string, nick, port_string, owner, trigger;
	int port;
	
	int c;
	
	while ((c = getopt (argc, argv, "s:p:c:n:o:t:")) != -1) {
	    switch(c) {
	    case 's':
		server = optarg;
		break;
	    case 'p':
		port_string = optarg;
		break;
	    case 'c':
		channel_string = optarg;
		break;
	    case 'n':
		nick = optarg;
		break;
	    case 'o':
		owner = optarg;
		break;
            case 't':
                trigger = optarg;
                break;
	    }
	}

	bool missing = false;
	
	if(server.empty()) {
	    cout << "Missing server argument (-s)" << endl;
	    missing = true;
	}
	if(channel_string.empty()) {
	    cout << "Missing channel argument (-c)" << endl;
	    missing = true;
	}
	if(nick.empty()) {
	    cout << "Missing nick argument (-n)" << endl;
	    missing = true;
	}
	if(owner.empty()) {
	    cout << "Missing owner argument (-o)" << endl;
	    missing = true;
	}
	if(trigger.empty()) {
	    cout << "Missing trigger argument (-t)" << endl;
	}
	if(missing) {
	    help(argv[0]);
	    return 1;
	}

	if(port_string.empty())
	    port_string = "6667";
	port = stoi(port_string);

	cout << "----------information----------" << endl;
	cout << "server=" + server <<endl;
	cout << "port=" + port_string << endl;
	cout << "channel=" + channel_string << endl;
	cout << "nick=" + nick << endl;
	cout << "owner=" + owner << endl;
	cout << "trigger=" + trigger << endl;
	cout << "-------------------------------" << endl;
	
	list<string> channels;
	stringstream ss(channel_string);

	string channel;

	while(ss >> channel) {
	    channels.push_back(channel);

	    if (ss.peek() == ',')
		ss.ignore();
	}

	MyBot bot = MyBot(server, port, channels, nick, "test", owner, trigger);
	bot.registerFunctions();
	bot.start();

	return 0;

}

void help(const string &program_name) {
cout << "Use like this:" << endl;
cout << string(program_name) + " -s irc.myserver.org [-p 6667] -c #mychannel -n botname" << endl;
cout << endl;
cout << "-s\tserver address" << endl;
cout << "-p\tport (standard: 6667)" << endl;
cout << "-c\tchannel/s (example -c #mychannel or -c #mychannel,#yourchannel -o you)" << endl;
cout << "-n\tname" << endl;
cout << "-o\towner" << endl;
cout << "-i\ttrigger (example -t ! for !help)" << endl;
cout << endl;
cout << "arguments can be given in any order" << endl;
}
