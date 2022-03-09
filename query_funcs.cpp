#include "query_funcs.h"
#include <iostream>
#include <pqxx/pqxx> 
using namespace std;
using namespace pqxx;


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) 
{
    try{
    /* Create a transactional object. */
    work W(*C);
    /* Create SQL statement */
    string sql;
    stringstream valueStream;
    // cout<< "firstname: " << first_name << ", bpg: " << bpg << endl;
    valueStream << team_id << ", " << jersey_num << ", " << W.quote(first_name) << ", " << W.quote(last_name) << ", " << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", " << spg << ", " << bpg;
    string valueString = valueStream.str();
    sql = "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES (";
    sql = sql + valueString + ");";
    
    

    /* Execute SQL query */
    // cout << "sql : " << sql << endl;
    W.exec(sql);
    W.commit();
    cout << "Players created successfully" << endl;
    } catch (exception & e){
        cerr << e.what() << endl;
    }
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
}


void add_state(connection *C, string name)
{
}


void add_color(connection *C, string name)
{
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
    
}


void query2(connection *C, string team_color)
{
}


void query3(connection *C, string team_name)
{
}


void query4(connection *C, string team_state, string team_color)
{
}


void query5(connection *C, int num_wins)
{
}

void test_player(connection *C){
    string sql;
    sql = "SELECT * from PLAYER";
     /* Create a non-transactional object. */
    nontransaction N(*C);
      
    /* Execute SQL query */
    result R( N.exec( sql ));
      
    /* List down all the records */
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << "Player_id = " << c[0].as<int>() << endl;
      cout << "Team_id = " << c[1].as<int>() << endl;
      cout << "Uniform_num = " << c[2].as<int>() << endl;
      cout << "First_name = " << c[3].as<string>() << endl;
      cout << "Last_name = " << c[4].as<string>() << endl;
      cout << "MPG = " << c[5].as<int>() << endl;
      cout << "PPG = " << c[6].as<int>() << endl;
      cout << "RPG = " << c[7].as<int>() << endl;
      cout << "APG = " << c[8].as<int>() << endl;
      cout << "SPG = " << c[9].as<float>() << endl;
      cout << "BPG = " << c[10].as<float>() << endl;
    //   cout << "Age = " << c[2].as<int>() << endl;
    //   cout << "Address = " << c[3].as<string>() << endl;
    //   cout << "Salary = " << c[4].as<float>() << endl;
    }
    cout << "Operation done successfully" << endl;
}
