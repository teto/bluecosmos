--fct + args
function loop(fct,...)

end

function spacefighter( entity  )
	
    --print("calling spacefighter")
    -- remplacer par une fct setup
    entity:setMesh("models/spacefighter.obj");
    entity:setup(
				3, 	-- range
				40,	-- life
				3,	-- damage
				100	-- bonus
				
				);
    --entity:setRange(3);
    --entity:setBonus(3);
    --entity:setLife(4);
	
	
	log_info("Adding loop task ");
	
	-- log_info(" TTOTOTOTOTOTOTOTO");
	-- wait( 5000 )
	-- log_info(" TTOTOTOTOTOTOTOTO");
	
	
	--addDependantTask( id, limited_loop( 4,aim_at_player) );
	
	--addNonblockingTask( moveInDirection,  entity,0,-0.1 )
	--addNonblockingTask( moveInDirection,  entity,0.2,0 )
	
	-- avec 2 ca marche avec 3 ca plante
	--addBlockingTask( limited_loop( 2,aim_at_player) );
	
	
	
	--log_info(">>>> start wait");
	--wait_fn(3000);
	--log_info("\n>>>> end wait");
	--addBlockingTask( id, moveInDirection,  entity,0,-0.2 );
	-- ceci ne doit pas s'afficher avant la fin de la tache precendete
	local x,y,z = entity:getPos();
	
	entity:setTarget(Player);
	entity:setRotationSpeed(360);
	addBlockingTask( infinite_loop( aim_at_player), entity );
	
	log_info("================\t spaceFighter finished at pos "..x.."/"..z.."!\t==============");
end


function aim_at_player(entity)
	
	--log_info("aim at player task with id ["..id.."]");
	--log_info("\n==>toto<==");
	entity:updateRotation();
	wait(2000)
	--local px,py,pz = Player:getPos();
	-- will try to face target
	
	entity:shootBullet("models/missile.obj",0);
	
	--getHorizontalAngle ()
	
	
end