#include <cstdlib>
#include <iostream>

#include <stdio.h>
#include <string>

#include "thirdlib/httplib.h"


std::string exec_cmd(std::string cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}


int main(int, char**) {
    std::cout << "Hello, world!\n";

    // auto x = system("ping cn.bing.com -c 10 > ping_result.log");
    // auto y = system("route -n > route_result.log");
    // auto z = system("ifconfig -a > ifconfig_result.log");

    httplib::Server server;
    
    server.Get("/ping", [](const httplib::Request &, httplib::Response &res) {
        std::string cmd = "ping cn.bing.com -c 10";
        
        auto ret = exec_cmd(cmd);
        std::cout<< ret <<std::endl;
        res.set_content(ret, "text/plain");
    });

    server.Get("/ifconfig", [](const httplib::Request &, httplib::Response &res) {
        std::string cmd = "ifconfig";
        auto ret = exec_cmd(cmd);
        std::cout<< ret <<std::endl;
        res.set_content(ret, "text/plain");
    });

    server.Get("/route", [](const httplib::Request &, httplib::Response &res) {
        std::string cmd = "route";
        auto ret = exec_cmd(cmd);
        std::cout<< ret <<std::endl;
        res.set_content(ret, "text/plain");
    });
    printf("listen ....");
    server.listen("0.0.0.0", 18888);
    
    // printf("\n%d\n", x);

    return 0;
}



