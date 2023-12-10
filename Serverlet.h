#define SERVERLET_H

#ifndef RESPONSE_H
    #include "Response.h"
#endif

#ifndef ROUTER_H
    #include "Router.h"
#endif

class Serverlet{
    private:
        Router* appRouter;
    public:
        int socketFlow();
        void createListener();
        void sendResponse(Response response);
};