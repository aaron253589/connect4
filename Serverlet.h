#ifndef SERVERLET_H
#define SERVERLET_H

    #include "Response.h"
    #include "Router.h"

class Serverlet{
    private:
        Router* appRouter;
    public:
        int socketFlow();
        void createListener();
        void sendResponse(Response response);
};
#endif