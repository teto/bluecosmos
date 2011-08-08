
--print("Got elasped time");
_G["elapsedTime"] = Engine:getElapsedTime();
--=

--game:Think( Engine:getElapsedTime() );



-- stop updating player input when dialoguing for example
--if( MainState:isPlayerUpdatable() ) then
--print("update player");
--local test = coroutine.running();
--print( "test",test);

log_info("stop main thread");

log_error ("FAIL");

luaManager:update();

    Player:processMoves();
    Player:processTransformations();
    Player:processShootings();
--end
--elapsedTime
MainState:update();
