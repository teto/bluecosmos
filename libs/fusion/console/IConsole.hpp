#ifndef _FUSION_CONSOLE_HPP
#define _FUSION_CONSOLE_HPP


#include <list>
#include <iostream>
#include <vector>
#include <fusion/fusion.hpp>
#include <fusion/scripting/IScriptInterpreter.hpp>



namespace fus {




class IConsole
{

protected:
    typedef std::wstring TStringType;
    //typedef TStringType TCommand;
    //typedef std::vector<TCommand> TCommandList;
    //TCommandList mCommands;

    //TCommand _bufferedCommand;

    //TStringType mBuffer;
    //TCommandList::iterator mIterator;
//    IConsole();




public:
    //void setVM
    //setInterpreter

    bool ValidateInput(const TStringType& command,IInterpreter* interpreter);
//    TStringType PreviousCommand();
//    TStringType NextCommand();

    //virtual TStringType getBufferedInput() = 0;
    //virtual void addToCommandList() = 0;

    //const TStringType& getCurrentCommand() const {return mBuffer;};

    virtual ~IConsole();


};

}


#endif
