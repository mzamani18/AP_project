#include <iostream>
#include <Board.h>
#include <httplib.h>
#include <string>

using namespace std;

int main()
{
    httplib::Client cli("127.0.0.1", 8000);
    if (auto res = cli.Get("/start"))
    {
        string username = res->body;
        cout << res->body << endl;
        string tmp = username.substr(39, 1);
        int num_of_players = stoi(tmp);
        username = username.substr(12, 4);
        cout << username << endl;
        if (res->status == 200)
        {
            //std::cout << res->body << std::endl;
            //username = username.substr(0, 3) + to_string(turn % num_of_players + 1);
            string ss = "";
            ss = "1A";
            //cout << ss << endl;
            while (true)
            {
                //auto ress = cli.Post("/turn", "0a", "text_plain");
                //cout << ress->body << endl;
                //cout << username[3] << endl;
                //cout << "ye chizi" << endl;
                //cout << ress->body << endl;
                if (ss[0] == username[3])
                {
                    cout << "The Updated Board after your Competitor move:\n";
                    auto res_of_map = cli.Post("/pl", "map", "text/plain");
                    cout << res_of_map->body << endl;
                    cout << "the player" << ss[0] << "is your turn" << endl;
                    string temp;
                    cin >> temp;
                    auto res = cli.Post("/pl", temp, "text/plain");
                    cout << res->body << endl;
                    auto res_res = cli.Post("/pl" /* username.c_str()*/, "next", "text/plain");
                    ss = res_res->body;
                    //cout << ss << endl;
                }
                else
                {
                    auto res_res = cli.Post("/pl", "now", "text/plain");
                    ss = res_res->body;
                }
                //cli.Post("/turn", "1a", "text_plain");
            }
        }
        else
        {
            cout << "Error" << endl;
        }
    }
}