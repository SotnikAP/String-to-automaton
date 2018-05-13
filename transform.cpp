#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>

void error( const std::string& e )
{
     std::cerr << e << std::endl;
}

int NumOfActions( const std::string str )
{
     std::unordered_set<char> actions;

     for ( auto i : str )
     {
          actions.insert( i );
     }

     return actions.size();
}

void StringToAutomaton( const std::string& str, std::ofstream& file )
{
     const int numOfActions = NumOfActions( str );
     const int numOfStates = str.size() + 1;

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
                         file << i << " " << str[i] << " " << i + 1 << "\n";
                    }
                    else
                    {
                         file << i << " " << str[j] << " " << str.size() + 1 << "\n";
                    }
               }
          }
     }
}

int main( int argc, char* argv[] )
{
     if ( argc < 2 )
     {
          error( "Execute with two files in .fsm format." );
          return 2;
     }

     for ( auto i = 1; i < argc; i++ )
     {
          std::ifstream fileWithString( argv[i] );
          std::ofstream automaton( "notUnicode.txt" );

          std::string str;

          std::getline( fileWithString, str );

          StringToAutomaton( str, automaton );
     }

     std::cout << "Succesful! \n";
}