#ifndef DATA_TABLE_HPP
#define DATA_TABLE_HPP

#include <string>

enum FLAGS {
    UP,
    DOWN,
    LOOPBACK,
    RUNNING,
    BROADCAST,
    MULTICAST,
    IPV4,
    IPV6
};

struct RoutingTable {
    std::string destiantion;
    std::string gateway;
    std::string genmask;
    std::string flags;
    std::string metric;
    std::string ref;
    std::string use;
    std::string Iface;
};

struct PingTable {
    std::string name;
    std::string result;
};

struct IfaceTable {
    std::string iface_name;
    std::string infomations;
};


#endif // DATA_TABLE_HPP
