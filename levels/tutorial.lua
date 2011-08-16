--[[levelinfo = {
width = 200,
height = 200,
name = "test"
}
]]--

-- TODO essayer de creer un level
--Level:setBackground("images/skydome.jpg");
--Level:addLayer();



--print("\nDEBUG preloading stuff");

-- TODO should be able to load them via threads
--dummyModel      = Level:loadModel("models/spacefighter.obj", 10, 50, 4);
--bgm             = Level:loadMusic("sounds/bgm.mp3");
eldaricActor    = MainState:loadActor("Eldaric","images/portraits/eldaric.png");
--logalmierActor  = Level:loadActor("Logalmier","images/portraits/logalmier.png");




addIndependantTask(
	nil,
    function ()
        --print("activator called!");
		--onReach(0.01)
		--luaManager:addBlockingTask( function () return onReach(0.01) end);
        while not onReach(0.1) do
            coroutine.yield();
        end

        log_info("POINT REACHED !!!");
        spawnFront(3,"spacefighter");

    end
);


-- TODO a generaliser
--[[
function startDialog(actor,speech)
	log_info("Starting dialog");

	MainState:showMessage(actor,speech);

	return coroutine.yield(luaManager.ReturnCodes.WaitingForInput);
end


addIndependantTask(
    nil,
    function ()

        --,"sounds/bgm.mp3"actor1,, "sounds/bgm.mp3"
        -- MainState
        local speech = CSinglePlayerState.createSpeech("Welcome to Blue Cosmos tutorial !\nPress W to go on.");
		--speech:setAudio();

        --print("calling Show message");
        speech:addAnswer("Resume tutorial",0);
        speech:addAnswer("Start first level",1);

        -- sort de la tache
        -- TODO yield cette coroutine et en mm temps celle du dessus
        --coroutine.yield(
        print ( "Running coroutine " , coroutine.running() )
		reply = startDialog(eldaricActor,speech);


        --startDialog(eldaricActor,speech);

        print("getting player reply from lua");

        -- local ret = MainState:getUserReply();
        print ("TOTO reply: "..reply);

        --logalmierActor
    end
);
]]--
