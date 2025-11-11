#ifndef DESTINATION_PACKAGE_H
#define DESTINATION_PACKAGE_H

#include <vector>
#include <map>

#include "package.h"

class DestinationPackages {
    private:
        std::map<std::string, std::vector<Package*>> _packs;
    public:
        ~DestinationPackages();
        void add_package(Package* g);
        double custo_total();
        double custo_total(std::string nome);
};

#endif

