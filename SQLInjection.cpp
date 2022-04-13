// SQLInjection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <locale>
#include <tuple>
#include <vector>

#include "sqlite3.h"
#include <regex>
#include "../SQL Injection Enhancement/sqlite3.h"

// DO NOT CHANGE
typedef std::tuple<std::string, std::string, std::string> user_record;
const std::string str_where = " where ";

// DO NOT CHANGE
static int callback(void* possible_vector, int argc, char** argv, char** azColName)
{
  if (possible_vector == NULL)
  { // no vector passed in, so just display the results
    for (int i = 0; i < argc; i++) 
    {
      std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
  }
  else
  {
    std::vector< user_record >* rows =
      static_cast<std::vector< user_record > *>(possible_vector);

    rows->push_back(std::make_tuple(argv[0], argv[1], argv[2]));
  }
  return 0;
}

// DO NOT CHANGE
bool initialize_database(sqlite3* db)
{
  char* error_message = NULL;
  std::string sql = "CREATE TABLE USERS(" \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "PASSWORD       TEXT    NOT NULL);";

  int result = sqlite3_exec(db, sql.c_str(), callback, NULL, &error_message);
  if (result != SQLITE_OK)
  {
    std::cout << "Failed to create USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }
  std::cout << "USERS table created." << std::endl;

  // insert some dummy data
  sql = "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (1, 'Fred', 'Flinstone');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (2, 'Barney', 'Rubble');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (3, 'Wilma', 'Flinstone');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (4, 'Betty', 'Rubble');" \
      //Four new dummy sets, to further test OR/AND, with no constant reference like the sample four
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (5, 'Randy', 'Orbit');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (6, 'Boris', 'Andre');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (7, 'Orlando', 'Corey');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (8, 'Bandit', 'Bandy');";

  result = sqlite3_exec(db, sql.c_str(), callback, NULL, &error_message);
  if (result != SQLITE_OK)
  {
    std::cout << "Data failed to insert to USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }

  return true;
}

int find_match_position(std::string s) {
//First, we cover the OR searches, then we have a separate set for the AND searches, to enhance search capability
    std::smatch m;
    std::regex e1("or");
//First it checks for the phrase 'or' and if it does not find based off of that, it searches for or value = value itself 
//New Version of our  OR searches, with the old ones commented out
    std::regex e2("or '[a-zA-Z]+' = '[a-zA-Z'] + '");
    std::regex e3("or  '[1-9]+=[1-9]+'");

    std::regex_search(s, m, e1);
//If it fails to find from or, it runs both the e2 and e3 checks to check for or value=value
    if (m.position(0) == 0) {
        std::regex_search(s, m, e2);
        std::regex_search(s, m, e3);
    }
//This section is identical to the OR searches, but uses AND instead
    std::smatch m2;
    std::regex e4("and");


//Our AND Searches moved to a new location, since it does this search set after the OR set. 
    std::regex e5("and '[a-zA-Z]+' = '[a-zA-Z'] + '");
    std::regex e6("and  '[1-9]+=[1-9]+'");

    std::regex_search(s, m2, e4);
    if (m.position(0) == 0) {
        std::regex_search(s, m2, e5);
        std::regex_search(s, m2, e6);
    }


    //Final failsafe regex search using just value phrases.
    std::regex e7("'[a-zA-Z]+' = '[a-zA-Z'] + '");
    std::regex e8("'[1-9]+=[1-9]+'");
    if (m.position(0) == 0) {
        std::regex_search(s, e7);
        std::regex_search(s, e8);
    }

    std::cout << "Match for concerning phrase found, position information hidden.";
    //I figured, that once I had an understanding of this code, the possition information should be hidden from the view because that could be used
    //in order to make attacks more easy.



    return m.position(0);
}
bool run_query(sqlite3* db, const std::string& sql, std::vector< user_record >& records)
{
    // TODO: Fix this method to fail and display an error if there is a suspected SQL Injection
    //  NOTE: You cannot just flag 1=1 as an error, since 2=2 will work just as well. You need
    //  something more generic
    int pos = find_match_position(sql.c_str());
    if (pos >= 0)
        //I couldn't really think of an all that better way to do this part of the code after thinkering with it. 
        std::cout << "\nTERMINATE SQL INJECTION ATTEMPT!\n";
    char temp[100]; //Lower character number just based on length of the phrases used.
    int x = 0;
    for (x = 0; x < pos; x++)
        temp[x] = sql.c_str()[x];
    temp[x] = '\0';

    // clear any prior results
    records.clear();

  char* error_message;
  if(sqlite3_exec(db, sql.c_str(), callback, &records, &error_message) != SQLITE_OK)
  {
    std::cout << "Data failed to be queried from USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }

  return true;
}

// DO NOT CHANGE
bool run_query_injection(sqlite3* db, const std::string& sql, std::vector< user_record >& records)
{
  std::string injectedSQL(sql);
  std::string localCopy(sql);

  // we work on the local copy because of the const
  std::transform(localCopy.begin(), localCopy.end(), localCopy.begin(), ::tolower);
  if(localCopy.find_last_of(str_where) >= 0)
  { // this sql has a where clause
    if(localCopy.back() == ';')
    { // smart SQL developer terminated with a semicolon - we can fix that!
      injectedSQL.pop_back();
    }

    switch (rand() % 4)
    {
       
      //Section of OR cases
    case 1:
      injectedSQL.append(" or 2=2;");
      break;
    case 2:
      injectedSQL.append(" or 'hi'='hi';");
      break;
    case 3:
      injectedSQL.append(" or 'hack'='hack';");
      break;
      //Section of additional cases for AND searches.
    case 4:
       injectedSQL.append(" and 2=2;");
       break;
    case 5:
       injectedSQL.append(" and 'hi'='hi';");
       break;
    case 6:
       injectedSQL.append(" and 'hack'='hack';");
       break;
    case 7:
       injectedSQL.append(" and 1=1;");
       break;
       //Default or case #0
    case 0:
    default:
      injectedSQL.append(" or 1=1;");
      break;
    }
  }
  
  return run_query(db, injectedSQL, records);
}


// DO NOT CHANGE
void dump_results(const std::string& sql, const std::vector< user_record >& records)
{
  std::cout << std::endl << "SQL: " << sql << " ==> " << records.size() << " records found." << std::endl;

  for (auto record : records)
  {
    std::cout << "User: " << std::get<1>(record) << " [UID=" << std::get<0>(record) << " PWD=" << std::get<2>(record) << "]" << std::endl;
  }
}

// DO NOT CHANGE
void run_queries(sqlite3* db)
{
  char* error_message = NULL;

  std::vector< user_record > records;

  // query all
  std::string sql = "SELECT * from USERS";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);
  // query old
  std::string sql = "SELECT * from USERS WHERE ID='1','2','3','4'";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);
  // query old
  std::string sql = "SELECT * from USERS WHERE ID='5','6','7','8'";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);

  //  query 1
  sql = "SELECT ID, NAME, PASSWORD FROM USERS WHERE NAME='Fred'";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);
  //  run query 1 with injection 10 times, originally 5
  for (auto i = 0; i < 10; ++i)
  {
    if (!run_query_injection(db, sql, records)) continue;
    dump_results(sql, records);
  }

  //  query 2
  sql = "SELECT ID, NAME, PASSWORD FROM USERS WHERE NAME='Randy'";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);
  //  run query 2 with injection 5 times
  for (auto i = 0; i < 5; ++i)
  {
      if (!run_query_injection(db, sql, records)) continue;
      dump_results(sql, records);
  }

}

// You can change main by adding stuff to it, but all of the existing code must remain, and be in the
// in the order called, and with none of this existing code placed into conditional statements
int main()
{
  // initialize random seed:
  srand(time(nullptr));

  int return_code = 0;
  std::cout << "SQL Injection Example" << std::endl;

  // the database handle
  sqlite3* db = NULL;
  char* error_message = NULL;

  // open the database connection
  int result = sqlite3_open(":memory:", &db);

  if(result != SQLITE_OK)
  {
    std::cout << "Failed to connect to the database and terminating. ERROR=" << sqlite3_errmsg(db) << std::endl;
    return -1;
  }

  std::cout << "Connected to the database." << std::endl;

  // initialize our database
  if(!initialize_database(db))
  {
    std::cout << "Database Initialization Failed. Terminating." << std::endl;
    return_code = -1;
  }
  else
  {
    run_queries(db);
  }

  // close the connection if opened
  if(db != NULL)
  {
    sqlite3_close(db);
  }

  return return_code;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
