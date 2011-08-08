#include "IConsole.hpp"
#include "../core/string.hpp"
#include "../logging/ILogger.hpp"


namespace fus {


IConsole::~IConsole() {
}



bool
IConsole::ValidateInput(const IConsole::TStringType& command,IInterpreter* interpreter){

    //BOOST_ASSERT(interpreter);
//    mCommands.push_back(command);

    if(interpreter){

        //convertir la commande
        //"print('hello')"

        //TODO y  a un bug ici
//        dans l'affichage etc...
        std::string temp("");
        convertIntoNarrowString(command,temp);
        _INFO << "commande convertie en narrow string :[" << temp << "] Running command...\r\n";
        bool ret = interpreter->RunCommand( temp.c_str() );

        //bool ret = false;
        return ret;
    }
    return false;
}




}
