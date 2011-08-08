
--require("dialogs/french.lua");
--dialogs[0]

--local dlg = CDialog();

--MainState.createSpeech();
--MainState:showMessage(speaker,speech)
function addSpeech(actor,speech)
    MainState:showMessage(actor,speech);
    local reply = MainState:getPlayerReply();
    return reply;
end

--co = coroutine.create(addSpeech);

actor1 = Level:addActor("Eldaric","images/portraits/eldaric.png");
actor2 = Level:addActor("Logalmier","images/portraits/logalmier.png");

--,"sounds/bgm.mp3"actor1,
local speech = MainState.createSpeech("Hi buddy welcome in the tutorial ! Press W to go on.", "sounds/bgm.mp3");

print("calling Show message");

MainState:showMessage(actor1,speech);


local ret = MainState:getPlayerReply();

--[[
print("Show message call finished");

if(ret == 1) then
    --print( 'dialog returned one');
    --actor2,
    CLevelManager.createSpeech("There might be a part of RPG in the future with choices to do","sounds/bgm.mp3");

end
--MainState:addSpeech(actor2,"There might be a part of RPG in the future with choices to do");
--actor1,
CLevelManager.createSpeech("2nd answer chosen... but there's still a long way to go","sounds/bgm.mp3");


]]--
