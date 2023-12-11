#define REQUEST_H

#ifndef ROUTER_H
    #include "Router.h"
#endif

#include <string>
#include <map>

class Request{
    private:
    std::string path;
    std::string requestParams;
        Router::HttpMethod method;
        std::map<std::string, std::string>* headers;
        std::string body;
    public:
        std::string& getPath();
        std::string& getRequestParams();
        std::string& getBody();
        std::string& getHeader(std::string header);
        Router::HttpMethod getMethod();
        Request(std::string rawRequest);
};