#ifndef ROUTER_H
#define ROUTER_H

#include "Response.h"

#include <string>
#include <functional>
#include <map>

class Request;

 class Router{
    public:
      enum HttpMethod{GET, POST};
      void add(HttpMethod method, std::string path, Response(&func)(std::string));
      Response(&getCallBack(Request request))(std::string);

      private:
        std::map<HttpMethod,std::map<std::string,std::function<Response(std::string)>>> map;
};
#endif