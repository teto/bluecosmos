--move entity of a vector v(xVec,yVec);
-- HACK / TEST ONLY
-- entity should be userdata
-- Todo transformer en infinite_loop
function moveInDirection(entity,xVec,zVec)

	while true do
		entity:translate(xVec,0,zVec);
		coroutine.yield();
	end
end



--[[ 
function moveToPoint(duration,xDest,yDest, entity)

	--id = id or DMG["currentObjId"]
	local coord_end = toDMV(x,y)
	local coord = Coord(id)

	local speed = (coord_end - coord) / duration

	resetBreak()
	while (duration >= DMG["elapsedTime"]) and nobreak() do
		entity:setPosition(Coord(id) + DMG["elapsedTime"]*speed,nil,id)
		duration = duration - DMG["elapsedTime"]
		coroutine.yield()
	end

	if nobreak() then
		entity:setPosition(coord_end,nil,id)
	end
end
 ]]