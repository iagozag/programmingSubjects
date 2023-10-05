#include <string>

class Pair{
    private:
        bool ans;
        std::string result;

    public:
        Pair();

        bool get_ans();

        std::string get_res();

        void set_ans(bool b);

        void set_result(std::string result);
};

Pair satisfaction(std::string& st, std::string& values);
