#define REQUEST_H

#include "Router.h"

#include <string>
#include <map>

class Request{
    private:
        Router::HttpMethod method;
        std::map<std::string, std::string>* headers;
        std::string body;
    public:
        Request(std::string rawRequest);
};