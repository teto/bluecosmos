
--log_info("stop main thread");

--print("Got elasped time");
_G["elapsedTime"] = Engine:getElapsedTime();
--=

--game:Think( Engine:getElapsedTime() );



-- stop updating player input when dialoguing for example
--if( MainState:isPlayerUpdatable() ) then
--print("update player");
--local co,main = coroutine.running();
--print( "Running coroutine (from update.lua) " , main )
--log_info("stop main thread");

luaManager:update();

    Player:processMoves();
    Player:processTransformations();
    Player:processShootings();
--end
--elapsedTime
MainState:update();
