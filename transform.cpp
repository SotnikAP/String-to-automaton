#include <unordered_set>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

void error( const std::string& e )
{
     std::cerr << e << std::endl;
}

std::vector<char> dictionary;

/// @brief Count number of actions in string.
///
/// @param [in] str - string, which will be transformed into automaton and actions number of which needs to count.
/// @return Number of actions.
int NumOfActions( const std::string& str )
{
     std::unordered_set<char> actions;

     for ( auto i : str )
     {
          actions.insert( i );
     }

     return actions.size();
}

int NumOfStates( const std::string& str )
{
     int numOfStates = 0;

     for ( auto i : str )
     {
          if ( i != '*' )
          {
               numOfStates++;
          }
     }

     return numOfStates;
}

int Find( char symb )
{
     if ( dictionary.empty() )
     {
          dictionary.push_back( symb );
          return -1;
     }
     for ( int i = 0; i < dictionary.size(); i++ )
     {
          if ( dictionary[i] == symb )
          {
               return i;
          }
          else
          {
               return -1;
          }
     }
}

int SymbToInt( char symb )
{
     if ( Find( symb ) == -1 )
     {
          dictionary.push_back( symb );
          return dictionary.size() + 1;
     }
     else
     {
          return Find( symb );
     }
}

/// @brief Makes file in fsm format, which represent automaton.
///
/// @param [in] str - string which will be transformed into automaton in .fsm format.
/// @return File in fsm format. which represent automaton.
void StringToAutomaton( const std::string& str, std::ofstream& file )
{
     const int numOfActions = NumOfActions( str );
     const int numOfStates = NumOfStates( str ) + 1;

     file << "F 4\n"
          << "S " << numOfStates << "\n"
          << "a " << numOfActions << "\n"
          << "n0 0\n"
          << "f " << str.size() << "\n"
          << "p " << numOfStates*numOfActions << "\n";

     std::unordered_set<char> checkUnique;

     for ( auto i = 0; i < numOfStates; i++ )
     {
          checkUnique.clear();
          for ( auto j = 0; j < numOfStates; j++ )
          {
               if ( checkUnique.insert( str[j] ).second )
               {     
                    if ( str[i] == str[j] )
                    {
                         file << i << " " << SymbToInt(str[i]) << " " << i + 1 << "\n";
                    }
                    else
                    {
                         file << i << " " << SymbToInt(str[j]) << " " << str.size() + 1 << "\n";
                    }
               }
          }
     }
}

int main( /*int argc, char* argv[]*/ )
{
     /*if ( argc < 2 )
     {
          error( "Execute with two files in .fsm format." );
          return 2;
     }*/

     /*for ( auto i = 1; i < argc; i++ )
     {*/
          std::ifstream fileWithString( "firstAtack.txt" );
          std::ofstream automaton( "notUnicode.txt" );

          std::string str;

          std::getline( fileWithString, str );

          StringToAutomaton( str, automaton );
          SymbToInt( '*' );
     /*}*/

     std::cout << "Succesful! \n";
}