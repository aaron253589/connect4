#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>
#include "Router.h"

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

#endif