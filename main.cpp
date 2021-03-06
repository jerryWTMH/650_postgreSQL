#include <iostream>
#include <pqxx/pqxx>
#include <fstream>      // std::ifstream

#include "exerciser.h"

using namespace std;
using namespace pqxx;

void dropTable(connection *C, string tableName){
  string sql = "DROP TABLE IF EXISTS " + tableName + " CASCADE;";
  work W(*C);
  W.exec(sql);
  W.commit();
}

void loadTables(string & sql, string filename, connection *C){
  ifstream ifs(filename);
  string curr_line;
  if(ifs.is_open()){
    while(getline(ifs, curr_line)){
      sql.append(curr_line);
    }
    // cout << "sql would be like: " << sql << endl;
    work W(*C);
    W.exec(sql);
    W.commit();
  } else{
    cout << "The loading of tables has some problems" << endl;
    return;
  }
 

}

void parsePlayer(string filename, connection *C){
  ifstream ifs(filename);
  if (ifs.is_open()) {
    // print file:
    string curr_line;
    int player_id, team_id, uniform_num, mpg, ppg, rpg, apg;
    string last_name, first_name;
    double spg, bpg;

    while(getline(ifs, curr_line)){
      stringstream ss(curr_line);
      ss >> player_id >> team_id >> uniform_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
      add_player(C, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
    } 
    ifs.close();
    // cout<< "The adding of all players are finished!!!" << endl;
  }
  else {
    // show message:
    std::cout << "Error opening file";
  }
}

void parseTeam(string filename, connection *C){
  ifstream ifs(filename);
  if (ifs.is_open()) {
    // print file:
    string curr_line;
    int team_id, state_id, color_id, wins, losses;
    string name;
    while(getline(ifs, curr_line)){
      stringstream ss(curr_line);
      ss >> team_id >> name >> state_id >> color_id >> wins >> losses;
      add_team(C, name, state_id, color_id, wins, losses);
    } 
    ifs.close();
    // cout<< "The adding of all teams are finished!!!" << endl;
  }
  else {
    // show message:
    std::cout << "Error opening file";
  }

}

void parseState(string filename, connection *C){
  ifstream ifs(filename);
  if (ifs.is_open()) {
    // print file:
    string curr_line;
    int state_id;
    string name;
    while(getline(ifs, curr_line)){
      stringstream ss(curr_line);
      ss >> state_id >> name;
      add_state(C, name);
    } 
    ifs.close();
    // cout<< "The adding of all states are finished!!!" << endl;
  }
  else {
    // show message:
    std::cout << "Error opening file";
  }
}

void parseColor(string filename, connection *C){
  ifstream ifs(filename);
  if (ifs.is_open()) {
    // print file:
    string curr_line;
    int color_id;
    string name;
    while(getline(ifs, curr_line)){
      stringstream ss(curr_line);
      ss >> color_id >> name;
      add_color(C, name);
    } 
    ifs.close();
    // cout<< "The adding of all colors are finished!!!" << endl;
  }
  else {
    // show message:
    std::cout << "Error opening file";
  }
}

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      // cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }

    /*Drop the table first */
    dropTable(C, "PLAYER");
    dropTable(C, "COLOR");
    dropTable(C, "TEAM");
    dropTable(C, "STATE");
    /* Create SQL statement */
    string sql;
    loadTables(sql, "tables.sql", C);

  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  parseColor("color.txt", C);
  parseState("state.txt", C);
  parseTeam("team.txt", C);
  parsePlayer("player.txt", C);
  

  // Start exercise!
  exercise(C);
  //Close database connection
  C->disconnect();

  return 0;
}


