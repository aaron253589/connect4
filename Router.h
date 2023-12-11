#define ROUTER_H

#ifndef RESPONSE_H
  #include "Response.h"
#endif

#ifndef REQUEST_H
    #include "Request.h"
#endif

#include <string>
#include <functional>
#include <map>


class Router{
    public:
      enum HttpMethod{GET, POST};
      void add(HttpMethod method, std::string path, Response(&func)(std::string));
      Response(&getCallBack(Request request))(std::string);

      private:
        std::map<HttpMethod,std::map<std::string,Response(std::string)>> map;
};