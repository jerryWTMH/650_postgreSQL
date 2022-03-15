#include "query_funcs.h"
#include <iostream>
#include <pqxx/pqxx> 
#include <string.h>
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
        W.exec(sql);
        W.commit();
        // cout << "Players created successfully" << endl;
    } catch (exception & e){
        cerr << e.what() << endl;
    }
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    try{
        /* Create a transactional object. */
        work W(*C);
        /* Create SQL statement */
        string sql;
        stringstream valueStream;
        // cout<< "firstname: " << first_name << ", bpg: " << bpg << endl;
        valueStream << W.quote(name) << ", " << state_id << ", " << color_id << ", " << wins << ", " << losses;
        string valueString = valueStream.str();
        sql = "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES (";
        sql = sql + valueString + ");";
        // cout << "sql :" << sql << endl;
        /* Execute SQL query */
        W.exec(sql);
        W.commit();
        // cout << "Players created successfully" << endl;
    } catch (exception & e){
        cerr << e.what() << endl;
    }
}


void add_state(connection *C, string name)
{
    try{
        /* Create a transactional object. */
        work W(*C);
        /* Create SQL statement */
        string sql;
        stringstream valueStream;
        // cout<< "firstname: " << first_name << ", bpg: " << bpg << endl;
        valueStream << W.quote(name);
        string valueString = valueStream.str();
        sql = "INSERT INTO STATE (NAME) VALUES (";
        sql = sql + valueString + ");";
        /* Execute SQL query */
        W.exec(sql);
        W.commit();
        // cout << "Players created successfully" << endl;
    } catch (exception & e){
        cerr << e.what() << endl;
    }
}


void add_color(connection *C, string name)
{
    try{
        /* Create a transactional object. */
        work W(*C);
        /* Create SQL statement */
        string sql;
        stringstream valueStream;
        // cout<< "firstname: " << first_name << ", bpg: " << bpg << endl;
        valueStream << W.quote(name);
        string valueString = valueStream.str();
        sql = "INSERT INTO COLOR (NAME) VALUES (";
        sql = sql + valueString + ");";
        /* Execute SQL query */
        W.exec(sql);
        W.commit();
        // cout << "Players created successfully" << endl;
    } catch (exception & e){
        cerr << e.what() << endl;
    }
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
  work W(*C);
  string sql;
  sql = "SELECT * FROM PLAYER WHERE ";
  int counter = 0;
  if(use_mpg != 0){
      sql = sql + "MPG >= " + to_string(min_mpg) + " AND MPG <= " + to_string(max_mpg);
      counter++;
  }
  if(use_ppg != 0){
      if(counter != 0){
          sql = sql + " AND ";
      }
      sql = sql + "PPG >= " + to_string(min_ppg) + " AND PPG <= " + to_string(max_ppg);
      counter++;
  }
  if(use_rpg != 0){
      if(counter != 0){
          sql = sql + " AND ";
      }
      sql = sql + "RPG >= " + to_string(min_rpg) + " AND RPG <= " + to_string(max_rpg);
      counter++;
  }
  if(use_apg != 0){
      if(counter != 0){
          sql = sql + " AND ";
      }
      sql = sql + "APG >= " + to_string(min_apg) + " AND APG <= " + to_string(max_apg);
      counter++;
  }
  if(use_spg != 0){
      if(counter != 0){
          sql = sql + " AND ";
      }
      sql = sql + "SPG >= " + to_string(min_spg) + " AND SPG <= " + to_string(max_spg);
      counter++;
  }
  if(use_bpg != 0){
      if(counter != 0){
          sql = sql + " AND ";
      }
      sql = sql + "BPG >= " + to_string(min_bpg) + " AND BPG <= " + to_string(max_bpg);
      counter++;
  }
  if(counter != 0){
    sql = sql + ";";  
    W.commit();
    nontransaction N(*C);
    result R(N.exec(sql));
    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<int>() << " ";
        cout << c[1].as<int>() << " ";
        cout << c[2].as<int>() << " ";
        cout << c[3].as<string>() << " ";
        cout << c[4].as<string>() << " ";
        cout << c[5].as<int>() << " ";
        cout << c[6].as<int>() << " ";
        cout << c[7].as<int>() << " ";
        cout << c[8].as<int>() << " ";
        cout << c[9].as<double>() << " ";
        cout << c[10].as<double>() << endl;
    }
  } else{
    sql = "SELECT * FROM PLAYER ";
    W.commit();
    nontransaction N(*C);
    result R(N.exec(sql));
    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<int>() << " ";
        cout << c[1].as<int>() << " ";
        cout << c[2].as<int>() << " ";
        cout << c[3].as<string>() << " ";
        cout << c[4].as<string>() << " ";
        cout << c[5].as<int>() << " ";
        cout << c[6].as<int>() << " ";
        cout << c[7].as<int>() << " ";
        cout << c[8].as<int>() << " ";
        cout << c[9].as<double>() << " ";
        cout << c[10].as<double>() << endl;
    }
  }
  
}


void query2(connection *C, string team_color)
{
  work W(*C);
  string sql;
  sql = "SELECT TEAM.NAME FROM COLOR, TEAM WHERE TEAM.COLOR_ID = COLOR.COLOR_ID AND COLOR.NAME = ";
  sql = sql +  W.quote(team_color) + ";";
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "NAME" << endl;
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << endl;
  }
}


void query3(connection *C, string team_name)
{
  work W(*C);
  string sql;
  sql = "SELECT FIRST_NAME, LAST_NAME FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.NAME = ";
  sql = sql +  W.quote(team_name) + " ORDER BY PPG DESC;";
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "FIRST_NAME LAST_NAME" << endl;
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << " "; 
    cout << c[1].as<string>() << endl;
  }
}


void query4(connection *C, string team_state, string team_color)
{
  work W(*C);
  string sql;
  sql = "SELECT FIRST_NAME, LAST_NAME, UNIFORM_NUM FROM PLAYER, STATE, COLOR, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.COLOR_ID = COLOR.COLOR_ID AND TEAM.STATE_ID = STATE.STATE_ID AND COLOR.NAME = ";
  sql = sql + W.quote(team_color);
  sql = sql + " AND STATE.NAME = ";
  sql = sql + W.quote(team_state) + ";";
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << " "; 
    cout << c[1].as<string>() << " ";
    cout << c[2].as<int>() << endl;
  }
}


void query5(connection *C, int num_wins)
{
  work W(*C);
  string sql;
  sql = "SELECT FIRST_NAME, LAST_NAME, NAME, WINS FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.WINS >= ";
  sql = sql + W.quote(num_wins) + ";";
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << " "; 
    cout << c[1].as<string>() << " ";
    cout << c[2].as<string>() << " ";
    cout << c[3].as<int>() << endl;
  }
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
